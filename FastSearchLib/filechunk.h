#pragma once
#include "stdafx.h"
#include "filechunk_intf.h"

using namespace std;

class CFileChunk 
	: public IFileChunk
{
public:
	CFileChunk();

	// Initializes CFileChunk
	// \param[in] buffer Buffer loaded from input file (part of the file)
	// \param[in] bufferSize Real size of the buffer.
	void Initialize(vector<char> & buffer, size_t bufferSize);

public:
	// \copydoc IFileChunk::Size
	size_t Size() override;

	// \copydoc IFileChunk::operator[]
	char operator[] (size_t index) override;

protected:
	// members
	size_t m_bufferSize;     // buffer length (read form input)
	vector<char> m_buffer;   // vector of bytes from input stream

public:
	// this struct is used for creating object.
	struct Factory {
		/* Creates instance of CFileChunk object
		param[out] spFileManager instance of CFileChunk
		param[in/out] buffer input buffer for chunk. WARNING - input buffer is swapped, because it is faster.
		param[in] bufferSize real size of input buffer
		*/
		virtual void CreateFileChunk(shared_ptr<IFileChunk> & spFileChunk, vector<char> & buffer, const size_t bufferSize);
	};

};

