#pragma once
#include "Service.h"
#include "IocpCore.h"
class ClientService : public Service
{
public:
	ClientService(std::shared_ptr<IocpCore> pIocpCore);
	virtual ~ClientService();

	virtual bool Start(IN const WCHAR* address, IN const int port) override;
};

