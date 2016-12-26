#include "stdafx.h"
#include "fspathwrapper.h"

using namespace std;

void CFsPathWrapper::Factory::CreateFsPathWrapper(shared_ptr<IFsPathWrapper> & spFsPathWrapper)
{
	shared_ptr<CFsPathWrapper> spImpl = make_shared<CFsPathWrapper>();
	spFsPathWrapper = spImpl;
}

bool CFsPathWrapper::IsValid(const string & path)
{
	return false;
}

bool CFsPathWrapper::IsDirectory(const string & path)
{
	return false;
}

vector<string> CFsPathWrapper::GetFilesInDir(const string & path)
{
	return vector<string>();
}
