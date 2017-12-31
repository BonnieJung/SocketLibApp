#include "TCPClient.hpp"
#include <iostream>
#include <sstream>
using namespace std;

TCPClient::TCPClient(unsigned short portParam, string addr) {
	// initialize WSA
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		cerr << "WSAStartup failed: TCPClient failed to start." << iResult << endl;
	}
	else {
		// Create the TCP socket
		hSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

		// Create the server address
		serverAddress = { 0 };
		serverAddress.sin_family = AF_INET;
		serverAddress.sin_port = htons(port);
		serverAddress.sin_addr.s_addr = inet_addr(addr.c_str());

		// connect the socket
		if (connect(hSocket, (SOCKADDR*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
			cerr << "Connect() failed : TCPClient\n";
			
		}
	}



}


//send
void TCPClient::Send(string msg) {
	if (msg.size() > MAX_CHARACTER) {
		unsigned offset = 0;
		for (; offset + MAX_CHARACTER < msg.size(); offset += MAX_CHARACTER) {
			string msgPiece = msg.substr(offset, MAX_CHARACTER);
			//sendto(hSocket, msgPiece.c_str(), msgPiece.size(), 0, (sockaddr*)&serverAddress, sizeof(serverAddress));
			send(hSocket, msgPiece.c_str(), msgPiece.size() + 1, 0);

		}
		string msgPiece = msg.substr(offset);
		//sendto(hSocket, msgPiece.c_str(), msgPiece.size(), 0, (sockaddr*)&serverAddress, sizeof(serverAddress));
		send(hSocket, msgPiece.c_str(), msgPiece.size() + 1, 0);
		
	}
	else {
		//sendto(hSocket, msg.c_str(), msg.size(), 0, (sockaddr*)&serverAddress, sizeof(serverAddress));
		send(hSocket, msg.c_str(), msg.size() + 1, 0);
	}
	
}//you can replace with any type! for now, string.

 //receive
string TCPClient::Receive() {
	//stringstream whatYouGot;
	//char msgAsArry[MAX_CHARACTER + 1];
	//int n = recvfrom(hSocket, msgAsArry, MAX_CHARACTER, 0, NULL, NULL);
	//if (n == -1)
	//	cout << "no reply" << endl;
	//else {
	//	whatYouGot << msgAsArry;
	//}

	string whatYouGot;
	char msgAsArry[MAX_CHARACTER + 1];
	int n = -1;
	unsigned count = 0;
	while (n == -1 & ++count < 500) { //500 is random number for looping it.(half a second)
		//n = recvfrom(hSocket, msgAsArry, MAX_CHARACTER, 0, NULL, NULL);
		n = recv(hSocket, msgAsArry, (sizeof(msgAsArry) / sizeof(msgAsArry[0])), 0);
		/*if (n == -1)
		cout << "no reply" << endl;
		else {*/
		if (n != -1)
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