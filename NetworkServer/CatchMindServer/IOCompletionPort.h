#pragma once
#include <WinSock2.h>
#include "..\..\Common\NetworkManager.h"
using namespace std;

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

/**
* @brief Input/Output Completion Port Ŭ����
* @details ���� ��� �� ���� ���� ����
* @details �۾� ������ ���� �� ��Ŷ ó��
* @author Dayeol Hyeon
*/

class IOCompletionPort
{
private:
	static IOCompletionPort* instance;

	IOCompletionPort();

public:
	~IOCompletionPort();

	/**
	* @brief ���� ��� �� ���� ���� ����
	* @details ���� ����ϰ� ���� ���� �����Ѵ�
	*/
	bool Init();

	/**
	* @brief ���� ����
	* @details ������ �����Ѵ�
	* @details Completion Port ��ü, Worker Thread�� �����Ѵ�
	* @details WSAAccept�� Ŭ���̾�Ʈ�� ������ �޴´�
	*/
	void StartServer();

	/**
	* @brief �۾� ������ ����
	* @details �۾� �����带 �����Ѵ�
	* @details ������ �۾� �������� ������ (CPU * 2) + 1
	*/
	bool CreateWorkerThread();

	/**
	* @brief �۾� ������
	* @details �۾� �������� ������ ó���Ѵ�
	* @details GetQueuedCompletionStatus �� �Լ��� ���� ��������� WaitingThread Queue �� �����·� ���� �ȴ�
	* @details �Ϸ�� Overlapped I/O �۾��� �߻��ϸ� IOCP Queue ���� �Ϸ�� �۾��� ������ ��ó���� �Ѵ�
	*/
	void WorkerThread();
	
	/**
	* @brief ��Ŷ ����Ʈ ��Ʈ�� ó��
	* @details ��Ŷ�� ��� ũ�⺸�� ū ��� ��Ŷ ó���� �Ѵ�
	*/
	void ProcessServerReceive(PACKET_INFO* packet, char * buf, int & len);

	/**
	* @brief ��Ŷ ó��
	* @details ������ ��Ŷ�� ����� ��� ������ �о� Ÿ�Ժ� ��Ŷ�� ó���Ѵ�
	*/
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
		SAFE_DELETE(instance);
	}

private:
	SOCKET_INFO *	socketInfo;		// ���� ����
	SOCKET			listenSocket;		// ���� ���� ����
	HANDLE			hIOCP;			// IOCP ��ü �ڵ�
	bool			bAccept;			// ��û ���� �÷���
	bool			bWorkerThread;	// �۾� ������ ���� �÷���
	HANDLE *		workerHandle;	// �۾� ������ �ڵ�
};