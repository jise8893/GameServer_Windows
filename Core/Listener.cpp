#include "pch.h"
#include "Listener.h"
#include "SocketUtils.h"
#include "Service.h"
#include "Session.h"
Listener::Listener()
{

}

Listener::~Listener()
{
	m_pService = nullptr;
}

void Listener::Dispatch(IocpEvent* iocpEvent, DWORD numOfBytes)
{
	if (iocpEvent->GetType() == EventType::ACCEPT)
	{

	}
}

bool Listener::RegisterAccept(IocpEvent* iocpEvent)
{
	SessionSharedPtr pSession = m_pService->CreateSession();
	if (SOCKET_ERROR == ::setsockopt(reinterpret_cast<SOCKET>(pSession->GetHandle()),
		SOL_SOCKET,
		SO_UPDATE_ACCEPT_CONTEXT,
		reinterpret_cast<char*>(&m_socket),
		sizeof(SOCKET)))
	{
		return false;
	}

	DWORD numOfReadBytes = 0;
	if (false == SocketUtils::AcceptEx(m_socket,
										reinterpret_cast<SOCKET>(pSession->GetHandle()),
										pSession->m_recvBuffer.WritePos(),
										0,
										sizeof(SOCKADDR_IN) + 16,
										sizeof(SOCKADDR_IN) + 16,
										&numOfReadBytes,
										reinterpret_cast<LPOVERLAPPED>(iocpEvent)))
	{
		const int32_t errCode = ::WSAGetLastError();
		if (WSA_IO_PENDING != errCode)
		{
			return RegisterAccept(iocpEvent);
		}
	}

	return true;
}

void Listener::ProcessAccept()
{

}

bool Listener::Start(ServiceSharedPtr pService, IN const WCHAR* address, IN const int port)
{
	m_socket = SocketUtils::CreateSocket();
	if (INVALID_SOCKET == m_socket)
	{
		return false; 
	}

	if (nullptr == pService)
	{
		return false;
	}
	m_pService = pService;

	if (false == SocketUtils::SetLinger(m_socket, false))
	{
		return false;
	}

	if (false == SocketUtils::SetTcpNoDelay(m_socket, true))
	{
		return false;
	}

	if (SocketUtils::SetReuseAddress(m_socket, true))
	{
		return false;
	}

	if (false == SocketUtils::BindAddress(m_socket, address, port))
	{
		return false;
	}

	if (false == SocketUtils::Listen(m_socket, BACK_LOG_COUNT))
	{
		return false;
	}
	
	for (int i = 0; i < ACCEPT_EVENT_COUNT; i++)
	{
		AcceptEvent* acceptEvent = new(std::nothrow) AcceptEvent;
		if (nullptr == acceptEvent)
		{
			return false;
		}
		acceptEvent->SetOwner(shared_from_this());
		m_vecAcceptEvent.emplace_back(acceptEvent);
		RegisterAccept(acceptEvent);
	}


	return true;

}
