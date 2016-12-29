#pragma once

#include <vector>

using namespace std;

/* this interface provides access to the buffer on the relative position in the file (wraps one file chunk). 
   Buffer can get characters from the chunks next to current chunk. So chunk[-3] or chunk[chunk.Size() + 2] is valid and return value.
*/
class IChunkWrapper {
public:
	// offset of the buffer in the file
	virtual size_t FileOffset() const = 0;

	// size of buffer
	virtual size_t Size() const = 0;

	// get char from chunk buffer
	virtual char operator[] (long index) const = 0;

	// chunk is first in the file
	virtual bool IsFirst() const = 0;

	// chunk is last in the file
	virtual bool IsLast() const = 0;
};
