#pragma comnet(lib, "ws2_32")
#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>

#define SERVERPORT 9000
#define BUFSIZE 512

// ���� ���� ������ ���� ����ü�� ����
struct SOCKETINFO
{
	WSAOVERLAPPED overlapped;
	SOCKET sock;
	char buf[BUFSIZE + 1];
	int recvbytes;
	int sendbytes;
	WSABUF wsabuf;
};

SOCKET client_sock;
HANDLE hReadEvent, hWriteEvent;

// �񵿱� ����� ���۰� ó�� �Լ�
DWORD WINAPI WorkerThread(LPVOID ard);
void CALLBACK CompletionRoutine(DWORD dwError, DWORD cbTransferred, LPWSAOVERLAPPED lpOverlapped, DWORD dwFlags);
// ���� ��� �Լ�
void err_quit(const char *msg);
void err_display(const char *msg);
void err_display(int errcode);

int main(int argx, char *argv[])
{
	int retval;

	// ���� �ʱ�ȭ
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	// socket()
	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sock == INVALID_SOCKET)
		err_quit("socket()");

	// bind()
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = bind(listen_sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR)
		err_quit("bind()");

	// listen()
	retval = listen(listen_sock, SOMAXCONN);
	if (retval == SOCKET_ERROR)
		err_quit("listen()");

	// �̺�Ʈ ��ü ����
	hReadEvent = CreateEvent(NULL, FALSE, TRUE, NULL);
	if (hReadEvent == NULL)
		return 1;
	hWriteEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	if (hWriteEvent == NULL)
		return 1;

	// ������ ����
	HANDLE hTread = CreateThread(NULL, 0, WorkerThread, NULL, 0, NULL);
	if (hTread == NULL)
		return 1;
	CloseHandle(hTread);

	while (1)
	{
		WaitForSingleObject(hReadEvent, INFINITE);
		// accept()
		client_sock = accept(listen_sock, NULL, NULL);
		if (client_sock = INVALID_SOCKET)
		{
			err_display("accept()");
			break;
		}
		SetEvent(hWriteEvent);
	}

	// ���� ����
	WSACleanup();
	return 0;

}

// �񵿱� ����� ���� �Լ�
DWORD WINAPI WorkerTread(LPVOID arg)
{
	int retval;

	while (1)
	{
		while (1)
		{
			//alertable wait
			DWORD result = WaitForSingleObjectEx(hWriteEvent, INFINITE, TRUE);
			if (result == WAIT_OBJECT_0)
				break;
			if (result != WAIT_IO_COMPLETION)
				return 1;
		}

		// ������ Ŭ���̾�Ʈ ���� ���
		SOCKADDR_IN clientaddr;
		int addrlen = sizeof(clientaddr);
		getpeername(client_sock, (SOCKADDR*)&clientaddr, &addrlen);
		printf("\n[TCP ����] Ŭ���̾�Ʈ ���� : IP �ּ� = %s, ��Ʈ ��ȣ = %d\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

		// ���� ���� ����ü �Ҵ�� �ʱ�ȭ
		SOCKETINFO *ptr = new SOCKETINFO;
		if (ptr == NULL)
		{
			printf("[����] �޸𸮰� �����մϴ�!\n");
			return 1;
		}
		ZeroMemory(&ptr->overlapped, sizeof(ptr->overlapped));
		ptr->sock = client_sock;
		SetEvent(hReadEvent);
		ptr->sendbytes = 0;
		ptr->sendbytes = 0;
		ptr->wsabuf.buf = ptr->buf;
		ptr->wsabuf.len = BUFSIZE;

		// �񵿱� ����� ����
		DWORD recvbytes;
		DWORD flags = 0;
		retval = WSARecv(ptr->sock, &ptr->wsabuf, 1, &recvbytes, &flags, &ptr->overlapped, CompletionRoutine);
		if (retval == SOCKET_ERROR)
		{
			err_display("WSARecv()");
			return 1;
		}
	}

	return 0;
}


// �񵿱� ����� ó�� �Լ�(����� �Ϸ� ��ƾ)
void CALLBACK CompletionRoutine(DWORD dwError, DWORD cbTransferred, LPWSAOVERLAPPED lpOverlapped, DWORD dwFlags)
{
	int retval;

	// Ŭ���̾�Ʈ ���� ���
	SOCKETINFO *ptr = (SOCKETINFO*)lpOverlapped;
	SOCKADDR_IN clientaddr;
	int addrlen = sizeof(clientaddr);
	getpeername(ptr->sock, (SOCKADDR*)&clientaddr, &addrlen);
	
	// �񵿱� ����� ��� Ȯ��
	if (dwError != 0 || cbTransferred == 0)
	{
		if (dwError != 0)
		{
			err_display(dwError);
			closesocket(ptr->sock);
			printf("[TCP ����] Ŭ���̾�Ʈ ���� : IP �ּ� = %s, ��Ʈ ��ȣ = %d\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
			delete ptr;
			return;
		}
	}

	// ������ ���۷� ����
	if (ptr->recvbytes == 0)
	{
		ptr->recvbytes = cbTransferred;
		ptr->sendbytes = 0;
		// ���� ������ ���
		ptr->buf[ptr->recvbytes] = '\0';
		printf("[TCP/%s:%d] %s\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port), ptr->buf);
	}
	else
	{
		ptr->sendbytes += cbTransferred;
	}

	if (ptr->recvbytes > ptr->sendbytes)
	{
		// ������ ������
	}
}