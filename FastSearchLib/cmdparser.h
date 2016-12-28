#pragma once
#include "stdafx.h"
#include "cmdparser_intf.h"

class CCmdParser : public ICmdParser
{
public:
	// method initializes object (parse arguments from input)
	void Initialize(int argc, char* argv[]);

public:
	// \copydoc ICmdParser::GetSearchPath
	wstring GetSearchPath() override;

	// \copydoc ICmdParser::GetPattern
	string GetPattern() override;

public:
	// this struct is used for creating object.
	struct Factory {
		/* Creates instance of CCmdParser object
		   param[out] spCmdParser instance of CCmdParser
		   param[in] argc number of arguments from command line
		   param[in] argv vector of arguments from command line
		*/
		virtual void CreateCmdParser(shared_ptr<ICmdParser> & spCmdParser, int argc, char* argv[]);
	};

private:
	wstring m_searchPath;    // file or directory to be searched
	string m_pattern;       // search pattern 
};
