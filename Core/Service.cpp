#include "pch.h"
#include "Service.h"

Service::Service(IocpCoreSharedPtr pIocpCore) : m_pIocpCore(pIocpCore)
{

}

Service::~Service()
{

}

bool Service::Start()
{
	try
	{
		m_pListener = std::make_shared<Listener>();
	}
	catch (std::bad_alloc& e)
	{
		printf_s("Failed to alloc Listener class, errCode = %d", GetLastError());
		return false;
	}



}
