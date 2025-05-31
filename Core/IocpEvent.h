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
	void Init();
	std::shared_ptr<IocpObject> GetOwner();
private:
	EventType	m_type;
	std::shared_ptr<IocpObject> m_pOwner;

};

