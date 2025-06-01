#include "pch.h"
#include "ThreadManager.h"

std::atomic<int32_t> ThreadManager::m_tidCounter = 0;

ThreadManager::ThreadManager()
{
	InitTid();
}

bool ThreadManager::CreateThread(std::function<void()> function)
{
	try
	{
		m_vecThread.emplace_back(std::thread([=]{
			InitTid();
			function();
		}));

	}
	catch (...)
	{
		return false;
	}

	return true;
}

void ThreadManager::Join()
{
	for (std::thread& thread : m_vecThread)
	{
		if (thread.joinable())
			thread.join();
	}
	m_vecThread.clear();
}

void ThreadManager::InitTid()
{
	m_tidCounter++;
	tlsThreadId = m_tidCounter;
}
