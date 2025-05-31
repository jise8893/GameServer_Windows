#include "pch.h"
#include "Session.h"
#include "SocketUtils.h"

Session::Session() : m_recvBuffer(BUFFER_SIZE), m_socket(INVALID_SOCKET)
{
	m_socket = SocketUtils::CreateSocket();
}

Session::~Session()
{

}

void Session::Dispatch(IocpEvent* iocpEvent, DWORD numOfBytes)
{
	switch (iocpEvent->GetType())
	{
	case EventType::CONNECT:
		break;
	case EventType::DISCONNECT:
		break;
	case EventType::RECV:
		break;
	case EventType::SEND:
		break;
	default:
		break;
	}
}

HANDLE Session::GetHandle()
{
	return m_socket;
}