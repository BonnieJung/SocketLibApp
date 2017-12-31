#include "TCPServer.hpp"

#include <iostream>
using namespace std;


TCPServer::TCPServer(unsigned short portParam, string addr) {
	//initialize WSA
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		cerr << "WSAStartup failed: TCPServer not working." << iResult << endl;
	}
	else {
		// Create the TCP!! socket
		hSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		hAccepted = SOCKET_ERROR;//check to see if connected 

								 // Create the server address
		serverAddress = { 0 };
		serverAddress.sin_family = AF_INET;
		serverAddress.sin_port = htons(port);
		serverAddress.sin_addr.s_addr = inet_addr(addr.c_str());

		int res = bind(hSocket, reinterpret_cast<sockaddr*>(&serverAddress), sizeof(sockaddr_in));
		if (res == SOCKET_ERROR) {
			cerr << "Error on bind\n";
			res = WSAGetLastError();
			cout << "Result: " << res << endl;
			closesocket(hSocket);
			cerr << "Error on bind : TCPServer is not working.\n";
		}
		else { //only required for TCP(UDP doens't care. UDP just needs a big loop for receiving. it takes whatever)

			cout << "TCP socket bound\n";
			if (listen(hSocket, 1) == SOCKET_ERROR) {
				cerr << "Error listening on socket\n";

			}
			else
			{
				cout << "TCP/IP socket is listening\n";
				while (hAccepted == SOCKET_ERROR) {
					hAccepted = accept(hSocket, NULL, NULL);
				}
				cout << "Client connected\n";
			}


		}
	}
}//end of ctor

void TCPServer::Send(string msg) {
	//sendto(hSocket, msg.c_str(), msg.size(), 0, &clientAddress, cbClientAddress);
	if (msg.size() > MAX_CHARACTER) {
		unsigned offset = 0;
		for (; offset + MAX_CHARACTER < msg.size(); offset += MAX_CHARACTER) {
			string msgPiece = msg.substr(offset, MAX_CHARACTER);
			//sendto(hSocket, msgPiece.c_str(), msgPiece.size(), 0, &clientAddress, cbClientAddress);
			send(hAccepted, msgPiece.c_str(), msgPiece.size() + 1, 0);

		}
		string msgPiece = msg.substr(offset);
		//sendto(hSocket, msgPiece.c_str(), msgPiece.size(), 0, &clientAddress, cbClientAddress);
		send(hAccepted, msgPiece.c_str(), msgPiece.size() + 1, 0);

	}
	else {
		//sendto(hSocket, msg.c_str(), msg.size(), 0, &clientAddress, cbClientAddress);
		send(hAccepted, msg.c_str(), msg.size() + 1, 0);
	}

}

string TCPServer::Receive() { //return with string

							  //stringstream whatYouGot;
							  //char msg[MAX_CHARACTER];
							  ////int n = recvfrom(hSocket, msg, MAX_CHARACTER, 0, &clientAddress, &cbClientAddress);
							  //int n = recv(hAccepted, msg, MAX_CHARACTER, 0);
							  //whatYouGot << msg;


	string whatYouGot;
	char msgAsArry[MAX_CHARACTER + 1];
	int n = -1;
	//n = recv(hSocket, msgAsArry, (sizeof(msgAsArry) / sizeof(msgAsArry[0])), 0);
	n = recv(hAccepted, msgAsArry, (sizeof(msgAsArry) / sizeof(msgAsArry[0])), 0); //server uses hAccepted, client uses hSocket

	if (n != -1)
		whatYouGot = msgAsArry;

	for (unsigned i = 0; i < whatYouGot.size(); ++i) {
		if (whatYouGot.at(i) < 32) { //ANSI character less than 32 is invalid character
			whatYouGot.erase(i);
			--i;
		}
	}

	return whatYouGot;
}




//#include "TCPServer.hpp"
//#include <iostream>
//#include <sstream>
//using namespace std;
//
//
//TCPServer::TCPServer(unsigned short portParam, string addr) {
//	//initialize WSA
//	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
//	if (iResult != 0) {
//		cerr << "WSAStartup failed: TCPServer not working." << iResult << endl;
//	}
//	else {
//		// Create the TCP!! socket
//		hSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//		hAccepted = SOCKET_ERROR;//check to see if connected 
//
//		// Create the server address
//		serverAddress = { 0 };
//		serverAddress.sin_family = AF_INET;
//		serverAddress.sin_port = htons(port);
//		serverAddress.sin_addr.s_addr = inet_addr(addr.c_str());
//
//		int res = bind(hSocket, reinterpret_cast<sockaddr*>(&serverAddress), sizeof(sockaddr_in));
//		if (res == SOCKET_ERROR) {
//			cerr << "Error on bind\n";
//			res = WSAGetLastError();
//			cout << "Result: " << res << endl;
//			closesocket(hSocket);
//			cerr << "Error on bind : TCPServer is not working.\n";
//		}
//		else { //only required for TCP(UDP doens't care. UDP just needs a big loop for receiving. it takes whatever)
//
//			cout << "TCP socket bound\n";
//			if (listen(hSocket, 1) == SOCKET_ERROR) {
//				cerr << "Error listening on socket\n";
//
//			}
//			else
//			{
//				cout << "TCP/IP socket is listening\n";
//				while (hAccepted == SOCKET_ERROR) {
//					hAccepted = accept(hSocket, NULL, NULL);
//				}
//				cout << "Client connected\n";
//			}
//
//
//		}
//	}
//}//end of ctor
//
//void TCPServer::Send(string msg) {
//	//sendto(hSocket, msg.c_str(), msg.size(), 0, &clientAddress, cbClientAddress);
//	if (msg.size() > MAX_CHARACTER) {
//		unsigned offset = 0;
//		for (; offset + MAX_CHARACTER < msg.size(); offset += MAX_CHARACTER) {
//			string msgPiece = msg.substr(offset, MAX_CHARACTER);
//			sendto(hSocket, msgPiece.c_str(), msgPiece.size(), 0, &clientAddress, cbClientAddress);
//
//		}
//		string msgPiece = msg.substr(offset);
//		sendto(hSocket, msgPiece.c_str(), msgPiece.size(), 0, &clientAddress, cbClientAddress);
//
//	}
//	else {
//		sendto(hSocket, msg.c_str(), msg.size(), 0, &clientAddress, cbClientAddress);
//	}
//
//}
//
//string TCPServer::Receive() { //return with string
//
//	stringstream whatYouGot;
//	char msg[MAX_CHARACTER + 1];
//	int n = recvfrom(hSocket, msg, MAX_CHARACTER, 0, &clientAddress, &cbClientAddress);
//	whatYouGot << msg;
//	return whatYouGot.str();
//}