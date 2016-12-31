#pragma once

#include <vector>
#include "..\filebuffer_intf.h"
#include "..\common.h"

using namespace std;

class CFileBufferFake : public IFileBuffer {

public:
	size_t FileOffset() const override
	{
		return m_fileOffset;
	}

	virtual size_t Size() const override
	{
		return m_bufferCurrent.size();
	}

	char operator[] (long index) const override
	{
		if (0 <= index && index < (long)m_bufferCurrent.size()) {
			return m_bufferCurrent[index];
		}
		else if (index >= (long)m_bufferCurrent.size() && !m_bufferNext.empty()) {
			long nextIndex = index - m_bufferCurrent.size();
			if (0 <= nextIndex && nextIndex < (long)m_bufferNext.size()) {
				return m_bufferNext[nextIndex];
			}
			else {
				return INVALID_BUFFER_CHARACTER;
			}
			
		}
		else if (index < 0 && !m_bufferPrev.empty()) {
			long prevIndex = index - m_bufferCurrent.size();
			if (0 <= prevIndex && prevIndex < (long)m_bufferPrev.size()) {
				return m_bufferPrev[prevIndex];
			}
			else {
				return INVALID_BUFFER_CHARACTER;
			}

			return m_bufferPrev[m_bufferPrev.size() + index];
		}

		else {
			return INVALID_BUFFER_CHARACTER;
		}
	}

	bool IsFirst() const override
	{
		return m_bufferPrev.empty();
	}

	bool IsLast() const override
	{
		return m_bufferNext.empty();
	}

	size_t m_fileOffset = 0;
	vector<char> m_bufferPrev, m_bufferCurrent, m_bufferNext;
};
