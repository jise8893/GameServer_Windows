#pragma once

#include <atomic>
/// 
/// @class Lock (SpinLock)
/// 
/// @brief �������� ������ ��� �ٸ� �������� ������ ������ ����ϰ�,
/// ������ ���濡 ���� ����ȭ �۾� ��, ����ȭ�� �ʿ��� �����Ϳ� ���� �۾��� ����Ų��.
///
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
	uint16_t m_writeCount = 0; // Write�� ���� ��ø ���� ����ϱ� ������ RAII Unlock��, �õ� Ƚ���� ����Ѵ�.

};

class ReadLockGuard
{
public:
	ReadLockGuard(Lock& lock) : m_lock(lock) { m_lock.ReadLock(); }
	~ReadLockGuard() { m_lock.ReadUnlock(); }
private:
	Lock& m_lock;
};


class WriteLockGuard
{
public:
	WriteLockGuard(Lock& lock) : m_lock(lock) { m_lock.WriteLock(); }
	~WriteLockGuard() { m_lock.WriteUnlock(); }
private:
	Lock& m_lock;
};