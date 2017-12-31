#include "UDPClient.hpp"
#include <iostream>
using namespace std;

UDPClient::UDPClient(unsigned short portParam, string addr) {
	// initialize WSA
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		cerr << "WSAStartup failed: UDPClient failed to start." << iResult << endl;
	}
	else {
		// Create the UDP socket
		hSocket = socket(AF_INET, SOCK_DGRAM, 0);

		// Create the server address
		serverAddress = { 0 };
		serverAddress.sin_family = AF_INET;
		serverAddress.sin_port = htons(port);
		serverAddress.sin_addr.s_addr = inet_addr(addr.c_str());
	}

}


//send
void UDPClient::Send(string msg) {
	if (msg.size() > MAX_CHARACTER) {
		unsigned offset = 0;
		for (; offset + MAX_CHARACTER < msg.size(); offset += MAX_CHARACTER) {
			string msgPiece = msg.substr(offset, MAX_CHARACTER);
			sendto(hSocket, msgPiece.c_str(), msgPiece.size(), 0, (sockaddr*)&serverAddress, sizeof(serverAddress));

		}
		string msgPiece = msg.substr(offset);
		sendto(hSocket, msgPiece.c_str(), msgPiece.size(), 0, (sockaddr*)&serverAddress, sizeof(serverAddress));

	}
	else {
		sendto(hSocket, msg.c_str(), msg.size(), 0, (sockaddr*)&serverAddress, sizeof(serverAddress));
	}
}//you can replace with any type! for now, string.

//receive
string UDPClient::Receive() {
	string whatYouGot;
	char msgAsArry[MAX_CHARACTER+1];
	int n = -1;
	unsigned count = 0;
	while (n == -1 & ++count < 500) { //500 is random number for looping it.(half a second)
		n = recvfrom(hSocket, msgAsArry, MAX_CHARACTER, 0, NULL, NULL);
		/*if (n == -1)
			cout << "no reply" << endl;
		else {*/
		if(n != -1)
			whatYouGot = msgAsArry;
		//}
	}

	for (unsigned i = 0; i < whatYouGot.size(); ++i) {
		if (whatYouGot.at(i) < 32) { //ANSI character less than 32 is invalid character
			whatYouGot.erase(i);
			--i;
		}
	}
	return whatYouGot;
}//return