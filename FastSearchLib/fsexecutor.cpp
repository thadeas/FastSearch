#include "stdafx.h"
#include "fsexecutor.h"
#include <windows.h>
#include <shlwapi.h>

using namespace std;

CFSExecutor::CFSExecutor()
{

}

void CFSExecutor::Initialize(const wstring & path)
{
	if (!PathFileExists(path.c_str())) {
		stringstream message;
		message << "Received invalid path (" << wstring_to_string(path) << ").\n";
		throw invalid_argument(message.str());
	}
	m_path = path;
}

void CFSExecutor::Execute()
{
	DWORD atributes = GetFileAttributes(m_path.c_str());
	if (atributes & FILE_ATTRIBUTE_DIRECTORY) {
		// create directory path
		vector<wstring> rootLvl;
		GetSubdirsRecursive(rootLvl, m_path, wstring());
	}
	else {
		// execute callback method on single
		m_spExecuteOperation->Execute(m_path);
	}
}


void CFSExecutor::RegisterCallback(IExecuteOperation * executeOperation)
{
	m_spExecuteOperation = executeOperation;
}

void CFSExecutor::Factory::CreateFSExecutor(shared_ptr<IFSExecutor> & spFsExecutor, const wstring & path)
{
	shared_ptr<CFSExecutor> spImpl = make_shared<CFSExecutor>();
	spImpl->Initialize(path);
	spFsExecutor = spImpl;
}


void CFSExecutor::GetSubdirs(vector<wstring>& output, const wstring& path)
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
			if (findfiledata.cFileName[0] != L'.') {
				if (findfiledata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
					output.push_back(findfiledata.cFileName);
				}
				else {
					// execute callback method on file
					m_spExecuteOperation->Execute(path + PATH_SEPARATOR + findfiledata.cFileName);
				}
			}
		} while (FindNextFile(hFind, &findfiledata) != 0);
	}
}

void CFSExecutor::GetSubdirsRecursive(vector<wstring>& output, const wstring& path, const wstring& prependStr)
{
	vector<wstring> firstLvl;
	GetSubdirs(firstLvl, path);
	for (const auto & item : firstLvl) {
		output.push_back(prependStr + item);
		GetSubdirsRecursive(output, path + PATH_SEPARATOR + item + PATH_SEPARATOR, prependStr + item + PATH_SEPARATOR);
	}
}
