#include "pch.h"
#include "SendBuffer.h"

SendBuffer::SendBuffer(const int32_t numOfBytes)
{
	m_buffer.reserve(numOfBytes);
}

SendBuffer::~SendBuffer()
{
	m_buffer.clear();
}

void SendBuffer::CopyData(IN const void* data, IN const int32_t size)
{
	::memcpy(m_buffer.data(), data, size);
	m_writePos += size;
}
