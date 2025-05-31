#pragma once

#include "IocpEvent.h"
#include "AutoCloseSocket.h"
#include "RecvBuffer.h"

class Session : public std::enable_shared_from_this<Session>
{
	enum
	{
		BUFFER_SIZE = 0x1000,
	};
public:
	Session(); 
	virtual ~Session();


	HANDLE	GetHandle();
private:
	RecvEvent			m_recvEvent;
	SendEvent			m_sendEvent;

	AutoCloseSocket		m_socket;
	RecvBuffer			m_recvBuffer;
};

