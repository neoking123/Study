#pragma once
#include <WinSock2.h>
#include "..\..\Common\NetworkManager.h"

#define	MAX_BUFFER		1024
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
	// ���� ����
	void StartServer();
	// �۾� ������ ����
	bool CreateWorkerThread();
	// �۾� ������
	void WorkerThread();
	// ��Ŷ ����Ʈ ��Ʈ�� ó��
	void ProcessServerReceive(PACKET_INFO* packet, char * buf, int & len);
	// ��Ŷ ó��
	bool ProcessServerPacket(PACKET_INFO* packet, char * buf, int & len);

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
	SOCKET			listenSocket;		// ���� ���� ����
	HANDLE			hIOCP;			// IOCP ��ü �ڵ�
	bool			bAccept;			// ��û ���� �÷���
	bool			bWorkerThread;	// �۾� ������ ���� �÷���
	HANDLE *		workerHandle;	// �۾� ������ �ڵ�
};