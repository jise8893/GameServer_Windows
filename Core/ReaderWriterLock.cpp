#include "pch.h"
#include "ReaderWriterLock.h"
#include "Tls.h"

void Lock::WriteLock()
{
	// 동일한 스레드에서 락을 잡은 경우 즉시 반환
	const uint32_t lockThreadId = m_lockFlag.load() & WRITE_THREAD_MASK;
	if (tlsThreadId == lockThreadId)
	{
		m_writeCount++;
		return;
	}

	// 어떤 스레드도 락을 소유하거나 공유하고 있지 않은 경우, 대기하여 소유권을 얻는다.
	const uint64_t beginTick = ::GetTickCount64();
	const uint32_t desired = ((tlsThreadId << 16) & WRITE_THREAD_MASK);
	while (true)
	{
		for (uint32_t spinCount = 0; spinCount < MAX_SPIN_COUNT; spinCount++)
		{
			uint32_t expected = EMPTY_FLAG;
			if (m_lockFlag.compare_exchange_strong(expected, desired))
			{
				m_writeCount++;
				return;
			}
		}

		// 일정 시간 동안이 지났음에도 락을 얻지 못한 경우 재시도
		if (::GetTickCount64() - beginTick >= ACQUIRE_TIMEOUT_TICK)
		{
			continue;
		}
		// CPU 사용량이 증가하여 해당 스레드만 점유율이 올라가는 것을 막기위해 CPU 점유를 다른 스레드에 양보한다.
		std::this_thread::yield();
	}

}

void Lock::ReadLock()
{
	// 동일한 스레드가 락을 잡는 경우 성공
	const uint32_t lockThreadId = (m_lockFlag.load() & WRITE_THREAD_MASK) >> 16;
	if (tlsThreadId == lockThreadId)
	{
		return;
	}

	// 아무도 WriteLock을 걸지 않은 경우 공유 카운트를 올린다.
	const uint64_t beginTick = ::GetTickCount64();
	while (true)
	{
		for (uint32_t spinCount = 0; spinCount < MAX_SPIN_COUNT; spinCount++)
		{
			uint32_t expected = m_lockFlag.load() & READ_COUNT_MASK;
			if (m_lockFlag.compare_exchange_strong(expected, expected + 1))
			{
				// Compare and swap 성공 시 락 허용
				return;
			}
		}

		if (::GetTickCount64() - beginTick >= ACQUIRE_TIMEOUT_TICK)
			continue;

		std::this_thread::yield();
	}


}

void Lock::WriteUnlock()
{
	// 발생한 경우 동기화 문제 발생
	if ((m_lockFlag.load() & READ_COUNT_MASK) != 0)
	{
		printf("MULTIPLE LOCK OCCURED\n");
		return;
	}

	const int32_t lockCount = --m_writeCount;
	if (0 == lockCount)
	{
		// WriteLock이 종료될 경우 플래그 초기화
		m_lockFlag.store(EMPTY_FLAG);
	}
}

void Lock::ReadUnlock()
{
	if ((m_lockFlag.fetch_sub(1) & READ_COUNT_MASK) == 0)
	{
		// 동기화 문제가 발생.
		printf("MULTIPLE LOCK OCCURED\n");
	}
}
