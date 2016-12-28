#include "stdafx.h"
#include "filemanager.h"
#include <windows.h>
#include <shlwapi.h>

using namespace std;

CFileManager::CFileManager()
	: m_pathsIndex(0)
{

}

void CFileManager::Initialize(const wstring & path)
{
	if (PathFileExists(path.c_str())) {
		// add file to the output list
		m_paths.push_back(path);
	}
	else {
		// create directory path
		GetSubdirsRecursive(m_paths, path, wstring());
	}
	
	m_pathsIndex = 0;
}

bool CFileManager::GetNextFile(wstring & path)
{
	if (m_pathsIndex < m_paths.size()) {
		path.swap(m_paths[m_pathsIndex++]);
		return true;
	}
	return false;   // no result
}

void CFileManager::Factory::CreateFileManager(shared_ptr<IFileManager> & spFileManager, const wstring & path)
{
	shared_ptr<CFileManager> spImpl = make_shared<CFileManager>();
	spImpl->Initialize(path);
	spFileManager = spImpl;
}


void CFileManager::GetSubdirs(vector<wstring>& output, const wstring& path)
{
	WIN32_FIND_DATA findfiledata;
	HANDLE hFind = INVALID_HANDLE_VALUE;

	wchar_t fullpath[MAX_PATH];
	GetFullPathName(path.c_str(), MAX_PATH, fullpath, 0);
	wstring fp(fullpath);

	hFind = FindFirstFile((LPCWSTR)(fp + L"\\*").c_str(), &findfiledata);
	if (hFind == INVALID_HANDLE_VALUE) {
		// ToDo Invalid path error.
	} else {
		do {
			if ((findfiledata.dwFileAttributes | FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY
				&& (findfiledata.cFileName[0] != '.'))
			{
				output.push_back(findfiledata.cFileName);
			}
		} while (FindNextFile(hFind, &findfiledata) != 0);
	}
}

void CFileManager::GetSubdirsRecursive(vector<wstring>& output, const wstring& path, const wstring& prependStr)
{
	vector<wstring> firstLvl;
	GetSubdirs(firstLvl, path);
	for (const auto & item : firstLvl) {
		output.push_back(prependStr + item);
		GetSubdirsRecursive(output, path + PATH_SEPARATOR + item + PATH_SEPARATOR, prependStr + item + PATH_SEPARATOR);
	}
}
