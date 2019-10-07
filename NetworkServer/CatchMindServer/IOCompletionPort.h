#pragma once
#include <WinSock2.h>
#include <stdio.h>

#define	MAX_BUFFER		1024
#define SERVER_PORT		9000

struct SOCKETINFO
{
	WSAOVERLAPPED	overlapped;
	WSABUF			dataBuf;
	SOCKET			socket;
	char			messageBuffer[MAX_BUFFER];
	int				recvBytes;
	int				sendBytes;
};

class IOCompletionPort
{
public:
	IOCompletionPort();
	~IOCompletionPort();

	// ���� ��� �� ���� ���� ����
	bool Initialize();
	// ���� ����
	void StartServer();
	// �۾� ������ ����
	bool CreateWorkerThread();
	// ���� ������ ����
	bool CreateAcceptThread();
	// �۾� ������
	void WorkerThread();
	// ���� ������
	void AcceptThread();

private:
	SOCKETINFO *	socketInfo;		// ���� ����
	SOCKET			listenSocket;		// ���� ���� ����
	HANDLE			hIOCP;			// IOCP ��ü �ڵ�
	bool			bAccept;			// ��û ���� �÷���
	bool			bWorkerThread;	// �۾� ������ ���� �÷���
	bool			bAcceptThread;	// ���� ������ ���� �÷���
	HANDLE *		workerHandle;	// �۾� ������ �ڵ�
	HANDLE *		acceptHandle;	// ���� ������ �ڵ�
};