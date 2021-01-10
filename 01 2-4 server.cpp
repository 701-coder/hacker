#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#pragma comment(lib, "WS2_32")
int __cdecl main(void) {
	//initialize
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	sockaddr_in sockaddr;
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_port = htons(827);
	sockaddr.sin_addr.S_un.S_addr = INADDR_ANY;

	//bind communication
	bind(s, (SOCKADDR*)&sockaddr, sizeof(SOCKADDR));
	listen(s, 1);
	SOCKADDR clientAddr;
	int nSize = sizeof(SOCKADDR);
	SOCKET clientSock;

	//get the socket communicating with client
	clientSock = accept(s, (SOCKADDR*)&clientAddr, &nSize);
	char inbuf[1024];

	//get message
	recv(clientSock, inbuf, sizeof(inbuf), NULL);
	printf("Receive: %s\r\n", inbuf);
	char outbuf[] = "Hello Polaris\r\n";

	//send message
	send(clientSock, outbuf, strlen(outbuf) + sizeof(char), NULL);

	//close the communication
	shutdown(clientSock, 0);
	closesocket(clientSock);

	//close server
	closesocket(s);
	WSACleanup();
	system("pause");
	return 0;
}
