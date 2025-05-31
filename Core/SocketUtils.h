#pragma once
class SocketUtils
{
private:
	static LPFN_ACCEPTEX		m_lpfnAcceptEx;
	static LPFN_CONNECTEX		m_lpfnConnectEx;
	static LPFN_DISCONNECTEX	m_lpfnDisconnectEx;
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
 

