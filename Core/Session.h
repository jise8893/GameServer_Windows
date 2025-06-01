#pragma once


#include "IocpEvent.h"
#include "IocpCore.h"
#include "AutoCloseSocket.h"
#include "RecvBuffer.h"
#include "SendBuffer.h"
#include "ReaderWriterLock.h"

class Service;
using ServiceSharedPtr = std::shared_ptr<Service>;
using SendBufferSharedPtr = std::shared_ptr<SendBuffer>;

class Session : public IocpObject
{
	enum
	{
		BUFFER_SIZE = 0x1000,
	};
public:
	Session() = delete;

	Session(ServiceSharedPtr pService); 
	virtual ~Session();


	virtual void	Dispatch(IocpEvent* iocpEvent, DWORD numOfBytes) override;
	virtual HANDLE	GetHandle() override;
	void			ProcessConnect();
	void			ProcessDisConnect();
	void			ProcessSend(DWORD numOfBytes);

	void			RegisterDisConnect();
	void			RegisterRecv();
	void			RegisterSend();
	void			DisConnect();



	void			Send(SendBufferSharedPtr pSendBuffer);
public:
	// 클라/서버 컨텐츠 단 구현 코드
	virtual void OnConnected() {};
	virtual void OnRecv() {};
	virtual void OnSend() {};
private:
	RecvEvent			m_recvEvent;
	SendEvent			m_sendEvent;
	DisConnectEvent		m_disConnectEvent;
	AutoCloseSocket		m_socket; // 소멸자에서 소켓 종료 처리하는 클래스
	ServiceSharedPtr	m_pService; 
private:
	std::atomic_bool		m_bRegistedSend;// Send를 계속해서 호출하지 않고 SendQueue로 모아서 하나의 스레드만 전송하도록 풀링
	std::queue<SendBufferSharedPtr>	m_sendQ;		// SendBuffer에서 전송할 데이터를 큐잉한다.
	Lock					m_sendLock;		// sendQ 동기화 스핀락
public:
	RecvBuffer			m_recvBuffer;
};

