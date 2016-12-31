#include "stdafx.h"
#include "kmpsearch.h"

using namespace std;

CKmpSearch::CKmpSearch(const string & pattern, const TKmpLps & lps)
	: m_pattern(pattern)
	, m_lps(lps)
{

}

IKmpSearch::TSearchResults CKmpSearch::Process(const IFileBuffer * const pBuffer)
{
	if (pBuffer == nullptr) {
		throw invalid_argument("KMP search receive nullptr buffer.");
#ifdef _DEBUG
		assert(false);
#endif
	}

	IKmpSearch::TSearchResults results;

	size_t bufferLength = pBuffer->Size();
	if (!pBuffer->IsLast()) {   
		// if the buffer is not the last one in the file we must search inside next buffer up to the pattern length
		bufferLength += m_pattern.size() - 1;
	}
	

	size_t bufIndex = 0;  // index for buffer[]
	size_t patIndex = 0;  // index for m_patter[]
	while (bufIndex < bufferLength)
	{
		if (m_pattern[patIndex] == pBuffer->operator[](bufIndex))
		{
			patIndex++;
			bufIndex++;
		}

		if (patIndex == m_lps.size())
		{
			// Pattern found
			IKmpSearch::SSearchResult result;
			result.position = pBuffer->FileOffset() + bufIndex - patIndex;
			result.prefix = GetPrefix(pBuffer, bufIndex - patIndex);
			result.sufix = GetSufix(pBuffer, bufIndex);
			results.push_back(result);
			patIndex = m_lps[patIndex - 1];
			
		}

		// mismatch after patIndex matches
		else if (bufIndex < bufferLength && m_pattern[patIndex] != pBuffer->operator[](bufIndex))	{
			// Do not match m_lps[0..m_lps[patIndex-1]] characters,
			// they will match anyway
			if (patIndex != 0) {
				patIndex = m_lps[patIndex - 1];
			}
			else {
				bufIndex = bufIndex + 1;
			}
		}
	}
	return results;
}

string CKmpSearch::GetPrefix(const IFileBuffer * const pBuffer, long patternBufBegin)
{
	string prefix;
	for (long index = -1; index > -PATTERN_PREFIX_LENGTH -1; index--) {
		char ch = pBuffer->operator[](patternBufBegin + index);
		if (ch == INVALID_BUFFER_CHARACTER) {
			break;
		} else {
			if (IsSpecialCharacter(ch)) {
				prefix = TransformSpecialCharacter(ch) + prefix;
			}
			else {
				prefix = ch + prefix;
			}
		}
	}
	return prefix;
}


std::string CKmpSearch::GetSufix(const IFileBuffer * const pBuffer, long patternBufEnd)
{
	string sufix;
	for (long index = 0; index < PATTERN_SUFIX_LENGTH; index++) {
		char ch = pBuffer->operator[](patternBufEnd + index);
		if (ch == INVALID_BUFFER_CHARACTER) {
			break;
		}
		else {
			if (IsSpecialCharacter(ch)) {
				sufix.append(TransformSpecialCharacter(ch));
			}
			else {
				sufix.push_back(ch);
			}
		}
	}
	return sufix;
}

bool CKmpSearch::IsSpecialCharacter(char ch)
{
	/// there should be used replace dictionary
	return (ch == '\t' || ch == '\n');
}

string CKmpSearch::TransformSpecialCharacter(char ch)
{
	if (ch == '\t') {
		return string("\\t");
	}
	else if (ch == '\n') {
		return string("\\n");
	}
#ifdef _DEBUG
	// unknown special character - assert this
	assert(false);
#endif
	string retChar;
	retChar.push_back(ch);
	return retChar;
}

void CKmpSearch::Factory::CreateKmpSearch(shared_ptr<IKmpSearch>& spKmpSearch, const string & pattern, const TKmpLps & lps)
{
	shared_ptr<CKmpSearch> spImpl = make_shared<CKmpSearch>(pattern, lps);
	spKmpSearch = spImpl;
}
