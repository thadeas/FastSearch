#pragma once
#include "stdafx.h"
#include "chunkwrapper_intf.h"
#include "filechunk_intf.h"

using namespace std;

class CChunkWrapper 
	: public IChunkWrapper
{
public:
	// constructor
	// \param[in] spChunkPrev Previous chunk in file.
	// \param[in] spChunkCurrent Current chunk in file.
	// \param[in] spChunkNext Next chunk in file.
	explicit CChunkWrapper(shared_ptr<IFileChunk> spChunkPrev,
		shared_ptr<IFileChunk> spChunkCurrent,
		shared_ptr<IFileChunk> spChunkNext);

public:
	// \copydoc IChunkWrapper::FileOffset
	size_t FileOffset() const override;

	// \copydoc IChunkWrapper::Size
	size_t Size() const override;

	// \copydoc IChunkWrapper::operator[]
	char operator[] (long index) const override;

	// \copydoc IChunkWrapper::IsFirst
	bool IsFirst() const override;

	// \copydoc IChunkWrapper::IsLast
	bool IsLast() const override;

protected:
	// shared pointer to the previous, current and next file chunk
	// previous can be nullptr for the first chunk in the file, next can be nullptr for the last chunk in the file.
	shared_ptr<IFileChunk> m_spChunkPrev, m_spChunkCurrent, m_spChunkNext;

	long m_bufferSize;    // current buffer size
public:
	// this struct is used for creating object.
	struct Factory {
		/* Creates instance of CChunkWrapper object
		\param[out] spFileManager instance of CChunkWrapper
		\param[in] spChunkPrev Previous chunk in file.
		\param[in] spChunkCurrent Current chunk in file.
		\param[in] spChunkNext Next chunk in file
		*/
		virtual void CreateChunkWrapper(shared_ptr<IChunkWrapper> & spChunkWrapper,
			shared_ptr<IFileChunk> spChunkPrev,
			shared_ptr<IFileChunk> spChunkCurrent,
			shared_ptr<IFileChunk> spChunkNext);
	};
};
