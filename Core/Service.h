#pragma once
#include "Listener.h"


using IocpCoreSharedPtr = std::shared_ptr<IocpCore>;

class Service : public std::enable_shared_from_this<Service>
{
public:
	Service(IocpCoreSharedPtr pIocpCore);
	virtual ~Service();

	bool	Start();

private:
	std::shared_ptr<Listener> m_pListener;
	IocpCoreSharedPtr m_pIocpCore;
};

