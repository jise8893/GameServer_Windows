#pragma once

class RecvBuffer
{
	enum
	{
		BUFFER_COUNT = 5,
	};

public:
	RecvBuffer(uint32_t bufferSize);
	~RecvBuffer();

	bool OnRead(int32_t numOfBytes);
	bool OnWrite(int32_t numOfBytes);
	void Clean();

	BYTE* ReadPos() { return &m_buffer[m_readPos]; }
	BYTE* ReadPos() { return &m_buffer[m_writePos]; }
	int32_t GetDataSize() { return m_writePos - m_readPos; }
	int32_t GetFreeSize() { return m_bufferSize - m_writePos;}


private:
	
	int32_t m_capacity = 0;

	int32_t m_bufferSize = 0;
	int32_t m_readPos = 0;
	int32_t m_writePos = 0;
	std::vector<BYTE> m_buffer;
};

