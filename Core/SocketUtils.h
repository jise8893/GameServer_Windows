#pragma once
class SocketUtils
{
public:
	static LPFN_ACCEPTEX		AcceptEx;
	static LPFN_CONNECTEX		ConnectEx;
	static LPFN_DISCONNECTEX	DisconnectEx;
public:
	static BOOL		Init();
	static SOCKET	CreateSocket();
	static BOOL		SetReuseAddress(SOCKET socket, bool reuse = true);
	

	// fn SetTcpNoDelay
	// @brief TCP ������ Nagle �˰��� ��� ���� ���� ��Ŷ���� �������� ��� �����Ѵ�.
	static BOOL		SetTcpNoDelay(SOCKET socket, bool noDelay = true);
	// @fn SetLinger
	// @brief tcp ������ ����� �� ���� ������ ó�� ��� 
	static BOOL		SetLinger(SOCKET socket, bool enable, int lingerTime = 0);

	static BOOL		BindAddress(SOCKET socket, const WCHAR* address, int port);
	static BOOL		BindAnyAddress(SOCKET socket, int port);
	static BOOL		Listen(SOCKET socket, int backlog);
	static BOOL		BindWindowsFunction(SOCKET  socket, GUID guid, LPVOID* fn);
};
 

