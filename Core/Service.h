#pragma once
#include "Listener.h"
#include "ReaderWriterLock.h"

class Session;
using IocpCoreSharedPtr = std::shared_ptr<IocpCore>;
using SessionSharedPtr = std::shared_ptr<Session>;
using ListenerSharedPtr = std::shared_ptr<Listener>;


class Service : public std::enable_shared_from_this<Service>
{
public:
	Service(IocpCoreSharedPtr pIocpCore);
	virtual ~Service();

	bool	Start(IN const WCHAR* address, IN const int port);
	SessionSharedPtr CreateSession();
	
private:
	IocpCoreSharedPtr				m_pIocpCore;
	ListenerSharedPtr				m_pListener;
	
	
	
	std::set<SessionSharedPtr>		m_setSession;
	Lock							m_lock; // session�� ���� ����ȭ�� ���� ��

};

