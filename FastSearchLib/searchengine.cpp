#include "stdafx.h"
#include "searchengine.h"

using namespace std;

void CSearchEngine::Initialize(const string & pattern)
{
	m_pattern = pattern;
}

void CSearchEngine::Search(const wstring & filePath)
{
	try {
		ifstream file;
		file.open(filePath, ios::binary | ios::in);
		if (file.is_open()) {

			// read from file and create separate chunks
			vector<char> buffer(MAX_CHUNK_SIZE);
			// ToDo: create chunk pool - released chunk can be used again
			shared_ptr<IFileChunk> spFileChunkPrev, spFileChunkCurrent, spFileChunkNext;
			while (!file.eof()) {
				auto currentPos = file.tellg();
				file.read(&buffer[0], buffer.size());

				// this method move chunks shared pointers from next -> current -> prev -> delete()
				spFileChunkPrev = spFileChunkCurrent;
				spFileChunkCurrent = spFileChunkNext;

				CreateFileChunk(spFileChunkNext, buffer, (size_t)file.gcount(), (size_t)currentPos);
			}
			if (spFileChunkNext) {
				// process th 
			}
			file.close();
		}

	}
	catch (...) {
		// ToDo: invalid operation on file
	}

}

void CSearchEngine::Factory::CreateSearchEngine(shared_ptr<ISearchEngine>& spSearchEngine, const string & pattern)
{
	shared_ptr<CSearchEngine> spImpl = make_shared<CSearchEngine>();
	spImpl->Initialize(pattern);
	spSearchEngine = spImpl;

}
