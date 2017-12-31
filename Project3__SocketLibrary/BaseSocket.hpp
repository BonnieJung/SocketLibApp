#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <string>
#pragma comment (lib,"ws2_32.lib")

unsigned short constexpr DEFAULT_PORT = 49153;
std::string const DEFAULT_ADDRESS = "127.0.0.1";
std::string const TERMINATING_MESSAGE = "Terminating!!";
int const MAX_CHARACTER = 256;

class BaseSocket {
protected:
	// Create the UDP socket
	SOCKET hSocket;
	WSAData wsaData;//it should be here because WSAData will be removed in dtor 
	unsigned short port;
public:
	~BaseSocket() {
		// terminate. 
		closesocket(hSocket);
		WSACleanup();
	}
};