#pragma once
#include <vector>

using namespace std;

/* this contains one part (buffer) of the file which is processed by a single thread
*/
class IFileChunk
{
public:
	virtual ~IFileChunk() {}

public:
	// get offset of the chunk buffer in the file
	virtual size_t FileOffset() const = 0;

	// size of block buffer
	virtual size_t Size() const = 0;

	// returns char on specific index in chunk buffer; otherwise it returns INVALID_BUFFER_CHARACTER ('\0')
	virtual char operator[] (long index) const = 0;
};
