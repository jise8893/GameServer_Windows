#include "pch.h"
#include "Session.h"
#include "SocketUtils.h"

Session::Session() : m_recvBuffer(BUFFER_SIZE)
{
	m_socket = SocketUtils::CreateSocket();
}

Session::~Session()
{

}

HANDLE Session::GetHandle()
{
	return m_socket;
}