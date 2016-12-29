#include "stdafx.h"
#include "cmdparser.h"

// number of arguments from input (2 arguments)
static const int ARGUMENT_COUNT = 2;
// index of path argument
static const int ARGUMENT_PATH_INDEX = 1;
// index of pattern argument
static const int ARGUMENT_PATTERN_INDEX = 2;

void CCmdParser::Initialize(int argc, char* argv[])
{
	// fail input with less arguments
	if (argc < ARGUMENT_COUNT + 1) {
		stringstream message;
		message << "Received invalid number (" << argc << ") of arguments from command line. Expected " << ARGUMENT_COUNT << ".\n";
		throw invalid_argument(message.str());
	}

	m_searchPath = string_to_wstring(argv[ARGUMENT_PATH_INDEX]);
	m_pattern = argv[ARGUMENT_PATTERN_INDEX];
	// check params
	if (m_pattern.size() > MAXIMUM_PATTERN_LENGTH) {
		stringstream message;
		message << "Pattern '" << m_pattern << " is longer than expected. Max. length is " << MAXIMUM_PATTERN_LENGTH << ".\n";
		throw invalid_argument(message.str());
	}
}

wstring CCmdParser::GetSearchPath()
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
