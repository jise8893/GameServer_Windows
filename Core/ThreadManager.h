#pragma once

#include "Tls.h"
#include "Singleton.h"
#include <functional>
#include <mutex>
class ThreadManager : public Singleton<ThreadManager>
{
public:
	ThreadManager();
	virtual ~ThreadManager() = default;
public:
	bool			CreateThread(std::function<void()> function);
	void			Join();
	static	void	InitTid();
	static	std::atomic<int32_t> m_tidCounter;
private:
	std::vector<std::thread> m_vecThread;
	std::mutex	m_lock;

};
#define THREAD_MGR	ThreadManager::GetInstance

