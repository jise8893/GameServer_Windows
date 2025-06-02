#pragma once
#include "../Core/Session.h"
class GameSession : public Session
{
public:
	virtual void		OnConnected() override;
	virtual int32_t		OnRecv(void* buffer, int32_t numOfBytes) override;
	virtual void		OnSend(int32_t numOfBytes) override;
};

