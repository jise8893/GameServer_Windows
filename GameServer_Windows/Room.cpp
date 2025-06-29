#include "pch.h"
#include "Room.h"

void Room::FlushJob()
{
	while (true)
	{
		JobSharedPtr pJob = m_queueJob.Pop();
		if (nullptr == pJob)
			break;
		pJob->Execute();
	}
}
