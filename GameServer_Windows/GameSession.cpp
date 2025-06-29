#include "pch.h"
#include "GameSession.h"

void GameSession::OnConnected()
{
}
int32_t GameSession::OnRecv(void* buffer, int32_t numOfBytes)
{
	int processedLen = 0;
	while (true)
	{
		int32_t dataSize = numOfBytes - processedLen;

		if (dataSize < sizeof(PacketHeader))
			break;

		PacketHeader* pPacketHeader = reinterpret_cast<PacketHeader*>(buffer);
		
		if (pPacketHeader->size > dataSize)
			break;


		// TODO PacketHandler
		processedLen += pPacketHeader->size;
	}

	return processedLen;
}
void GameSession::OnSend(int32_t numOfBytes)
{
	return;
}