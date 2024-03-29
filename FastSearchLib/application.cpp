#include "stdafx.h"
#include "application.h"

using namespace std;

void CApplication::Initialize(int argc, char* argv[])
{
	shared_ptr<ICmdParser> spCmdParser;
	CreateCmdParser(spCmdParser, argc, argv);
	CreateFSExecutor(m_spFSExecutor, spCmdParser->GetSearchPath());
	CreateSearchEngine(m_spSearchEngine, spCmdParser->GetPattern());

	// register callback for file system executor
	m_spFSExecutor->RegisterCallback(this);
}

void CApplication::Run()
{
	// search pattern on all files
	m_spFSExecutor->Execute();
}

void CApplication::ExecuteOn(const wstring & filePath)
{
	m_spSearchEngine->Search(filePath);
}
