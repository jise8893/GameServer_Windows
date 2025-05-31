#pragma once
class SendBuffer
{
public:
	SendBuffer(const int32_t numOfBytes);
	~SendBuffer();

	BYTE*	GetBuffer() { return m_buffer.data(); }
	int32_t	GetWriteSize() { return m_writePos; }
	int32_t GetCapacity() { return static_cast<int32_t>(m_buffer.size()); }
	void	CopyData(IN const void* data, IN const int32_t size);
private:
	std::vector<BYTE>	m_buffer;
	int32_t				m_writePos = 0;
};

