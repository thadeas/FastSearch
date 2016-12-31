#pragma once
#include "stdafx.h"
#include <future>
#include "searchengine_intf.h"
#include "filechunk.h"
#include "kmplps.h"
#include "filebuffer.h"
#include "kmpsearch.h"

class CSearchEngine 
	: public ISearchEngine
	, protected CFileChunk::Factory
	, protected CFileBuffer::Factory
	, protected CKmpLps::Factory
	, protected CKmpSearch::Factory
{
public:
	// Initialize search engine class
	// param[in] pattern Searched string.
	void Initialize(const string & pattern);

	// \copydoc ISearchEngine::Search
	void Search(const wstring & filePath) override;

	void PrintResultsToOutput(future<IKmpSearch::TSearchResults> &searchResults, wstring fileName);

protected:
	// get full path to the file and separate file name (also it coverts wstring to string)
	wstring GetFileName(const wstring& filePath);

	// method move chunks shared pointers from next -> current -> prev -> delete()
	void MoveChunks(shared_ptr<IFileChunk> &spFileChunkPrev, shared_ptr<IFileChunk> &spFileChunkCurrent, shared_ptr<IFileChunk> spFileChunkNext);

	// method synchronize threads and send results to standard output
	// \param[in] futures list of futures
	// \param[in] filename currently processed file
	void SynchronizeFuturesIntoOutput(vector<future<IKmpSearch::TSearchResults>> & futures, const wstring & fileName);

	// process the parallel search and release unused buffer
	// param[in] pBuffer pointer to buffer
	IKmpSearch::TSearchResults SearchTask(IFileBuffer * pBuffer);

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
