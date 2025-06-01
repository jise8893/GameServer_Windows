#pragma once
#include <Windows.h>
#include "SendBuffer.h"
enum class EventType : uint8_t
{
	CONNECT,
	DISCONNECT,
	ACCEPT,
	RECV,
	SEND,
	END
};

class IocpObject;
class Session;
class IocpEvent : public OVERLAPPED
{
public:
	IocpEvent(EventType type);
	virtual ~IocpEvent();

	void Init();

	void SetOwner(std::shared_ptr<IocpObject> pIocpObject);
	std::shared_ptr<IocpObject> GetOwner();
	EventType GetType() { return m_type; }
private:
	EventType	m_type;
	std::shared_ptr<IocpObject> m_pOwner;

};

class AcceptEvent : public IocpEvent
{
public:
	AcceptEvent() : IocpEvent(EventType::ACCEPT)
	{ }
public:
	std::shared_ptr<Session> m_pSession;
};

class SendEvent : public IocpEvent
{
public:
	SendEvent() : IocpEvent(EventType::SEND)
	{
	}
public:
	std::vector<std::shared_ptr<SendBuffer>> m_vecSendBuffer;
};

class RecvEvent : public IocpEvent
{
public:
	RecvEvent() :IocpEvent(EventType::RECV)
	{ 
	}
};

class DisConnectEvent : public IocpEvent
{
public:
	DisConnectEvent() : IocpEvent(EventType::DISCONNECT)
	{
	}
};

class ConnectEvent : public IocpEvent
{
public:
	ConnectEvent(): IocpEvent(EventType::CONNECT)
	{ }
};