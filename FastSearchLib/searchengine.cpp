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

		// read from file and create separate chunks
		vector<char> buffer(MAX_CHUNK_SIZE);
		while (file.read(&buffer[0], buffer.size())) {
			shared_ptr<IFileChunk> spFileChunk;
			CreateFileChunk(spFileChunk, buffer, (size_t)file.gcount());

			///do with buffer
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
