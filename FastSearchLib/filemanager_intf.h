#pragma once
#include <vector>

using namespace std;

class IFileManager {
public:
	/* return file(s) from the path
	  if path is invalid - result is empty vector
	  if path is valid file path result will be only one file
	  if path is directory result will be 
	  \param[in] path Path to the file or directory
	*/
	virtual vector<string> GetFiles(const string & path) = 0;
};
