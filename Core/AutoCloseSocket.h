#pragma once
#include <WinSock2.h>

class AutoCloseSocket
{
public:
    AutoCloseSocket();
    AutoCloseSocket(SOCKET socket);

    // ������ ���� �ϴ� ��ü���� �Ҹ��ڿ��� ������ �ݴ´�.
    ~AutoCloseSocket();

    AutoCloseSocket& operator=(SOCKET socket);
    // ������ �����ε��� ���� ������ ���� ���
    constexpr operator SOCKET() const noexcept { return m_socket; }
    operator HANDLE() { return reinterpret_cast<HANDLE>(m_socket); }

private:
    SOCKET m_socket; 
};


