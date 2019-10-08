#pragma once
#include <WinSock2.h>
#include <stdio.h>
#include "..\..\Common\Macro.h"
#include "..\..\Common\NetworkManager.h"

#define	MAX_BUFFER		1024
#define SERVER_IP		"127.0.0.1"
#define SERVER_PORT		9000

struct SOCKET_INFO
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
private:
	static IOCompletionPort* instance;

	IOCompletionPort();

public:
	~IOCompletionPort();

	// ���� ��� �� ���� ���� ����
	bool Init();
	// Ŭ�� ����
	void StartClient();
	// �۾� ������ ����
	bool CreateWorkerThread();
	// �۾� ������
	void WorkerThread();
	// ��Ŷ ����Ʈ ���� ó��
	void ProcessClientReceive(PACKET_INFO* packet, char * buf, int & len);
	// ��Ŷ ó��
	bool ProcessClientPacket(PACKET_INFO* packet, char * buf, int & len);

	inline SOCKET GetClientSocket()
	{
		return clientSocket;
	}

	inline static IOCompletionPort* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new IOCompletionPort();
		}
		return instance;
	}

	inline static void FreeInstance()
	{
		if (instance != nullptr)
		{
			SAFE_DELETE(instance);
		}
	}

private:
	SOCKET_INFO *	socketInfo;		// ���� ����
	SOCKET			clientSocket;	// Ŭ�� ����
	PACKET_INFO*	packet;			// ��Ŷ ����
	HANDLE			hIOCP;			// IOCP ��ü �ڵ�
	bool			bAccept;		// ��û ���� �÷���
	bool			bWorkerThread;	// �۾� ������ ���� �÷���
	HANDLE*			workerHandle;	// �۾� ������ �ڵ�
};