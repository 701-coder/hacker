#include <winsock2.h>
#include <Ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#pragma comment(lib, "WS2_32")
int __cdecl main(int argc, char** argv) {
	//initialize
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	SOCKET s = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	//get the address of the server
	SOCKADDR_IN sockAddr;
	sockAddr.sin_family = AF_INET;
	sockAddr.sin_port = htons(827);
	inet_pton(AF_INET, "127.0.0.1", (void*)&sockAddr.sin_addr.S_un.S_addr);

	//connect server
	connect(s, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));

	//send message
	char szMessage[] = "Give me the money.";
	send(s, szMessage, strlen(szMessage) + sizeof(char), 0);

	//get message
	char szBuffer[MAXBYTE] = { 0 };
	recv(s, szBuffer, MAXBYTE, NULL);
	printf("szBuffer = %s \r\n", szBuffer);

	//close connection
	shutdown(s, 0);
	closesocket(s);
	WSACleanup();
	system("pause");
	return 0;
}
