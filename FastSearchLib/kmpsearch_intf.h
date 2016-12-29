#pragma once
#include <vector>

using namespace std;

/* Class using KMP (Knuth Morris Pratt) Pattern Searching algorithm
*/
class IKmpSearch 
{
public:
	struct SearchResult {
		size_t position;   // position of the search
		string prefix;     // prefix before the search
		string postfix;    // postfix after the search
	};

	// results of the search from buffer
	using TSearchResults = vector<IKmpSearch::SearchResult>;

	virtual vector<SearchResult> Run() = 0;
};
