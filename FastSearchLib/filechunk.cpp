#include "stdafx.h"
#include "filechunk.h"

using namespace std;

CFileChunk::CFileChunk()
	: m_buffer(MAX_CHUNK_SIZE, 0)
	, m_bufferSize(0)
{

}

void CFileChunk::Initialize(vector<char> & buffer, size_t bufferSize, size_t bufferOffset)
{
	m_buffer.reserve(buffer.size());
	m_buffer.swap(buffer);
	m_bufferSize = min(bufferSize, m_buffer.size());   // real buffer size is minimum of this
	m_bufferOffset = bufferOffset;
}

size_t CFileChunk::Size()
{
	return m_bufferSize;
}

char CFileChunk::operator[](size_t index)
{
	if (index < 0 || index >= m_bufferSize) {
		return '\0';
	}
	else {
		return m_buffer[index];
	}
	
}

void CFileChunk::Factory::CreateFileChunk(shared_ptr<IFileChunk> & spFileChunk, vector<char> & buffer, size_t bufferSize, size_t bufferOffset)
{
	shared_ptr<CFileChunk> spImpl = make_shared<CFileChunk>();
	spImpl->Initialize(buffer, bufferSize, bufferOffset);
	spFileChunk = spImpl;
}
