#pragma once
#include <set>
#include <functional>
#include "Listener.h"
#include "ReaderWriterLock.h"

class Session;
using IocpCoreSharedPtr = std::shared_ptr<IocpCore>;
using SessionSharedPtr = std::shared_ptr<Session>;
using ListenerSharedPtr = std::shared_ptr<Listener>;

using ContentSession = std::function<SessionSharedPtr()>;
class Service: public std::enable_shared_from_this<Service>
{
public:
	Service() = delete;

	Service(IocpCoreSharedPtr pIocpCore, ContentSession function);
	virtual ~Service();

	virtual bool	Start(IN const WCHAR* address, IN const int port) = 0;
	SessionSharedPtr CreateSession();
	void			 CloseSession(SessionSharedPtr pSession);

	IocpCoreSharedPtr GetIocpCore() { return m_pIocpCore; }

	void		BroadCast(std::shared_ptr<SendBuffer> pSendBuffer);

protected:
	IocpCoreSharedPtr				m_pIocpCore;
	ListenerSharedPtr				m_pListener;
	
	ContentSession					m_function; // 세션을 상속하여 패킷 처리를 재정의 하기 위해 
												// 재정의한 세션으로 오버라이딩하기 위한 함수
	
	
	std::set<SessionSharedPtr>		m_setSession;
	Lock							m_lock; // session에 대한 동기화를 위한 락

};

