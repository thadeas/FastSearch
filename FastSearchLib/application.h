#pragma once
#include "stdafx.h"
#include "cmdparser.h"

using namespace std;

/*
Main class for fast search application
*/
class CApplication
	: protected CCmdParser::Factory
{
public:

	/* Initializes object
	\param[in] argc number of arguments from command line
	\param[in] argv vector of arguments from command line
	*/
	void Run(int argc, char* argv[]);
};

