//#include <Project3__SocketLibrary.lib>
#include "../Project3__SocketLibrary/TCPClient.hpp"
#include "../Project3__SocketLibrary/UDPClient.hpp"
using namespace std;

#include <iostream>
#include <string>

int main() {
	char ch;
	
	//could be either tcp or udp 
	TCPClient client = TCPClient();
	client.Send("hello!!!!!!!");
	string messageYouGot = "Nothing";
	while (messageYouGot == "Nothing") {
		messageYouGot = client.Receive();
	}
	cout << messageYouGot;

	/**************(WORKING UDP :-)******************/
	//UDPClient client = UDPClient();
	//string messageYouGot = "Nothing";
	//client.Send("hello!!!!!!!"); //NOTE!!!! send from client first. server waits to receive before sending
	//while (messageYouGot == "Nothing")
	//	messageYouGot = client.Receive();
	//
	//cout << messageYouGot;

	
	cin >> ch;

	
}