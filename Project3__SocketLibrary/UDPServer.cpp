#include "UDPServer.hpp"
#include <iostream>
using namespace std;


UDPServer::UDPServer(unsigned short portParam){
//initialize WSA
int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
if (iResult != 0) {
	cerr << "WSAStartup failed: UDPServer not working." << iResult << endl;
}
else {
	// Create the UDP socket
	hSocket = socket(AF_INET, SOCK_DGRAM, 0);

	// Create the server address
	serverAddress = { 0 };
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(port);
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);

	int res = bind(hSocket, reinterpret_cast<sockaddr*>(&serverAddress), sizeof(sockaddr_in));
	if (res == SOCKET_ERROR) {
		cerr << "Error on bind\n";
		res = WSAGetLastError();
		cout << "Result: " << res << endl;
		closesocket(hSocket);
		cerr << "Error on bind : UDPServer is not working.\n";
	}
	else {
		cout << "UDP socket bound\n";
	}	
}

	}//end of ctor

void UDPServer::Send(string msg){
	//sendto(hSocket, msg.c_str(), msg.size(), 0, &clientAddress, cbClientAddress);
	if (msg.size() > MAX_CHARACTER) {
		unsigned offset = 0;
		for (; offset + MAX_CHARACTER < msg.size(); offset += MAX_CHARACTER) {
			string msgPiece = msg.substr(offset, MAX_CHARACTER);
			sendto(hSocket, msgPiece.c_str(), msgPiece.size(), 0, &clientAddress, cbClientAddress);

		}
		string msgPiece = msg.substr(offset);
		sendto(hSocket, msgPiece.c_str(), msgPiece.size(), 0, &clientAddress, cbClientAddress);

	}
	else {
		sendto(hSocket, msg.c_str(), msg.size(), 0, &clientAddress, cbClientAddress);
	}

}

string UDPServer::Receive(){ //return with string

	string whatYouGot;
	char msg[MAX_CHARACTER + 1];
	int n = recvfrom(hSocket, msg, MAX_CHARACTER, 0, &clientAddress, &cbClientAddress);
	whatYouGot = msg;

	for (unsigned i = 0; i < whatYouGot.size(); ++i) {
		if (whatYouGot.at(i) < 32) { //ANSI character less than 32 is invalid character
			whatYouGot.erase(i);
			--i;
		}
	}
	return whatYouGot;
}