#pragma once
#include "stdafx.h"
#include "cmdparser.h"
#include "filemanager.h"
#include "searchengine.h"

using namespace std;

/*
Main class for fast search application
*/
class CApplication
	: protected CCmdParser::Factory
	, protected CFileManager::Factory
	, protected CSearchEngine::Factory
{
public:

	/* Initializes object
	\param[in] argc number of arguments from command line
	\param[in] argv vector of arguments from command line
	*/
	void Run(int argc, char* argv[]);
};

