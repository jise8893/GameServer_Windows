#include "pch.h"
#include "SocketUtils.h"

LPFN_CONNECTEX SocketUtils::m_lpfnConnectEx = nullptr;
LPFN_ACCEPTEX SocketUtils::m_lpfnAcceptEx = nullptr;
LPFN_DISCONNECTEX SocketUtils::m_lpfnDisconnectEx = nullptr;


BOOL SocketUtils::Init()
{
	if(BindWindowsFunction(INVALID_SOCKET, WSAID_CONNECTEX, reinterpret_cast<LPVOID*>(&m_lpfnConnectEx))&&
		BindWindowsFunction(INVALID_SOCKET, WSAID_ACCEPTEX, reinterpret_cast<LPVOID*>(&m_lpfnAcceptEx))&&
		BindWindowsFunction(INVALID_SOCKET, WSAID_DISCONNECTEX, reinterpret_cast<LPVOID*>(&m_lpfnDisconnectEx)))
	{
		return TRUE; 
	}
	return FALSE;
}

SOCKET SocketUtils::CreateSocket()
{
	SOCKET socket = ::WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
	if (socket == INVALID_SOCKET)
	{
		return -1; // Error creating socket
	}
	return socket;
}

BOOL SocketUtils::SetReuseAddress(SOCKET socket, bool reuse)
{
	int optVal = reuse ? 1 : 0;
	return SOCKET_ERROR != ::setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<const char*>(&optVal), sizeof(optVal));
}

BOOL SocketUtils::SetTcpNoDelay(SOCKET socket, bool noDelay)
{
	int optVal = noDelay ? 1 : 0;
	return SOCKET_ERROR != ::setsockopt(socket, IPPROTO_TCP, TCP_NODELAY, reinterpret_cast<const char*>(&optVal), sizeof(optVal));
}

BOOL SocketUtils::SetLinger(SOCKET socket, bool enable, int lingerTime)
{
	linger l = { 0 };
	l.l_onoff = enable ? 1 : 0;
	l.l_linger = lingerTime;
	return SOCKET_ERROR != ::setsockopt(socket, SOL_SOCKET, SO_LINGER, reinterpret_cast<const char*>(&l), sizeof(l));
}

BOOL SocketUtils::BindAddress(SOCKET socket, const WCHAR* address, int port)
{
	sockaddr_in addr = { 0 };
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	InetPton(AF_INET, address, &addr.sin_addr);
	return SOCKET_ERROR != ::bind(socket, reinterpret_cast<sockaddr*>(&addr), sizeof(addr));
}

BOOL SocketUtils::BindAnyAddress(SOCKET socket, int port)
{
	sockaddr_in addr = { 0 };
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(port); 
	return SOCKET_ERROR != ::bind(socket, reinterpret_cast<sockaddr*>(&addr), sizeof(addr));
}

BOOL SocketUtils::Listen(SOCKET socket, int backlog)
{
	return SOCKET_ERROR != ::listen(socket, backlog);
}

BOOL SocketUtils::BindWindowsFunction(SOCKET socket, GUID guid, LPVOID* fn)
{
	DWORD byte = 0;
	return SOCKET_ERROR != ::WSAIoctl(socket, SIO_GET_EXTENSION_FUNCTION_POINTER, &guid, sizeof(guid), fn, sizeof(fn), &byte, NULL, NULL);
}
