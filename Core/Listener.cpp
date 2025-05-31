#include "pch.h"
#include "Listener.h"


void Listener::Dispatch(IocpEvent* iocpEvent, DWORD numOfBytes)
{
	if (iocpEvent->GetType() == EventType::ACCEPT)
	{

	}
}

void Listener::RegisterAccept()
{

}

void Listener::ProcessAccept()
{
}
