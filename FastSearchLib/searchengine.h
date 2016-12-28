#pragma once
#include "stdafx.h"
#include "searchengine_intf.h"
#include "filechunk.h"

class CSearchEngine 
	: public ISearchEngine
	, protected CFileChunk::Factory
{
public:
	// Initialize search engine class
	// param[in] pattern Searched string.
	void Initialize(const string & pattern);

	// \copydoc ISearchEngine::Search
	void Search(const wstring & filePath) override;

protected:
	string m_pattern;    // pattern to be searched

public:
	// this struct is used for creating object.
	struct Factory {
		/* Creates instance of CSearchEngine object
		param[out] spSearchEngine instance of CSearchEngine
		*/
		virtual void CreateSearchEngine(shared_ptr<ISearchEngine> & spSearchEngine, const string & pattern);
	};
};
