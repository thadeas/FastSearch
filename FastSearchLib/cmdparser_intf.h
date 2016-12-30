#pragma once
#include <string>

using namespace std;

/*
 This class parse command line and do basic checks on it
*/
class ICmdParser
{
public:
	virtual ~ICmdParser() {}

public:
	// returns path parsed and validated from the command line
	virtual wstring GetSearchPath() = 0;

	// return pattern parsed from command line
	virtual string GetPattern() = 0;
};
