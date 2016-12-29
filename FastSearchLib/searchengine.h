#pragma once
#include "stdafx.h"
#include "searchengine_intf.h"
#include "filechunk.h"
#include "kmplps.h"
#include "chunkwrapper.h"
#include "kmpsearch.h"

class CSearchEngine 
	: public ISearchEngine
	, protected CFileChunk::Factory
	, protected CChunkWrapper::Factory
	, protected CKmpLps::Factory
	, protected CKmpSearch::Factory
{
public:
	// Initialize search engine class
	// param[in] pattern Searched string.
	void Initialize(const string & pattern);

	// \copydoc ISearchEngine::Search
	void Search(const wstring & filePath) override;

protected:
	// get full path to the file and separate file name (also it coverts wstring to string)
	wstring GetFileName(const wstring& filePath);

protected:
	string m_pattern;    // pattern to be searched
	TKmpLps m_lps;       // preprocessed lps in KMP algorithm search

public:
	// this struct is used for creating object.
	struct Factory {
		/* Creates instance of CSearchEngine object
		\param[out] spSearchEngine instance of CSearchEngine
		\param[in] pattern search pattern
		*/
		virtual void CreateSearchEngine(shared_ptr<ISearchEngine> & spSearchEngine, const string & pattern);
	};
};
