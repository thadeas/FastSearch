#include "stdafx.h"
#include "filebuffer.h"

using namespace std;

CFileBuffer::CFileBuffer(shared_ptr<IFileChunk> spChunkPrev,
	shared_ptr<IFileChunk> spChunkCurrent,
	shared_ptr<IFileChunk> spChunkNext)
	: m_spChunkPrev(spChunkPrev)
	, m_spChunkCurrent(spChunkCurrent)
	, m_spChunkNext(spChunkNext)
	, m_bufferSize(m_spChunkCurrent->Size())
{
}

size_t CFileBuffer::FileOffset() const
{
	return m_spChunkCurrent->FileOffset();
}

size_t CFileBuffer::Size() const
{
	return m_spChunkCurrent->Size();
}

char CFileBuffer::operator[](long index) const
{
	if (0 <= index && index < m_bufferSize) {
		// return char from current chunk
		return m_spChunkCurrent->operator[](index);
	}
	else if (index >= m_bufferSize && m_spChunkNext != nullptr) {
		// return char from next chunk
		return m_spChunkNext->operator[](index - m_bufferSize);
	}
	else if (index < 0 && m_spChunkPrev != nullptr) {
		// return char from previos chunk
		return m_spChunkPrev->operator[](m_spChunkPrev->Size() + index);
	}
	
	else {
		return INVALID_BUFFER_CHARACTER;
	}
}

bool CFileBuffer::IsFirst() const
{
	return m_spChunkPrev == nullptr;
}

bool CFileBuffer::IsLast() const
{
	return m_spChunkNext == nullptr;
}

void CFileBuffer::Factory::CreateFileBuffer(shared_ptr<IFileBuffer>& spFileBuffer, shared_ptr<IFileChunk> spChunkPrev, shared_ptr<IFileChunk> spChunkCurrent, shared_ptr<IFileChunk> spChunkNext)
{
	shared_ptr<CFileBuffer> spImpl = make_shared<CFileBuffer>(spChunkPrev, spChunkCurrent, spChunkNext);
	spFileBuffer = spImpl;
}
