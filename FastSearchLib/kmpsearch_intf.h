#pragma once
#include <vector>
#include "chunkwrapper_intf.h"

using namespace std;

/* Class using KMP (Knuth Morris Pratt) Pattern Searching algorithm
*/
class IKmpSearch 
{
public:
	virtual ~IKmpSearch() {}

public:
	// this structure holds results form the search
	struct SSearchResult {
		size_t position;   // position of the search
		string prefix;     // prefix before the search
		string sufix;      // sufix after the search
	};

	// results of the search from buffer
	using TSearchResults = vector<IKmpSearch::SSearchResult>;

	// Run KMP search over buffer
	// \param[in] pBuffer weak pointer to buffer (chunk wrapper) from the file (based on file chunks)
	virtual vector<SSearchResult> Process(const IChunkWrapper * const pBuffer) = 0;
};
