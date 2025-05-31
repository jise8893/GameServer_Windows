#include "pch.h"
#include "Listener.h"
#include "SocketUtils.h"

Listener::Listener()
{
	m_socket = SocketUtils::CreateSocket();
}

Listener::~Listener()
{

}

void Listener::Dispatch(IocpEvent* iocpEvent, DWORD numOfBytes)
{
	if (iocpEvent->GetType() == EventType::ACCEPT)
	{

	}
}

void Listener::RegisterAccept()
{

}

void Listener::ProcessAccept()
{

}
