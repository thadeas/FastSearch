#pragma once
#include <string>

using namespace std;

class ISearchEngine {
public:

	/* Search for all patterns in file
	   param[in] filePath File to be searched.
	   param[in] pattern Searched string.
	*/
	virtual void Search(const string & filePath, const string & pattern) = 0;
};