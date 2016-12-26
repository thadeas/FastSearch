#pragma once
#include "stdafx.h"
#include "filemanager_intf.h"
#include "fspathwrapper.h"

using namespace std;

class CFileManager
	: public IFileManager
	, protected CFsPathWrapper::Factory
{
public:
	// \copydoc IFileManager::GetFiles
	vector<string> GetFiles(const string & path) override;

protected:
	shared_ptr<IFsPathWrapper> m_spFsPathWrapper;

public:
	// this struct is used for creating object.
	struct Factory {
		/* Creates instance of CCmdParser object
		param[out] spFileManager instance of CFileManager
		*/
		virtual void CreateFileManager(shared_ptr<IFileManager> & spFileManager);
	};
};
