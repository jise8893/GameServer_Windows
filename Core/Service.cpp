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
