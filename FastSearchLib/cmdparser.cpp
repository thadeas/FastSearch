#include "stdafx.h"
#include "cmdparser.h"

// number of arguments from input (exe path + 2 arguments)
static const int ARGUMENT_COUNT = 3;
// index of path argument
static const int ARGUMENT_PATH_INDEX = 1;
// index of pattern argument
static const int ARGUMENT_PATTERN_INDEX = 2;

void CCmdParser::Initialize(int argc, char* argv[])
{
	// fail input with less arguments
	if (argc < ARGUMENT_COUNT) {
		throw invalid_argument("Received invalid number of arguments.");
	}
	m_searchPath = argv[ARGUMENT_PATH_INDEX];
	m_pattern = argv[ARGUMENT_PATTERN_INDEX];
}

string CCmdParser::GetSearchPath()
{
	return m_searchPath;
}

string CCmdParser::GetPattern()
{
	return m_pattern;
}

void CCmdParser::Factory::CreateCmdParser(shared_ptr<ICmdParser> & spCmdParser, int argc, char* argv[])
{
	shared_ptr<CCmdParser> spImpl = make_shared<CCmdParser>();
	spImpl->Initialize(argc, argv);
	spCmdParser = spImpl;
}
