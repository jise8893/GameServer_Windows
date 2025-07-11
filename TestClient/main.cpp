#include "pch.h"
#include <thread>
#include "../Core/ClientService.h"
#include "../Core/ThreadManager.h"
#include "GameSession.h"

auto gameSession = []() {return std::make_shared<GameSession>(); };
int main()
{

	std::this_thread::sleep_for(std::chrono::seconds(2));
	std::shared_ptr<ClientService> pService = nullptr;
	IocpCoreSharedPtr pIocpCore = nullptr;

	try
	{
		pIocpCore = std::make_shared<IocpCore>();
		pService = std::make_shared<ClientService>(pIocpCore, gameSession);
	}
	catch (std::bad_alloc& e)
	{
		printf_s("std::shared_ptr bad_alloc �߻�: %s", e.what());
		return 0;
	}

	if (false == pService->Start(L"127.0.0.1", 8888))
		return false;

	THREAD_MGR().CreateThread([=] {
		while (true)
		{
			pService->GetIocpCore()->Dispatch();
		}
		});


	THREAD_MGR().Join();
	

	return 0;
}