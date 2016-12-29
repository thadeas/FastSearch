#include "stdafx.h"
#include "searchengine.h"

using namespace std;

void CSearchEngine::Initialize(const string & pattern)
{
	m_pattern = pattern;
	shared_ptr<IKmpLps> spKmpLps;
	CreateKmpLps(spKmpLps);
	m_lps = spKmpLps->Compute(pattern);
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

void CSearchEngine::Search(const wstring & filePath)
{
	try {
		ifstream file;
		file.open(filePath, ios::binary | ios::in);
		if (file.is_open()) {
			// zero base fill output
			wcout.fill(L'0');

			wstring fileName = GetFileName(filePath);
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

				if (spFileChunkCurrent) {
					shared_ptr<IChunkWrapper> spBuffer;
					CreateChunkWrapper(spBuffer, spFileChunkPrev, spFileChunkCurrent, spFileChunkNext);
					shared_ptr<IKmpSearch> spKmpSearch;
					CreateKmpSearch(spKmpSearch, m_pattern, m_lps, spBuffer);
					IKmpSearch::TSearchResults searchResults = spKmpSearch->Run();
					for (const auto & result : searchResults) {
						wcout << fileName << L"(" << setw(10) << result.position << L"): "
							<< string_to_wstring(result.prefix) << L"..." << string_to_wstring(result.sufix) << L"\n";
					}
				}
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
