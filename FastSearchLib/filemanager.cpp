#include "stdafx.h"
#include "filemanager.h"

using namespace std;


vector<string> CFileManager::GetFiles(const string & path)
{
	if (!m_spFsPathWrapper->IsValid(path)) {
		throw invalid_argument("Path '" + path + "' is not valid");
	}
	
	if (m_spFsPathWrapper->IsDirectory(path)) {
		return m_spFsPathWrapper->GetFilesInDir(path);
	}
	else {
		// return just one file
		vector<string> files;
		files.push_back(path);
		return files;
	}
}

void CFileManager::Factory::CreateFileManager(shared_ptr<IFileManager> & spFileManager)
{
	shared_ptr<CFileManager> spImpl = make_shared<CFileManager>();
	spFileManager = spImpl;
}
