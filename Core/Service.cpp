#include "pch.h"
#include "Service.h"
#include "Session.h"
#include "SocketUtils.h"

Service::Service(IocpCoreSharedPtr pIocpCore, ContentSession function) : m_pIocpCore(pIocpCore)
{
}
Service::~Service()
{
	SocketUtils::Clear();
}

SessionSharedPtr Service::CreateSession()
{
	SessionSharedPtr pSession = nullptr;
	
	try
	{
		pSession = m_function();
	}
	catch (...)
	{
		return pSession;
	}
	pSession->SetService(shared_from_this());
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
void Service::BroadCast(std::shared_ptr<SendBuffer> pSendBuffer)
{
	for (const auto session : m_setSession)
	{
		session->Send(pSendBuffer);
	}
}