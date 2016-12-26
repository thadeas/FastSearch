#pragma once
#include <vector>

using namespace std;

/* Class wraps file system operations with file/directory path
*/
class IFsPathWrapper {
public:
	virtual bool IsValid(const string & path) = 0;

	virtual bool IsDirectory(const string & path) = 0;

	virtual vector<string> GetFilesInDir(const string & path) = 0;
};
