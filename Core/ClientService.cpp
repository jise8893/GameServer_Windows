#include "pch.h"
#include "ClientService.h"
#include "SocketUtils.h"
#include "Session.h"
ClientService::ClientService(std::shared_ptr<IocpCore> pIocpCore, std::function<SessionSharedPtr()> function) : Service(pIocpCore, function)
{
}

ClientService::~ClientService()
{
}

bool ClientService::Start(IN const WCHAR* address, IN const int port)
{
	if (false == SocketUtils::Init())
	{
		return false;
	}

	std::shared_ptr<Session> pSession = CreateSession();
if (false == pSession->RegisterConnect(address, port))
		return false;
	return true;
}