#pragma once
#include "stdafx.h"
#include "fspathwrapper_intf.h"

class CFsPathWrapper 
	: public IFsPathWrapper 
{
public:
	// \copydoc IFsPathWrapper::IsValid
	bool IsValid(const string & path) override;

	// \copydoc IFsPathWrapper::IsDirectory
	bool IsDirectory(const string & path) override;

	// \copydoc IFsPathWrapper::GetFilesInDir
	vector<string> GetFilesInDir(const string & path) override;

public:
	// this struct is used for creating object.
	struct Factory {
		/* Creates instance of object
		param[out] spFsPathWrapper instance of CFsPathWrapper
		*/
		virtual void CreateFsPathWrapper(shared_ptr<IFsPathWrapper> & spFsPathWrapper);
	};
};
