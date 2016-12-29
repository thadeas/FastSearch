#include "stdafx.h"
#include "kmpsearch.h"

using namespace std;

CKmpSearch::CKmpSearch(const string & pattern, const TKmpLps & lps)
	: m_pattern(pattern)
	, m_lps(lps)
{

}

IKmpSearch::TSearchResults CKmpSearch::Run()
{
	vector<char> buffer;
	size_t m_bufferOffset = 0;

	IKmpSearch::TSearchResults results;

	size_t i = 0;  // index for buffer[]
	size_t j = 0;  // index for m_patter[]
	while (i < buffer.size())
	{
		if (m_pattern[j] == buffer[i])
		{
			j++;
			i++;
		}

		if (j == m_lps.size())
		{
			// Found pattern
			IKmpSearch::SearchResult result;
			result.position = m_bufferOffset + i - j;
			results.push_back(result);
			j = m_lps[j - 1];
			
		}

		// mismatch after j matches
		else if (i < buffer.size() && m_pattern[j] != buffer[i])
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
