#pragma once
#include "stdafx.h"
#include "filebuffer_intf.h"
#include "filechunk_intf.h"

using namespace std;

class CFileBuffer 
	: public IFileBuffer
{
public:
	// constructor
	// \param[in] spChunkPrev Previous chunk in file.
	// \param[in] spChunkCurrent Current chunk in file.
	// \param[in] spChunkNext Next chunk in file.
	explicit CFileBuffer(shared_ptr<IFileChunk> spChunkPrev,
		shared_ptr<IFileChunk> spChunkCurrent,
		shared_ptr<IFileChunk> spChunkNext);

public:
	// \copydoc IFileBuffer::FileOffset
	size_t FileOffset() const override;

	// \copydoc IFileBuffer::Size
	size_t Size() const override;

	// \copydoc IFileBuffer::operator[]
	char operator[] (long index) const override;

	// \copydoc IFileBuffer::IsFirst
	bool IsFirst() const override;

	// \copydoc IFileBuffer::IsLast
	bool IsLast() const override;

protected:
	// shared pointer to the previous, current and next file chunk
	// previous can be nullptr for the first chunk in the file, next can be nullptr for the last chunk in the file.
	shared_ptr<IFileChunk> m_spChunkPrev, m_spChunkCurrent, m_spChunkNext;

	long m_bufferSize;    // current buffer size
public:
	// this struct is used for creating object.
	struct Factory {
		/* Creates instance of CFileBuffer object
		\param[out] spFileBuffer instance of CFileBuffer
		\param[in] spChunkPrev Previous chunk in file.
		\param[in] spChunkCurrent Current chunk in file.
		\param[in] spChunkNext Next chunk in file
		*/
		virtual void CreateFileBuffer(shared_ptr<IFileBuffer> & spFileBuffer,
			shared_ptr<IFileChunk> spChunkPrev,
			shared_ptr<IFileChunk> spChunkCurrent,
			shared_ptr<IFileChunk> spChunkNext);
	};
};
