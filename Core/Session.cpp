#include "pch.h"
#include "Session.h"
#include "SocketUtils.h"
#include "Service.h"
#include "Protocol.h"
Session::Session() : m_recvBuffer(BUFFER_SIZE), m_bIsConnected(false), m_socket(INVALID_SOCKET)
{
	m_socket = SocketUtils::CreateSocket();
}


Session::~Session()
{
	printf("hello session");
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
	m_bIsConnected.store(true);
	// 컨텐츠 단에서 OnConnected 호출 처리 
	OnConnected();

	// RegisterRecv 등록  
	RegisterRecv();
}

void Session::ProcessDisConnect()
{
	m_pService->CloseSession(std::static_pointer_cast<Session>(shared_from_this()));
	m_disConnectEvent.Init();
}

void Session::ProcessSend(DWORD numOfBytes)
{
	// 하나의 스레드에 한해 SendEvent에 접근을 허용하기 때문에 동기화 불필요
	m_sendEvent.m_pOwner = nullptr;
	m_sendEvent.m_vecSendBuffer.clear();
	m_sendEvent.Init();

	if (0 == numOfBytes)
	{
		DisConnect();
	}

	OnSend(numOfBytes);

	WriteLockGuard lockGuard(m_sendLock);
	if(m_sendQ.empty())
	{
		// Send 를 다시 다른 스레드가 등록할 수 있도록 변경
		m_bRegistedSend.store(false);
	}
	else
	{
		RegisterSend();
	}

}

void Session::ProcessRecv(DWORD numOfBytes)
{
	
	m_recvEvent.m_pOwner = nullptr;
	// RecvBuffer에 대해서 하나의 스레드만 Recv를 등록하고 처리하기에 동기화 불필요
	
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
	if (false == m_recvBuffer.OnRead(numOfRead))
	{
		DisConnect();
		return;
	}

	m_recvBuffer.Clean();
	RegisterRecv();

}


void Session::RegisterRecv()
{
	if (m_bIsConnected.load() == false)
		return;

	WSABUF wsaBuf = { 0, };
	wsaBuf.buf = reinterpret_cast<char*>(m_recvBuffer.WritePos());
	wsaBuf.len = m_recvBuffer.GetFreeSize();
	DWORD numOfBytes = 0;
	DWORD flags = 0;
	m_recvEvent.m_pOwner = shared_from_this();

	if (SOCKET_ERROR == ::WSARecv(m_socket, &wsaBuf, 1, &numOfBytes, &flags, &m_recvEvent, nullptr))
	{
		const int32_t errCode = ::WSAGetLastError();
		if (WSA_IO_PENDING != errCode)
		{
			DisConnect();
			m_recvEvent.m_pOwner = nullptr;
		}
	}
}

void Session::RegisterSend()
{
	if (m_bIsConnected.load() == false)
	{
		m_bRegistedSend.store(false);
		return;
	}
		
	m_sendEvent.m_pOwner = shared_from_this();
	m_sendEvent.m_vecSendBuffer.reserve(m_sendQ.size()); // 최적화

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

		// Queue에서 제거 한 후 SendBuffer가 Reference Count가 0이 되어 소멸되지 않도록 추가
		m_sendEvent.m_vecSendBuffer.push_back(pSendBuffer);
		wsaBufs.push_back(wsabuf);
	}

	DWORD numOfBytes = 0;
	if (SOCKET_ERROR == ::WSASend(m_socket, wsaBufs.data(), wsaBufs.size(), &numOfBytes, 0, &m_sendEvent, nullptr))
	{
		int32_t errCode = ::WSAGetLastError();
		if (WSA_IO_PENDING != errCode)
		{
			DisConnect();
		}
	}

}

void Session::DisConnect()
{
	if (m_bIsConnected.exchange(false) == false)
		return;


	m_disConnectEvent.m_pOwner = shared_from_this();
	if (false == ::SocketUtils::DisconnectEx(m_socket, &m_disConnectEvent, TF_REUSE_SOCKET, 0))
	{
		int32_t errCode = ::WSAGetLastError();
		if (WSA_IO_PENDING != errCode)
		{
			m_disConnectEvent.m_pOwner = nullptr;
		}
	}
}

bool Session::RegisterConnect(IN const WCHAR* address, IN const int port)  
{  
	
	if (m_bIsConnected == true)
		return true;
	

    if (false == SocketUtils::SetReuseAddress(m_socket, true))  
    {  
        return false;  
    }  

    if (false == SocketUtils::BindAnyAddress(m_socket, 0))  
    {  
		return false;
    }  


	SOCKADDR_IN sockAddr;
    sockAddr.sin_family = AF_INET;  
    sockAddr.sin_port = htons(port);
	::InetPtonW(AF_INET, address, &sockAddr.sin_addr);
 
    m_connectEvent.m_pOwner = shared_from_this();  

    DWORD numOfBytes = 0; 
	
	
    if (false == SocketUtils::ConnectEx(m_socket, reinterpret_cast<SOCKADDR*>(&sockAddr), sizeof(sockAddr), nullptr, 0, &numOfBytes, &m_connectEvent))  
    {  
        int32_t errCode = ::WSAGetLastError();  
        if (WSA_IO_PENDING != errCode)  
        {  
			m_connectEvent.m_pOwner = nullptr;
			return false;
        }
    }  
	else
	{
		return false;
	}
  
}


void Session::SetService(ServiceSharedPtr pService)
{
	m_pService = pService;
}

void Session::Send(SendBufferSharedPtr pSendBuffer)
{
	bool registerSend = false;
	{
		WriteLockGuard lockGuard(m_sendLock);
		m_sendQ.emplace(pSendBuffer);
		if (m_bRegistedSend.exchange(true) == false)
		{
			registerSend = true;
		}

	}
	
	if (registerSend)
		RegisterSend();
	
}
