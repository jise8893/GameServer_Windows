#include "pch.h"
#include "Session.h"
#include "SocketUtils.h"
#include "Service.h"
Session::Session(ServiceSharedPtr pService) : m_recvBuffer(BUFFER_SIZE), m_socket(INVALID_SOCKET)
{
	m_socket = SocketUtils::CreateSocket();
	m_pService = pService;
}


Session::~Session()
{

}

void Session::Dispatch(IocpEvent* iocpEvent, DWORD numOfBytes)
{
	switch (iocpEvent->GetType())
	{
	case EventType::CONNECT:
		ProcessConnect();
		break;
	case EventType::DISCONNECT:
		ProcessDisConnect();
		break;
	case EventType::RECV:
		ProcessRecv(numOfBytes);
		break;
	case EventType::SEND:
		ProcessSend(numOfBytes);
		break;
	default:
		break;
	}
}

HANDLE Session::GetHandle()
{
	return m_socket;
}

void Session::ProcessConnect()
{

	// ������ �ܿ��� OnConnected ȣ�� ó�� 
	OnConnected();

	// RegisterRecv ���  
	RegisterRecv();
}

void Session::ProcessDisConnect()
{
	m_pService->CloseSession(std::static_pointer_cast<Session>(shared_from_this()));
	m_disConnectEvent.Init();
}

void Session::ProcessSend(DWORD numOfBytes)
{
	// �ϳ��� �����忡 ���� SendEvent�� ������ ����ϱ� ������ ����ȭ ���ʿ�
	m_sendEvent.SetOwner(nullptr);
	m_sendEvent.m_vecSendBuffer.clear();
	m_sendEvent.Init();

	if (0 == numOfBytes)
	{
		DisConnect();
	}

	// ������ �ܿ��� ó��, ���� ����ȭ ���� ���
	OnSend(numOfBytes);

	WriteLockGuard lockGuard(m_sendLock);
	if(m_sendQ.empty())
	{
		// Send �� �ٽ� �ٸ� �����尡 ����� �� �ֵ��� ����
		m_bRegistedSend.store(false);
	}
	else
	{
		RegisterSend();
	}

}

void Session::ProcessRecv(DWORD numOfBytes)
{
	
	m_recvEvent.SetOwner(nullptr);
	// RecvBuffer�� ���ؼ� �ϳ��� �����常 Recv�� ����ϰ� ó���ϱ⿡ ����ȭ ���ʿ�
	
	if (0 == numOfBytes)
	{
		DisConnect();
		return;
	}

	if (false == m_recvBuffer.OnWrite(numOfBytes))
	{
		DisConnect();
		return;
	}

	DWORD numOfRead = OnRecv(m_recvBuffer.ReadPos(), m_recvBuffer.GetDataSize());
	if (m_recvBuffer.OnRead(numOfRead))
	{
		DisConnect();
		return;
	}

	m_recvBuffer.Clean();
	RegisterRecv();

}


void Session::RegisterRecv()
{
	WSABUF wsaBuf = { 0, };
	wsaBuf.buf = reinterpret_cast<char*>(m_recvBuffer.WritePos());
	wsaBuf.len = m_recvBuffer.GetFreeSize();
	DWORD numOfBytes = 0;
	DWORD flags = 0;
	m_recvEvent.SetOwner(shared_from_this());

	if (SOCKET_ERROR == ::WSARecv(m_socket, &wsaBuf, 1, &numOfBytes, &flags, &m_recvEvent, nullptr))
	{
		const int32_t errCode = ::WSAGetLastError();
		if (ERROR_IO_PENDING != errCode)
		{
			DisConnect();
			m_recvEvent.SetOwner(nullptr);
		}
	}
}

void Session::RegisterSend()
{
	m_sendEvent.SetOwner(shared_from_this());
	m_sendEvent.m_vecSendBuffer.reserve(m_sendQ.size()); // ����ȭ

	std::vector<WSABUF> wsaBufs;

	WriteLockGuard lockGuard(m_sendLock);
	wsaBufs.reserve(m_sendQ.size());

	while (false == m_sendQ.empty())
	{
		WSABUF wsabuf;
		SendBufferSharedPtr pSendBuffer = m_sendQ.front();
		
		wsabuf.buf = reinterpret_cast<char*>(pSendBuffer->GetBuffer());
		wsabuf.len = pSendBuffer->GetWriteSize();
		m_sendQ.pop();

		// Queue���� ���� �� �� SendBuffer�� Reference Count�� 0�� �Ǿ� �Ҹ���� �ʵ��� �߰�
		m_sendEvent.m_vecSendBuffer.push_back(pSendBuffer);
	}

	DWORD numOfBytes = 0;
	if (SOCKET_ERROR == ::WSASend(m_socket, wsaBufs.data(), wsaBufs.size(), &numOfBytes, 0, &m_sendEvent, nullptr))
	{
		int32_t errCode = ::WSAGetLastError();
		if (ERROR_IO_PENDING != errCode)
		{
			DisConnect();
		}
	}

}

void Session::DisConnect()
{
	m_disConnectEvent.SetOwner(shared_from_this());
	if (false == ::SocketUtils::DisconnectEx(m_socket, &m_disConnectEvent, TF_REUSE_SOCKET, 0))
	{
		int32_t errCode = ::WSAGetLastError();
		if (ERROR_IO_PENDING != errCode)
		{
			m_disConnectEvent.SetOwner(nullptr);
		}
	}
}

void Session::Send(SendBufferSharedPtr pSendBuffer)
{
	WriteLockGuard lockGuard(m_sendLock);
	m_sendQ.emplace(pSendBuffer);

	if (m_bRegistedSend.exchange(true) == false)
	{
		RegisterSend();
	}
}

int32_t Session::OnRecv(void* buffer, int32_t numOfBytes)
{
	return numOfBytes;
}
