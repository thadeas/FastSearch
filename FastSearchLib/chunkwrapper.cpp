#include "stdafx.h"
#include "chunkwrapper.h"

using namespace std;

CChunkWrapper::CChunkWrapper(shared_ptr<IFileChunk>& spChunkPrev,
	shared_ptr<IFileChunk>& spChunkCurrent,
	shared_ptr<IFileChunk>& spChunkNext)
	: m_spChunkPrev(spChunkPrev)
	, m_spChunkCurrent(spChunkCurrent)
	, m_spChunkNext(spChunkNext)
	, m_bufferSize(m_spChunkCurrent->Size())
{
}

size_t CChunkWrapper::FileOffset() const
{
	return m_spChunkCurrent->FileOffset();
}

size_t CChunkWrapper::Size() const
{
	return m_spChunkCurrent->Size();
}

char CChunkWrapper::operator[](long index) const
{
	if (0 <= index && index < m_bufferSize) {
		return m_spChunkCurrent->operator[](index);
	}
	else if (index >= m_bufferSize && m_spChunkNext != nullptr) {
		return m_spChunkNext->operator[](index + 1 - m_bufferSize);
	}
	else if (index < 0 && m_spChunkPrev != nullptr) {
		return m_spChunkPrev->operator[](m_spChunkPrev->Size() + index);
	}
	
	else {
		return INVALID_BUFFER_CHARACTER;
	}
}

bool CChunkWrapper::IsFirst() const
{
	return m_spChunkPrev == nullptr;
}

bool CChunkWrapper::IsLast() const
{
	return m_spChunkNext == nullptr;
}

void CChunkWrapper::Factory::CreateChunkWrapper(shared_ptr<IChunkWrapper>& spChunkWrapper, shared_ptr<IFileChunk>& spChunkPrev, shared_ptr<IFileChunk>& spChunkCurrent, shared_ptr<IFileChunk>& spChunkNext)
{
	shared_ptr<CChunkWrapper> spImpl = make_shared<CChunkWrapper>(spChunkPrev, spChunkCurrent, spChunkNext);
	spChunkWrapper = spImpl;
}
