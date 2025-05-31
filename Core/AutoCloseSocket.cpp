#include "pch.h"
#include "AutoCloseSocket.h"

AutoCloseSocket::AutoCloseSocket() : m_socket(INVALID_SOCKET)
{

}

AutoCloseSocket::AutoCloseSocket(SOCKET socket) : m_socket(socket)
{
}

AutoCloseSocket::~AutoCloseSocket()
{
    if (m_socket != INVALID_SOCKET)
    {
		::shutdown(m_socket, SD_BOTH); // TCP 통신에서 종료 신호를 보내기 위해 호출한다.
        ::closesocket(m_socket);
        m_socket = INVALID_SOCKET;
    }
}