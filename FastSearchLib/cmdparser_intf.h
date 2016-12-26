#pragma once
#include <string>

using namespace std;

/*
 This class parse command line input and return required values
*/
class ICmdParser
{
public:
	// returns path parsed and validated from the command line
	virtual string GetSearchPath() = 0;

	// return pattern parsed from command line
	virtual string GetPattern() = 0;
};
