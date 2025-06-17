#pragma once
#include "Service.h"
#include "IocpCore.h"
class ClientService : public Service
{
public:
	ClientService(std::shared_ptr<IocpCore> pIocpCore, std::function<SessionSharedPtr()> function);
	virtual ~ClientService();

	virtual bool Start(IN const WCHAR* address, IN const int port) override;
};

