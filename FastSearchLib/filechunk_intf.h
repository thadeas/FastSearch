#pragma once
#include <vector>

using namespace std;

/* this contain one part (buffer) of the file which is processed by a single thread

*/
class IFileChunk
{
public:
	static const char INVALID_BUFFER_CHARACTER = '\0';

	// size of block buffer
	virtual size_t Size() = 0;

	// returns char on specific index in chunk buffer; otherwise it returns INVALID_BUFFER_CHARACTER ('\0')
	virtual char operator[] (size_t index) = 0;
};
