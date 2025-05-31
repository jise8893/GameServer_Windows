#pragma once
#include <WinSock2.h>

class AutoCloseSocket
{
public:
    AutoCloseSocket();
    AutoCloseSocket(SOCKET socket);

    // 소켓을 소유 하는 객체에서 소멸자에서 소켓을 닫는다.
    ~AutoCloseSocket();

    AutoCloseSocket& operator=(SOCKET socket);
    // 연산자 오버로딩을 통해 소켓을 직접 사용
    constexpr operator SOCKET() const noexcept { return m_socket; }
    operator HANDLE() { return reinterpret_cast<HANDLE>(m_socket); }

private:
    SOCKET m_socket; 
};


