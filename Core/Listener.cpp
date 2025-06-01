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
		ProcessAccept(reinterpret_cast<AcceptEvent*>(iocpEvent));
	}
}

bool Listener::RegisterAccept(AcceptEvent* acceptEvent)
{
	SessionSharedPtr pSession = m_pService->CreateSession();
	DWORD numOfReadBytes = 0;
	acceptEvent->Init();
	acceptEvent->m_pSession = pSession;
	if (false == SocketUtils::AcceptEx(m_socket,
										reinterpret_cast<SOCKET>(pSession->GetHandle()),
										pSession->m_recvBuffer.WritePos(),
										0,
										sizeof(SOCKADDR_IN) + 16,
										sizeof(SOCKADDR_IN) + 16,
										&numOfReadBytes,
										reinterpret_cast<LPOVERLAPPED>(acceptEvent)))
	{
		const int32_t errCode = ::WSAGetLastError();
		if (WSA_IO_PENDING != errCode)
		{
			return RegisterAccept(acceptEvent);
		}
	}

	return true;
}

void Listener::ProcessAccept(AcceptEvent* acceptEvent)
{ 
	SessionSharedPtr pSession = acceptEvent->m_pSession;
	
	// GetQueueCompletionStatus �� AcceptEx�� ȣ�� �� �� SO_UPDATE_ACCEPT_CONTEXT �ɼ� ���� �ʿ�
	if (SOCKET_ERROR == ::setsockopt(reinterpret_cast<SOCKET>(pSession->GetHandle()),
		SOL_SOCKET,
		SO_UPDATE_ACCEPT_CONTEXT,
		reinterpret_cast<char*>(&m_socket),
		sizeof(SOCKET)))
	{
		RegisterAccept(acceptEvent);
		return;
	}

	// ������ Ŭ���̾�Ʈ�� IP �� TCP �ּҸ� ������ �� ����.
	// Ŭ���̾�Ʈ ���� ���� ó��

	pSession->ProcessConnect();


	RegisterAccept(acceptEvent);


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

	if (false == SocketUtils::SetReuseAddress(m_socket, true))
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
	
	m_pService->GetIocpCore()->Register(shared_from_this());


	for (int i = 0; i < 1; i++)
	{
		AcceptEvent* acceptEvent = new(std::nothrow) AcceptEvent;
		if (nullptr == acceptEvent)
		{
			return false;
		}
		acceptEvent->m_pOwner = shared_from_this();
		m_vecAcceptEvent.emplace_back(acceptEvent);
		RegisterAccept(acceptEvent);
	}


	return true;

}
