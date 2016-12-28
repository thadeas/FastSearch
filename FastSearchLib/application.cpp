#include "stdafx.h"
#include "application.h"

using namespace std;

void CApplication::Run(int argc, char* argv[])
{
	shared_ptr<ICmdParser> spCmdParser;
	CreateCmdParser(spCmdParser, argc, argv);

	shared_ptr<IFileManager> spFileManager;
	CreateFileManager(spFileManager, spCmdParser->GetSearchPath());

	shared_ptr<ISearchEngine> spSearchEngine;
	CreateSearchEngine(spSearchEngine, spCmdParser->GetPattern());

	// search pattern in all files
	wstring filePath;
	while (spFileManager->GetNextFile(filePath)) {
		spSearchEngine->Search(filePath);
	}


}
