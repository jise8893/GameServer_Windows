#include "pch.h"
#include "../Core/ServerService.h"
#include "../Core/ThreadManager.h"
#include "GameSession.h"

auto gameSession = []() {return std::make_shared<GameSession>(); };
// @func main
// @brief main function for the game server
int main()
{

	std::shared_ptr<ServerService> pService = nullptr;
	IocpCoreSharedPtr pIocpCore = nullptr;

	try
	{
		pIocpCore = std::make_shared<IocpCore>();
		pService = std::make_shared<ServerService>(pIocpCore, gameSession);
	}
	catch (std::bad_alloc& e)
	{
		printf_s("std::shared_ptr bad_alloc �߻�: %s", e.what());
		return 0;
	}

	pService->Start(L"127,0,0,1", 8888);

	for (int i = 0; i < 3; i++)
	{
		THREAD_MGR().CreateThread([=] {
			while (true)
			{
				pIocpCore->Dispatch();
			}
		});
	}

	THREAD_MGR().Join();
	return 0;
}