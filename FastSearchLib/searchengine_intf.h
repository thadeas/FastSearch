#pragma once
#include <string>

using namespace std;

class ISearchEngine {
public:

	/* Search for all patterns in file
	   param[in] filePath File to be searched.
	*/
	virtual void Search(const wstring & filePath) = 0;
};