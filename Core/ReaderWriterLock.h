#pragma once

#include <atomic>
/// 
/// @class Lock (SpinLock)
/// 
/// @brief 데이터의 참조의 경우 다른 스레드의 데이터 참조는 허용하고,
/// 데이터 변경에 대한 동기화 작업 시, 동기화가 필요한 데이터에 대한 작업을 대기시킨다.
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
	uint16_t m_writeCount = 0; // Write에 대해 중첩 락을 허용하기 때문에 RAII Unlock시, 시도 횟수를 계산한다.

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