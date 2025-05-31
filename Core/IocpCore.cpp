#include "pch.h"
#include "IocpCore.h"
#include "IocpEvent.h"

IocpCore::IocpCore()
{
	m_hIocp = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0);
}

IocpCore::~IocpCore()
{
	::CloseHandle(m_hIocp);
}
bool IocpCore::Dispatch()
{
	DWORD numOfBytes = 0;
	ULONG_PTR key = 0;
	IocpEvent* iocpEvent = nullptr;

	if(::GetQueuedCompletionStatus(m_hIocp, &numOfBytes, &key, reinterpret_cast<LPOVERLAPPED*>(&iocpEvent), INFINITE))
	{
		std::shared_ptr<IocpObject> pIocpObject = iocpEvent->GetOwner();
		pIocpObject->Dispatch(iocpEvent, numOfBytes);
		
	}
	else
	{
		int32_t errCode = ::WSAGetLastError();
		printf_s("WSAGetLastError = %d, Line = %s", errCode, __LINE__);
	}

	return true;
}

bool IocpCore::Register(std::shared_ptr<IocpObject> pIocpObject)
{
	return ::CreateIoCompletionPort(pIocpObject->GetHandle(), m_hIocp, 0, 0);
}

