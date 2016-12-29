#pragma once
#include <vector>

using namespace std;

/* Iterate through the selected path and find results in every single file
*/
class IFileManager {
public:
	/* return next file to be processed. Internally it holds the position in the directory tree.
	  \param[out] path Path to the file
	  \ return true if next file is found. Return false if there is no file to be processed.
	*/
	virtual bool GetNextFile(wstring & path) = 0;
};
