#pragma once
#include <string>

using namespace std;

/* This interface search for pattern inside file
*/
class ISearchEngine {
public:
	virtual ~ISearchEngine() {}

public:

	/* Search for all patterns in file
	   param[in] filePath File to be searched.
	*/
	virtual void Search(const wstring & filePath) = 0;
};