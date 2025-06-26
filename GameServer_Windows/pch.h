#pragma once
#include <winsock2.h>
#include <mswsock.h>
#include <WS2tcpip.h>
#include <memory>

#define WIN32_LEAN_AND_MEAN

#pragma comment(lib, "abseil_dll.lib")
#ifdef _DEBUG
#pragma comment(lib, "libprotobufd.lib")
#else
#pragma comment(lib, "libprotobuf.lib")
#endif