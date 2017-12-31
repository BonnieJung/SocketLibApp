#pragma once
#include "BaseSocket.hpp"


class TCPServer : BaseSocket {
	sockaddr clientAddress;
	sockaddr_in  serverAddress;
	socklen_t cbClientAddress = sizeof(clientAddress);
	SOCKET hAccepted;
public:

	TCPServer(unsigned short portParam = DEFAULT_PORT, std::string addr = DEFAULT_ADDRESS);
	//send
	void Send(std::string msg);//you can replace with any type! for now, string.
	std::string Receive(); //return

						   //dtor is already defined in BaseSocket:-)
	~TCPServer() {
		closesocket(hAccepted); //super dtor will be done anyways.
	}
};