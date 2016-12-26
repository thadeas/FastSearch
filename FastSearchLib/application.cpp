#include "stdafx.h"
#include "application.h"

void CApplication::Run(int argc, char* argv[])
{
	std::shared_ptr<ICmdParser> spCmdParser;
	CreateCmdParser(spCmdParser, argc, argv);
}
