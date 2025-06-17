#pragma once

#include "IocpCore.h"
#include "AutoCloseSocket.h"
#include "IocpEvent.h"

class Service;
using ServiceSharedPtr = std::shared_ptr<Service>;

class Listener : public IocpObject
{
	enum
	{
		BACK_LOG_COUNT = 10, // ���� ��� ��α� ť ��
		ACCEPT_EVENT_COUNT = 5, // ���ÿ� ������ Ŭ���̾�Ʈ �̺�Ʈ
	};
public:
	Listener();
	virtual ~Listener();

	virtual void	Dispatch(IocpEvent* iocpEvent, DWORD numOfBytes);
	virtual HANDLE	GetHandle() override { return m_socket; }

	bool			Start(ServiceSharedPtr pService, IN const WCHAR* address, IN const int port);
private:
	bool			RegisterAccept(AcceptEvent* acceptEvent);
	void			ProcessAccept(AcceptEvent* acceptEvent);
private:
	AutoCloseSocket m_socket;
	std::vector<AcceptEvent*> m_vecAcceptEvent;
private:
	ServiceSharedPtr m_pService;
};

