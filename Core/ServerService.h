#pragma once
#include "Service.h"
#include "IocpCore.h"
class ServerService : public Service
{
public:
	ServerService(std::shared_ptr<IocpCore> pIocpCore, std::function<SessionSharedPtr()> function);
	virtual ~ServerService();
	virtual bool Start(IN const WCHAR* address, IN const int port) override;
};

