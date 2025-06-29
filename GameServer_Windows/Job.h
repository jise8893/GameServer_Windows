#pragma once
#include "../Core/ReaderWriterLock.h"

/*!
* Job
* @brief
* Thread ������ ������ ������ ���̱� ���� ����ϴ� Job ���� ó�� Ŭ����
* 
*/
class IJob
{
public:
	virtual void Execute() = 0;

};

class HealJob : public IJob
{
public:
	virtual void Execute() override
	{
		std::cout << m_target << "���� HEAL " << m_healValue<< "\n";
	}
private:
	uint64_t m_target = 0; 
	uint64_t m_healValue = 0;
};


using JobSharedPtr = shared_ptr<IJob>;

class JobQueue
{
public:
	void Push(JobSharedPtr job)
	{
		WriteLockGuard lock(m_lock);
		if (m_queueJob.empty())
		{

		}
	}

	JobSharedPtr Pop()
	{
		WriteLockGuard lock(m_lock);
		if (m_queueJob.empty())
			return nullptr;

		JobSharedPtr pJob = m_queueJob.front();
		m_queueJob.pop(); 
		return pJob;
	}

private:
	Lock m_lock;
	std::queue<JobSharedPtr> m_queueJob;
};