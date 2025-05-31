#pragma once
#include <WinSock2.h>

class AutoCloseSocket
{
public:
    AutoCloseSocket();
    AutoCloseSocket(SOCKET socket);

    // ������ ���� �ϴ� ��ü���� �Ҹ��ڿ��� ������ �ݴ´�.
    ~AutoCloseSocket();

    // ������ �����ε��� ���� ������ ���� ���
    constexpr operator SOCKET() const noexcept { return m_socket; }

private:
    SOCKET m_socket; 
};


