#include "pch.h"
#include "../Core/Service.h"
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
		printf_s("서버 시작 예외 발생: %s", e.what());
		return 0;
	}

	pService->Start(L"127,0,0,1", 8888);
	

	return 0;
}