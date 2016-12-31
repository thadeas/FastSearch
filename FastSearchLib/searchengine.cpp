#include "stdafx.h"
#include "searchengine.h"
#include <future>

using namespace std;

// synchronize every FLUSH_RESULT futures with main thread
static const long FLUSH_RESULT = 100;

void CSearchEngine::Initialize(const string & pattern)
{
	m_pattern = pattern;
	shared_ptr<IKmpLps> spKmpLps;
	CreateKmpLps(spKmpLps);
	m_lps = spKmpLps->Compute(pattern);
}

void CSearchEngine::Search(const wstring & filePath)
{
	try {
		ifstream file;
		file.open(filePath, ios::binary | ios::in);
		if (file.is_open()) {
			// zero base fill output
			wcout.fill(L'0');

			wstring fileName = GetFileName(filePath);
			//////////////////////////////////////////////////////////////////////////
			// sequentially read the whole file and store it into separate chunks (buffers)
			// KMP search algorithm get 3 chunks (previous chunk, current chunk, and next chunk)
			// it search only in current chunk
			//////////////////////////////////////////////////////////////////////////
			vector<char> buffer(CHUNK_SIZE);
			shared_ptr<IFileChunk> spFileChunkPrev, spFileChunkCurrent, spFileChunkNext;
			vector<future<IKmpSearch::TSearchResults>> futures;
			long flushResultCounter = 0;
			while (!file.eof()) {
				auto bufferOffset = file.tellg();
				file.read(&buffer[0], buffer.size());
				MoveChunks(spFileChunkPrev, spFileChunkCurrent, spFileChunkNext);

				// chunk is held in shared ptr so when nobody holds this chunk it will be released. 
				// Shared pointers are thread safe so we don't need any extra locking to ensure thread-safe chunk release.
				CreateFileChunk(spFileChunkNext, buffer, (size_t)file.gcount(), (size_t)bufferOffset);
				if (spFileChunkCurrent) {
					IFileBuffer * pBuffer = new CFileBuffer(spFileChunkPrev, spFileChunkCurrent, spFileChunkNext);
					// ---------------------------------------
					// do it in parallel ---------------------
					// ---------------------------------------
					futures.push_back(async([this, pBuffer]() { return SearchTask(pBuffer); }));
				}

				// ---------------------------------------
				// flush results
				// ---------------------------------------
				if ( ++flushResultCounter >= FLUSH_RESULT) {
					flushResultCounter = 0;
					// handle results
					SynchronizeFuturesIntoOutput(futures, fileName);
				}
				
			}   // end while (!file.eof())
			// ---------------------------------------
			// process the last chunk
			// ---------------------------------------
			if (spFileChunkNext) {
				MoveChunks(spFileChunkPrev, spFileChunkCurrent, spFileChunkNext);
				spFileChunkNext = nullptr;   // there is no chunk on the right
				IFileBuffer * pBuffer = new CFileBuffer(spFileChunkPrev, spFileChunkCurrent, spFileChunkNext);
				// do it in parallel
				futures.push_back( async([this, pBuffer]() { return SearchTask(pBuffer); }));
			}
			// handle results
			SynchronizeFuturesIntoOutput(futures, fileName);

			file.close();
		}

	}
	catch (...) {
		// ToDo: invalid operation on file
	}

}


wstring CSearchEngine::GetFileName(const wstring& filePath)
{
	// string filePathStr = wstring_to_string(path);
	size_t index = filePath.rfind(PATH_SEPARATOR, filePath.size());
	if (index != wstring::npos) {
		return filePath.substr(index + 1, filePath.size() - index);
	}
	else {
		return filePath;
	}
}

IKmpSearch::TSearchResults CSearchEngine::SearchTask(IFileBuffer * pBuffer)
{
	shared_ptr<IKmpSearch> spKmpSearch;
	CreateKmpSearch(spKmpSearch, m_pattern, m_lps);
	auto result = spKmpSearch->Process(pBuffer);
	delete pBuffer;
	return result;
}

void CSearchEngine::SynchronizeFuturesIntoOutput(vector<future<IKmpSearch::TSearchResults>> & futures, const wstring & fileName)
{
	for (auto & searchResults : futures) {
		for (const auto & result : searchResults.get()) {
			wcout << fileName << L"(" << setw(12) << result.position << L"): "
				<< string_to_wstring(result.prefix) << L"..." << string_to_wstring(result.sufix) << L"\n";
		}
	}
	futures.clear();
}

void CSearchEngine::MoveChunks(shared_ptr<IFileChunk> &spFileChunkPrev, shared_ptr<IFileChunk> &spFileChunkCurrent, shared_ptr<IFileChunk> spFileChunkNext)
{
	spFileChunkPrev = spFileChunkCurrent;
	spFileChunkCurrent = spFileChunkNext;
}

void CSearchEngine::Factory::CreateSearchEngine(shared_ptr<ISearchEngine>& spSearchEngine, const string & pattern)
{
	shared_ptr<CSearchEngine> spImpl = make_shared<CSearchEngine>();
	spImpl->Initialize(pattern);
	spSearchEngine = spImpl;

}
