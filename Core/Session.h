#pragma once

#include "IocpEvent.h"
#include "IocpCore.h"
#include "AutoCloseSocket.h"
#include "RecvBuffer.h"

class Session : public IocpObject, public std::enable_shared_from_this<Session>
{
	enum
	{
		BUFFER_SIZE = 0x1000,
	};
public:
	Session(); 
	virtual ~Session();


	virtual void	Dispatch(IocpEvent* iocpEvent, DWORD numOfBytes) override;
	virtual HANDLE	GetHandle() override;
private:
	RecvEvent			m_recvEvent;
	SendEvent			m_sendEvent;

	AutoCloseSocket		m_socket; // 소멸자에서 소켓 종료 처리하는 클래스
public:

	RecvBuffer			m_recvBuffer;
};

