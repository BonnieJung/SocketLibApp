#pragma once
#include "BaseSocket.hpp"


class UDPServer : BaseSocket {
	sockaddr clientAddress;
	sockaddr_in  serverAddress;
	socklen_t cbClientAddress = sizeof(clientAddress);
public:

	UDPServer(unsigned short portParam = DEFAULT_PORT);
	//send
	void Send(std::string msg);//you can replace with any type! for now, string.
	std::string Receive(); //return
	
	//dtor is already defined in BaseSocket:-)
};