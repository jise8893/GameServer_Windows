
#include "pch.h"
#include "GameSession.h"

void GameSession::OnConnected()
{
	printf("OnConnected\n");
}
int32_t GameSession::OnRecv(void* buffer, int32_t numOfBytes)
{
	printf("OnRecv: %d bytes\n", numOfBytes);
	return numOfBytes;
}
void GameSession::OnSend(int32_t numOfBytes)
{
	printf("OnSend: %d bytes\n", numOfBytes);
	return;
}