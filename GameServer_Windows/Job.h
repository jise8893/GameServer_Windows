#pragma once
#include "../Core/ReaderWriterLock.h"

/*!
* Job
* @brief
* Thread 경합을 컨텐츠 단위로 줄이기 위해 사용하는 Job 단위 처리 클래스
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
		std::cout << m_target << "에게 HEAL " << m_healValue<< "\n";
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