#pragma once
#include "Job.h"

class Room
{
public:
	void Enter();
	void Leave();
	void BroadCast();
public:
	void PushJob(JobSharedPtr job) { m_queueJob.Push(job); }
	void FlushJob();
private:
	JobQueue m_queueJob;
};


extern Room GRoom;

class EnterJob : public IJob
{
	EnterJob(Room& room) : m_room(room)
	{	
	}

	virtual void Execute() override
	{
		
	}

public:
	Room& m_room;

};
