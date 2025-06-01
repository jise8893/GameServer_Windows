#include "pch.h"
#include "ClientService.h"
#include "SocketUtils.h"
#include "Session.h"
ClientService::ClientService(std::shared_ptr<IocpCore> pIocpCore) : Service(pIocpCore)
{
}

ClientService::~ClientService()
{
}

bool ClientService::Start(IN const WCHAR* address, IN const int port)
{
	std::shared_ptr<Session> pSession = CreateSession();
	pSession->RegisterConnect(address, port);
	return true;
}