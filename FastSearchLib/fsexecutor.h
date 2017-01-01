#pragma once
#include "stdafx.h"
#include "fsexecutor_intf.h"

using namespace std;

class CFSExecutor
	: public IFSExecutor
{
public:
	CFSExecutor();

	// Initialize class
	// \param[in] path Path to the file or directory
	void Initialize(const wstring & path);

public:

	// \copydoc IFSExecutor::Execute
	void Execute() override;

	// \copydoc IFSExecutor::RegisterCallback
	void RegisterCallback(IExecuteOperation * executeOperation) override;

protected:
	// Gets a list of subdirectories under a specified path
	// \param[out] output Empty vector to be filled with result
	// \param[in]  path   Input path, may be a relative path from working dir
	void CFSExecutor::GetSubdirs(vector<wstring>& output, const wstring& path);

	// Gets a list of subdirectory and their subdirs under a specified path
	// \param[out] output Empty vector to be filled with result
	// \param[in]  path   Input path, may be a relative path from working dir
	// \param[in]  prependStr String to be pre-appended before each result
	//                        for top level path, this should be an empty string
	void GetSubdirsRecursive(vector<wstring>& output, const wstring& path, const wstring& prependStr);

protected:
	wstring m_path;                                        // path to the file or directory
	IExecuteOperation * m_spExecuteOperation = nullptr;    // execute operation callback

public:
	// this struct is used for creating object.
	struct Factory {
		/* Creates instance of CFSExecutor object
		\param[out] spFSExecutor instance of CFSExecutor
		\param[in] path Path to dir of file to be searched
		*/
		virtual void CreateFSExecutor(shared_ptr<IFSExecutor> & spFSExecutor, const wstring & path);
	};
};
