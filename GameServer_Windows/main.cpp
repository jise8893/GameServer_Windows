#include "pch.h"
#include "../Core/Service.h"
#include "../Core/ThreadManager.h"
// @func main
// @brief main function for the game server
int main()
{

	ServiceSharedPtr pService = nullptr;
	IocpCoreSharedPtr pIocpCore = nullptr;

	try
	{
		pIocpCore = std::make_shared<IocpCore>();
		pService = std::make_shared<Service>(pIocpCore);
	}
	catch (std::bad_alloc& e)
	{
		printf_s("std::shared_ptr bad_alloc ¹ß»ý: %s", e.what());
		return 0;
	}

	pService->Start(L"127,0,0,1", 8888);
	
	THREAD_MGR().CreateThread([=]{
		pIocpCore->Dispatch();
	});
	THREAD_MGR().Join();
	return 0;
}