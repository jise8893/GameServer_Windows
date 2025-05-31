#include "pch.h"
#include "ReaderWriterLock.h"
#include "Tls.h"

void Lock::WriteLock()
{
	// ������ �����忡�� ���� ���� ��� ��� ��ȯ
	const uint32_t lockThreadId = m_lockFlag.load() & WRITE_THREAD_MASK;
	if (tlsThreadId == lockThreadId)
	{
		m_writeCount++;
		return;
	}

	// � �����嵵 ���� �����ϰų� �����ϰ� ���� ���� ���, ����Ͽ� �������� ��´�.
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

		// ���� �ð� ������ ���������� ���� ���� ���� ��� ��õ�
		if (::GetTickCount64() - beginTick >= ACQUIRE_TIMEOUT_TICK)
		{
			continue;
		}
		// CPU ��뷮�� �����Ͽ� �ش� �����常 �������� �ö󰡴� ���� �������� CPU ������ �ٸ� �����忡 �纸�Ѵ�.
		std::this_thread::yield();
	}

}

void Lock::ReadLock()
{
	// ������ �����尡 ���� ��� ��� ����
	const uint32_t lockThreadId = (m_lockFlag.load() & WRITE_THREAD_MASK) >> 16;
	if (tlsThreadId == lockThreadId)
	{
		return;
	}

	// �ƹ��� WriteLock�� ���� ���� ��� ���� ī��Ʈ�� �ø���.
	const uint64_t beginTick = ::GetTickCount64();
	while (true)
	{
		for (uint32_t spinCount = 0; spinCount < MAX_SPIN_COUNT; spinCount++)
		{
			uint32_t expected = m_lockFlag.load() & READ_COUNT_MASK;
			if (m_lockFlag.compare_exchange_strong(expected, expected + 1))
			{
				// Compare and swap ���� �� �� ���
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
	// �߻��� ��� ����ȭ ���� �߻�
	if ((m_lockFlag.load() & READ_COUNT_MASK) != 0)
	{
		printf("MULTIPLE LOCK OCCURED\n");
		return;
	}

	const int32_t lockCount = --m_writeCount;
	if (0 == lockCount)
	{
		// WriteLock�� ����� ��� �÷��� �ʱ�ȭ
		m_lockFlag.store(EMPTY_FLAG);
	}
}

void Lock::ReadUnlock()
{
	if ((m_lockFlag.fetch_sub(1) & READ_COUNT_MASK) == 0)
	{
		// ����ȭ ������ �߻�.
		printf("MULTIPLE LOCK OCCURED\n");
	}
}
