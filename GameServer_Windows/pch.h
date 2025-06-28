#pragma once
#include <winsock2.h>
#include <mswsock.h>
#include <WS2tcpip.h>
#include <memory>

#define WIN32_LEAN_AND_MEAN
#ifdef _DEBUG
#pragma comment(lib, "Debug\\dll\\libprotobufd.dll")
#else
#pragma comment(lib, "Release\\dll\\libprotobuf.dll")
#endif