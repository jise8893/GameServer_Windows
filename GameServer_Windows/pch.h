#pragma once
#include <winsock2.h>
#include <mswsock.h>
#include <WS2tcpip.h>
#include <memory>
#include <iostream>
#include <queue>
using namespace std;
#define WIN32_LEAN_AND_MEAN
#ifdef _DEBUG
#pragma comment(lib, "Debug\\libprotobufd.lib")
#else
#pragma comment(lib, "Release\\libprotobuf.lib")
#endif