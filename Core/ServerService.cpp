#include "pch.h"
#include "ServerService.h"
#include "SocketUtils.h"

ServerService::ServerService(std::shared_ptr<IocpCore> pIocpCore) : Service(pIocpCore)
{

}

ServerService::~ServerService()
{

}
bool ServerService::Start(IN const WCHAR* address, IN const int port)
{
	if (false == SocketUtils::Init())
	{
		return false;
	}

	try
	{
		m_pListener = std::make_shared<Listener>();
	}
	catch (std::bad_alloc& e)
	{
		printf_s("Failed to alloc Listener class, errCode = %d", GetLastError());
		return false;
	}

	m_pListener->Start(shared_from_this(), address, port);
}

