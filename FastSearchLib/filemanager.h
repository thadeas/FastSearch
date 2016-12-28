#pragma once
#include "stdafx.h"
#include "filemanager_intf.h"

using namespace std;

class CFileManager
	: public IFileManager
{
public:
	CFileManager();

	void Initialize(const wstring & path);

	// \copydoc IFileManager::GetNextFile
	bool GetNextFile(wstring & path) override;

protected:

	// Gets a list of subdirectories under a specified path
	// \param[out] output Empty vector to be filled with result
	// \param[in]  path   Input path, may be a relative path from working dir
	void CFileManager::GetSubdirs(vector<wstring>& output, const wstring& path);

	// Gets a list of subdirectory and their subdirs under a specified path
	// \param[out] output Empty vector to be filled with result
	// \param[in]  path   Input path, may be a relative path from working dir
	// \param[in]  prependStr String to be pre-appended before each result
	//                        for top level path, this should be an empty string
	void GetSubdirsRecursive(vector<wstring>& output, const wstring& path, const wstring& prependStr);

protected:
	size_t          m_pathsIndex = 0;   // current file path
	vector<wstring> m_paths;    // vector with the file paths

public:
	// this struct is used for creating object.
	struct Factory {
		/* Creates instance of CFileManager object
		param[out] spFileManager instance of CFileManager
		param[in] path Path to be searched for files.
		*/
		virtual void CreateFileManager(shared_ptr<IFileManager> & spFileManager, const wstring & path);
	};
};
