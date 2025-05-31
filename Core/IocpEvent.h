#pragma once
#include <Windows.h>

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

class IocpEvent : public OVERLAPPED
{
public:
	IocpEvent(EventType type);
	virtual ~IocpEvent();

	void Init();
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
	{
	}

};

class SendEvent : public IocpEvent
{
public:
	SendEvent() : IocpEvent(EventType::SEND)
	{
	}

};

class RecvEvent : public IocpEvent
{
public:
	RecvEvent() :IocpEvent(EventType::RECV)
	{
	}
};

