#include "pch.h"
#include "RecvBuffer.h"

RecvBuffer::RecvBuffer(IN const uint32_t bufferSize)
{
	m_capacity = BUFFER_COUNT;
	m_bufferSize = bufferSize;
	m_buffer.resize(bufferSize * m_capacity);
}


RecvBuffer::~RecvBuffer()
{
	m_buffer.clear();
}

bool RecvBuffer::OnRead(IN const int32_t numOfBytes)
{
	int dataSize = GetDataSize();
	if (numOfBytes > GetDataSize())
		return false;
	m_readPos += numOfBytes;
	return true;
}


bool RecvBuffer::OnWrite(IN const int32_t numOfBytes)
{
	if (numOfBytes > GetFreeSize())
	{
		return false;
	}

	m_writePos += numOfBytes;
	return true;
}


void RecvBuffer::Clean()
{
	int32_t dataSize = GetDataSize();
	if (0 == dataSize)
	{
		// 데이터를 처리한 것과 수신한 데이터 포인터가 동일한 경우 처음 위치로 조정
		m_readPos = m_writePos = 0;
	}
	else 
	{
		// 데이터 버퍼가 넘길 경우 남은 데이터를 앞으로 복사
		::memcpy(&m_buffer[0], &m_buffer[m_readPos], dataSize);
		m_readPos = 0;
		m_writePos = dataSize;
	}

}
