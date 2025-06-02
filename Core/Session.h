#pragma once


#include "IocpEvent.h"
#include "IocpCore.h"
#include "AutoCloseSocket.h"
#include "RecvBuffer.h"
#include "SendBuffer.h"
#include "ReaderWriterLock.h"
#include <queue>
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

	Session(); 
	virtual ~Session();


	virtual void		Dispatch(IocpEvent* iocpEvent, DWORD numOfBytes) override;
	virtual HANDLE		GetHandle() override;
	void				ProcessConnect();
	void				ProcessDisConnect();
	void				ProcessSend(DWORD numOfBytes);
	void				ProcessRecv(DWORD numOfBytes);

	void				RegisterRecv();
	void				RegisterSend();
	void				DisConnect();
	bool				RegisterConnect(IN const WCHAR* address, IN const int port);

	void				SetService(ServiceSharedPtr pService);
	void				Send(SendBufferSharedPtr pSendBuffer);
public:
	// Ŭ��/���� ������ �� ���� �ڵ�
	virtual void		OnConnected() {};
	virtual int32_t		OnRecv(void* buffer, int32_t numOfBytes) { return numOfBytes; }
	virtual void		OnSend(int32_t numOfBytes) {};
private:
	RecvEvent				m_recvEvent;
	SendEvent				m_sendEvent;
	ConnectEvent			m_connectEvent;
	DisConnectEvent			m_disConnectEvent;
	AutoCloseSocket			m_socket; // �Ҹ��ڿ��� ���� ���� ó���ϴ� Ŭ����
	ServiceSharedPtr		m_pService; 
private:
	std::atomic_bool		m_bRegistedSend;// Send�� ����ؼ� ȣ������ �ʰ� SendQueue�� ��Ƽ� �ϳ��� �����常 �����ϵ��� Ǯ��
	std::queue<SendBufferSharedPtr>	m_sendQ;		// SendBuffer���� ������ �����͸� ť���Ѵ�.
	Lock					m_sendLock;		// sendQ ����ȭ ���ɶ�
public:
	std::atomic_bool		m_bIsConnected;
	RecvBuffer				m_recvBuffer;
};

