#include "pch.h"
#include "Service.h"
#include "Session.h"
#include "SocketUtils.h"
Service::Service(IocpCoreSharedPtr pIocpCore) : m_pIocpCore(pIocpCore)
{
}

Service::~Service()
{

}

bool Service::Start(IN const WCHAR* address, IN const int port)
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

SessionSharedPtr Service::CreateSession()
{
	SessionSharedPtr pSession = nullptr;
	try
	{
		pSession = std::make_shared<Session>(shared_from_this());
	}
	catch (...)
	{
		return pSession;
	}

	m_pIocpCore->Register(pSession);

	WriteLockGuard lockGuard(m_lock);
	m_setSession.insert(pSession);
	return pSession;
}

void Service::CloseSession(SessionSharedPtr pSession)
{
	WriteLockGuard lockGuard(m_lock);
	m_setSession.erase(pSession);
}
