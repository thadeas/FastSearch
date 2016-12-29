#pragma once
#include <vector>

using namespace std;

/* Class using KMP (Knuth Morris Pratt) Pattern Searching algorithm
*/
class IKmpSearch 
{
public:
	struct SSearchResult {
		size_t position;   // position of the search
		string prefix;     // prefix before the search
		string sufix;      // sufix after the search
	};

	// results of the search from buffer
	using TSearchResults = vector<IKmpSearch::SSearchResult>;

	virtual vector<SSearchResult> Run() = 0;
};
