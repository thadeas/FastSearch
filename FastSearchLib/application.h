#pragma once
#include "stdafx.h"
#include "cmdparser.h"
#include "fsexecutor.h"
#include "searchengine.h"

using namespace std;

/*
Main class for fast search application
*/
class CApplication
	: protected CCmdParser::Factory
	, protected CFSExecutor::Factory
	, protected CSearchEngine::Factory
	, protected IFSExecutor::IExecuteOperation
{
public:

	/* Initializes object
	\param[in] argc number of arguments from command line
	\param[in] argv vector of arguments from command line
	*/
	void Initialize(int argc, char* argv[]);

	// Execute application
	void Run();

protected:
	// \copydoc IFSExecutor::IExecuteOperation::Execute
	void Execute(const wstring & filePath) override;

protected:
	shared_ptr<IFSExecutor> m_spFSExecutor;        // file system executor
	shared_ptr<ISearchEngine> m_spSearchEngine;    // search engine class
};

