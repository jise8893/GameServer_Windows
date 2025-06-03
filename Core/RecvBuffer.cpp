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
		// �����͸� ó���� �Ͱ� ������ ������ �����Ͱ� ������ ��� ó�� ��ġ�� ����
		m_readPos = m_writePos = 0;
	}
	else 
	{
		// ������ ���۰� �ѱ� ��� ���� �����͸� ������ ����
		::memcpy(&m_buffer[0], &m_buffer[m_readPos], dataSize);
		m_readPos = 0;
		m_writePos = dataSize;
	}

}
