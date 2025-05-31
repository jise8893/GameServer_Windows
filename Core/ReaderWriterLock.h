#pragma once

#include <atomic>
class Lock
{
	enum : uint32_t
	{
		ACQUIRE_TIMEOUT_TICK = 10000,
		MAX_SPIN_COUNT = 5000,
		WRITE_THREAD_MASK = 0xFFFF'0000,
		READ_COUNT_MASK = 0x0000'FFFF,
		EMPTY_FLAG = 0x00000000,
	};

public:
	void WriteLock();
	void ReadLock();
	void WriteUnlock();
	void ReadUnlock();
private:
	std::atomic<uint32_t> m_lockFlag;
	uint16_t m_writeCount = 0; // Write �� ���� ��ø ���� ����ϱ� ������ RAII Unlock��, �õ� Ƚ���� ����Ѵ�.

};
/// 
/// @class ReaderWriterLock (SpinLock)
/// 
/// @brief �������� ������ ��� �ٸ� �������� ������ ������ ����ϰ�,
/// ������ ���濡 ���� ����ȭ �۾� ��, ����ȭ�� �ʿ��� �����Ϳ� ���� �۾��� ����Ų��.
///
class ReaderWriterLock
{


};

