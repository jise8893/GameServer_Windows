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
	// Ŭ��/���� ������ �� ���� �ڵ�
	virtual void OnConnected() {};
	virtual void OnRecv() {};
	virtual void OnSend() {};
private:
	RecvEvent			m_recvEvent;
	SendEvent			m_sendEvent;
	DisConnectEvent		m_disConnectEvent;
	AutoCloseSocket		m_socket; // �Ҹ��ڿ��� ���� ���� ó���ϴ� Ŭ����
	ServiceSharedPtr	m_pService; 
private:
	std::atomic_bool		m_bRegistedSend;// Send�� ����ؼ� ȣ������ �ʰ� SendQueue�� ��Ƽ� �ϳ��� �����常 �����ϵ��� Ǯ��
	std::queue<SendBufferSharedPtr>	m_sendQ;		// SendBuffer���� ������ �����͸� ť���Ѵ�.
	Lock					m_sendLock;		// sendQ ����ȭ ���ɶ�
public:
	RecvBuffer			m_recvBuffer;
};

