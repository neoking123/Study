#include "IOCompletionPort.h"
#include "CatchMind.h"
#include <process.h>

IOCompletionPort* IOCompletionPort::instance = nullptr;

unsigned int WINAPI CallWorkerThread(LPVOID p)
{
	IOCompletionPort* overlappedEvent = (IOCompletionPort*)p;
	overlappedEvent->WorkerThread();
	return 0;
}

IOCompletionPort::IOCompletionPort()
{
}

IOCompletionPort::~IOCompletionPort()
{
	// winsock �� ����� ������
	WSACleanup();

	// �� ����� ��ü�� ����
	if (socketInfo)
	{
		SAFE_DELETE_ARRAY(socketInfo);
	}

	if (workerHandle)
	{
		SAFE_DELETE_ARRAY(workerHandle);
	}

	if (packet)
	{
		SAFE_DELETE(packet);
	}
}

bool IOCompletionPort::Init()
{
	bWorkerThread = true;
	bAccept = true;

	WSADATA wsaData;
	int nResult;
	packet = new PACKET_INFO();
	packet->len = 0;

	// winsock 2.2 �������� �ʱ�ȭ
	nResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

	if (nResult != 0)
	{
		printf_s("[ERROR] winsock �ʱ�ȭ ����\n");
		return false;
	}

	// ���� ����
	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (clientSocket == INVALID_SOCKET) {
		printf_s("[ERROR] ���� ���� ����\n");
		return false;
	}

	// ������ ���� ������ ������ ����ü
	SOCKADDR_IN serverAddr;
	char	szOutMsg[MAX_BUFFER];
	char	sz_socketbuf_[MAX_BUFFER];
	serverAddr.sin_family = AF_INET;

	// ������ ���� ��Ʈ �� IP
	serverAddr.sin_port = htons(SERVER_PORT);
	serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

	// ������ ���� ��Ʈ �� IP
	serverAddr.sin_port = htons(SERVER_PORT);
	serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

	nResult = connect(clientSocket, (sockaddr*)&serverAddr, sizeof(sockaddr));
	if (nResult == SOCKET_ERROR) {
		printf_s("[ERROR] connect ����\n");
		return -1;
	}

	return true;
}

void IOCompletionPort::StartClient()
{
	// Completion Port ��ü ����
	hIOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);

	// Worker Thread ����
	if (!CreateWorkerThread()) 
		return;

	printf_s("[INFO] CatchMind Ŭ�� ����...\n");

	socketInfo = new SOCKET_INFO();
	socketInfo->socket = clientSocket;
	socketInfo->recvBytes = 0;
	socketInfo->sendBytes = 0;
	socketInfo->dataBuf.len = MAX_BUFFER;
	socketInfo->dataBuf.buf = socketInfo->messageBuffer;

	hIOCP = CreateIoCompletionPort(
		(HANDLE)clientSocket, hIOCP, (DWORD)socketInfo, 0);
}

bool IOCompletionPort::CreateWorkerThread()
{
	unsigned int threadId;

	// Ŭ�� ������ ����
	int nThreadCnt = 1;

	// thread handler ����
	workerHandle = new HANDLE[nThreadCnt];

	// thread ����
	for (int i = 0; i < nThreadCnt; i++)
	{
		workerHandle[i] = (HANDLE *)_beginthreadex(
			NULL, 0, &CallWorkerThread, this, CREATE_SUSPENDED, &threadId);
		if (workerHandle[i] == NULL)
		{
			printf_s("[ERROR] Worker Thread ���� ����\n");
			return false;
		}
		ResumeThread(workerHandle[i]);
	}

	printf_s("[INFO] Worker Thread ����...\n");
	return true;
}

void IOCompletionPort::WorkerThread()
{
	// �Լ� ȣ�� ���� ����
	BOOL	bResult;
	int		nResult;

	// Overlapped I/O �۾����� ���۵� ������ ũ��
	DWORD	recvBytes;
	DWORD	sendBytes;

	// Completion Key�� ���� ������ ����
	SOCKET_INFO *	completionKey;

	// I/O �۾��� ���� ��û�� Overlapped ����ü�� ���� ������	
	SOCKET_INFO *	socketInfo;
	
	DWORD	dwFlags = 0;

	while (bWorkerThread)
	{
		/**
		 * �� �Լ��� ���� ��������� WaitingThread Queue �� �����·� ���� ��
		 * �Ϸ�� Overlapped I/O �۾��� �߻��ϸ� IOCP Queue ���� �Ϸ�� �۾��� ������
		 * ��ó���� ��
		 */
		bResult = GetQueuedCompletionStatus(hIOCP,
			&recvBytes,						// ������ ���۵� ����Ʈ
			(LPDWORD)&completionKey,		// completion key
			(LPOVERLAPPED *)&socketInfo,    // overlapped I/O ��ü
			INFINITE						// ����� �ð�
		);

		if (!bResult && recvBytes == 0)
		{
			printf_s("[INFO] socket(%d) ���� ����\n", socketInfo->socket);
			closesocket(socketInfo->socket);
			free(socketInfo);
			continue;
		}

		socketInfo->dataBuf.len = recvBytes;

		if (recvBytes == 0)
		{
			closesocket(socketInfo->socket);
			free(socketInfo);
			continue;
		}
		else
		{
			int len = recvBytes;

			// ��Ŷ ó��
			ProcessClientReceive(packet, socketInfo->dataBuf.buf, len);

			// SOCKET_INFO ������ �ʱ�ȭ
			ZeroMemory(&(socketInfo->overlapped), sizeof(OVERLAPPED));
			socketInfo->dataBuf.len = MAX_BUFFER;
			socketInfo->dataBuf.buf = socketInfo->messageBuffer;
			ZeroMemory(socketInfo->messageBuffer, MAX_BUFFER);
			socketInfo->recvBytes = 0;
			socketInfo->sendBytes = 0;

			dwFlags = 0;

			if (nResult == SOCKET_ERROR && WSAGetLastError() != WSA_IO_PENDING)
			{
				printf_s("[ERROR] WSARecv ���� : ", WSAGetLastError());
			}
		}
	}
}

void IOCompletionPort::ProcessClientReceive(PACKET_INFO * packet, char * buf, int & len)
{
	// ����Ʈ ��Ʈ�� ó��
	while (true)
	{
		if (!ProcessClientPacket(packet, buf, len))
		{
			Sleep(100);
			break;
		}
		else
		{
			if (packet->len < sizeof(PACKET_HEADER))
				break;
		}
	}
}

bool IOCompletionPort::ProcessClientPacket(PACKET_INFO * packet, char * buf, int & len)
{
	if (len > 0)
	{
		memcpy(&packet->buf[packet->len], buf, len);
		packet->len += len;
		len = 0;
	}

	if (packet->len < sizeof(PACKET_HEADER))
		return false;

	PACKET_HEADER header;
	memcpy(&header, packet->buf, sizeof(header));

	switch (header.type)
	{
	case PACKET_TYPE::PACKET_TYPE_LOGIN:
	{
		PACKET_LOGIN packet;
		memcpy(&packet, buf, header.len);

		CatchMind::GetInstance()->playerIndex = packet.loginIndex;
	}
	break;

	case PACKET_TYPE::PACKET_TYPE_USER_DATA:
	{
		PACKET_USER_DATA packet;
		memcpy(&packet, buf, header.len);
	}
	break;

	case PACKET_TYPE::PACKET_TYPE_LOBBY_DATA:
	{
		PACKET_LOBBY_DATA packet;
		memcpy(&packet, buf, header.len);
	}
	break;

	case PACKET_TYPE::PACKET_TYPE_MOVE_TO:
	{
		PACKET_MOVE_TO packet;
		memcpy(&packet, buf, header.len);
	}
	break;

	case PACKET_TYPE::PACKET_TYPE_CHAT:
	{
		PACKET_CHAT packet;
		memcpy(&packet, buf, header.len);
	}
	break;

	}

	memcpy(&packet->buf, &packet->buf[header.len], packet->len - header.len);
	packet->len -= header.len;

	return true;
}
