#include "pch.h"
#include "SocketUtils.h"
#include "AutoCloseSocket.h"
LPFN_CONNECTEX SocketUtils::ConnectEx = nullptr;
LPFN_ACCEPTEX SocketUtils::AcceptEx = nullptr;
LPFN_DISCONNECTEX SocketUtils::DisconnectEx = nullptr;


BOOL SocketUtils::Init()
{
	WSADATA wsaData;
	if(0 != WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		return false;
	}

	AutoCloseSocket dummy = CreateSocket();

	if(BindWindowsFunction(dummy, WSAID_CONNECTEX, reinterpret_cast<LPVOID*>(&ConnectEx))&&
		BindWindowsFunction(dummy, WSAID_ACCEPTEX, reinterpret_cast<LPVOID*>(&AcceptEx))&&
		BindWindowsFunction(dummy, WSAID_DISCONNECTEX, reinterpret_cast<LPVOID*>(&DisconnectEx)))
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
		printf_s("WSASocket Failed : %d", WSAGetLastError());
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
