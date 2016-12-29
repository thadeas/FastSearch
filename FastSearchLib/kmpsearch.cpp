#include "stdafx.h"
#include "kmpsearch.h"

using namespace std;

CKmpSearch::CKmpSearch(const string & pattern, const TKmpLps & lps, const shared_ptr<IChunkWrapper> & spBuffer)
	: m_pattern(pattern)
	, m_lps(lps)
	, m_spBuffer(spBuffer)
{

}

IKmpSearch::TSearchResults CKmpSearch::Run()
{
	IKmpSearch::TSearchResults results;

	size_t bufferLength = m_spBuffer->Size();
	if (!m_spBuffer->IsLast()) {   
		// if the buffer is not the last one in the file we must search inside next buffer up to the pattern length
		bufferLength += m_pattern.size() - 1;
	}
	

	size_t i = 0;  // index for buffer[]
	size_t j = 0;  // index for m_patter[]
	while (i < bufferLength)
	{
		if (m_pattern[j] == m_spBuffer->operator[](i))
		{
			j++;
			i++;
		}

		if (j == m_lps.size())
		{
			// Found pattern
			IKmpSearch::SSearchResult result;
			result.position = m_spBuffer->FileOffset() + i - j;
			result.prefix = GetPrefix(i - j);
			result.sufix = GetSufix(i);
			results.push_back(result);
			j = m_lps[j - 1];
			
		}

		// mismatch after j matches
		else if (i < bufferLength && m_pattern[j] != m_spBuffer->operator[](i))
		{
			// Do not match m_lps[0..m_lps[j-1]] characters,
			// they will match anyway
			if (j != 0)
				j = m_lps[j - 1];
			else
				i = i + 1;
		}
	}
	return results;
}

string CKmpSearch::GetPrefix(long patternBufBegin)
{
	string prefix;
	for (long index = -1; index > -PATTERN_PREFIX_LENGTH -1; index--) {
		char ch = m_spBuffer->operator[](patternBufBegin + index);
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


std::string CKmpSearch::GetSufix(long patternBufEnd)
{
	string sufix;
	for (long index = 1; index <= PATTERN_SUFIX_LENGTH; index++) {
		char ch = m_spBuffer->operator[](patternBufEnd + index);
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

void CKmpSearch::Factory::CreateKmpSearch(shared_ptr<IKmpSearch>& spKmpSearch, const string & pattern, const TKmpLps & lps, const shared_ptr<IChunkWrapper>& spBuffer)
{
	shared_ptr<CKmpSearch> spImpl = make_shared<CKmpSearch>(pattern, lps, spBuffer);
	spKmpSearch = spImpl;
}
