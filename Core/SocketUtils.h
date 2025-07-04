#pragma once
class SocketUtils
{
public:
	static LPFN_ACCEPTEX		AcceptEx;
	static LPFN_CONNECTEX		ConnectEx;
	static LPFN_DISCONNECTEX	DisconnectEx;
public:
	static BOOL		Init();
	static BOOL		Clear();
	static SOCKET	CreateSocket();
	static BOOL		SetReuseAddress(SOCKET socket, bool reuse = true);
	

	// fn SetTcpNoDelay
	// @brief TCP 소켓의 Nagle 알고리즘 사용 여부 설정 패킷전송 지연없이 즉시 전송한다.
	static BOOL		SetTcpNoDelay(SOCKET socket, bool noDelay = true);
	// @fn SetLinger
	// @brief tcp 소켓이 종료될 때 남은 데이터 처리 방식 
	static BOOL		SetLinger(SOCKET socket, bool enable, int lingerTime = 0);

	static BOOL		BindAddress(SOCKET socket, const WCHAR* address, int port);
	static BOOL		BindAnyAddress(SOCKET socket, int port);
	static BOOL		Listen(SOCKET socket, int backlog);
	static BOOL		BindWindowsFunction(SOCKET  socket, GUID guid, LPVOID* fn);
};
 

