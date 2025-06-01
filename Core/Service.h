#pragma once
#include <set>
#include "Listener.h"
#include "ReaderWriterLock.h"

class Session;
using IocpCoreSharedPtr = std::shared_ptr<IocpCore>;
using SessionSharedPtr = std::shared_ptr<Session>;
using ListenerSharedPtr = std::shared_ptr<Listener>;


class Service : public std::enable_shared_from_this<Service>
{
public:
	Service() = delete;

	Service(IocpCoreSharedPtr pIocpCore);
	virtual ~Service();

	virtual bool	Start(IN const WCHAR* address, IN const int port) = 0;
	SessionSharedPtr CreateSession();
	void			 CloseSession(SessionSharedPtr pSession);

	IocpCoreSharedPtr GetIocpCore() { return m_pIocpCore; }
protected:
	IocpCoreSharedPtr				m_pIocpCore;
	ListenerSharedPtr				m_pListener;
	
	
	
	std::set<SessionSharedPtr>		m_setSession;
	Lock							m_lock; // session에 대한 동기화를 위한 락

};

