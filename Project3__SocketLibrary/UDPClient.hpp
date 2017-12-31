#pragma once

#include "BaseSocket.hpp"

class UDPClient : BaseSocket {
	sockaddr_in serverAddress;
public:

	UDPClient(unsigned short portParam = DEFAULT_PORT, std::string addr= DEFAULT_ADDRESS);
	//send
	void Send(std::string msg);//you can replace with any type! for now, string.
	std::string Receive(); //return

						   //dtor is already defined in BaseSocket:-)
};