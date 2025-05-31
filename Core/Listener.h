#pragma once

#include "IocpCore.h"
#include "AutoCloseSocket.h"
#include "IocpEvent.h"
class Listener : public IocpObject
{
public:
	Listener();
	virtual ~Listener();

	virtual void	Dispatch(IocpEvent* iocpEvent, DWORD numOfBytes);
	virtual HANDLE	GetHandle() override { return m_socket; }
private:
	void RegisterAccept();
	void ProcessAccept();
private:
	AutoCloseSocket m_socket;
};

