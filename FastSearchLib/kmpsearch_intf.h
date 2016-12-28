#pragma once
#include <vector>

using namespace std;

/* Class using KMP (Knuth Morris Pratt) Pattern Searching algorithm
*/
class IKmpSearch 
{
public:
	struct SearchResult {
		size_t position;
		string prefix;
		string postfix;
	};
	virtual vector<SearchResult> Run() = 0;
};
