#pragma once
#include <vector>

using namespace std;

/* Iterate through the selected path find, find all files and executes callback on it
*/

class IFSExecutor 
{
public:
	virtual ~IFSExecutor() {}
public:

	// callback class for executing operation on files in file system
	class IExecuteOperation {
	public:
		// callback method for execute operation on single file
		virtual void ExecuteOn(const wstring & filePath) = 0;
	};


public:
	/* iterate through the directory tree and searches for pattern
	*/
	virtual void Execute() = 0;

	/* register search callback. Next call of this method release previous callback holder.
	  \param[in] executeOnFile Callback class.
	*/
	virtual void RegisterCallback(IExecuteOperation * executeOperation) = 0;
};
