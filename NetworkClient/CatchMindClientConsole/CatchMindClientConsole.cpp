#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <windows.h>

#define SERVERIP "127.0.0.1"
//#define SERVERIP "10.30.10.204"
#define SERVERPORT 9000
#define BUFSIZE 512

void ErrorHandling(const char *message);

int main()
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error!");

	SOCKET hSocket = WSASocket(PF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	if (hSocket == INVALID_SOCKET)
		ErrorHandling("socket() error");

	SOCKADDR_IN recvAddr;
	memset(&recvAddr, 0, sizeof(recvAddr));
	recvAddr.sin_family = AF_INET;
	recvAddr.sin_addr.s_addr = inet_addr(SERVERIP);
	recvAddr.sin_port = htons(SERVERPORT);

	if (connect(hSocket, (SOCKADDR*)&recvAddr, sizeof(recvAddr)) == SOCKET_ERROR)
		ErrorHandling("connect() error!");

	WSAEVENT event = WSACreateEvent();

	WSAOVERLAPPED overlapped;
	memset(&overlapped, 0, sizeof(overlapped));

	overlapped.hEvent = event;

	WSABUF dataBuf;
	char message[1024] = { 0, };
	int sendBytes = 0;
	int recvBytes = 0;
	int flags = 0;

	while (true)
	{
		flags = 0;
		printf("전송할데이터(종료를원할시exit)\n");

		scanf("%s", message);

		if (!strcmp(message, "exit")) break;

		dataBuf.len = strlen(message);
		dataBuf.buf = message;

		if (WSASend(hSocket, &dataBuf, 1, (LPDWORD)&sendBytes, 0, &overlapped, NULL) == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSA_IO_PENDING)
				ErrorHandling("WSASend() error");
		}

		WSAWaitForMultipleEvents(1, &event, TRUE, WSA_INFINITE, FALSE);

		WSAGetOverlappedResult(hSocket, &overlapped, (LPDWORD)&sendBytes, FALSE, NULL);

		printf("전송된바이트수: %d \n", sendBytes);

		if (WSARecv(hSocket, &dataBuf, 1, (LPDWORD)&recvBytes, (LPDWORD)&flags, &overlapped, NULL) == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSA_IO_PENDING)
				ErrorHandling("WSASend() error");
		}

		printf("Recv[%s]\n", dataBuf.buf);
	}

	closesocket(hSocket);

	WSACleanup();

	return 0;
}

void ErrorHandling(const char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);

	exit(1);
}