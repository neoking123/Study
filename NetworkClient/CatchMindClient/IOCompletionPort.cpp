#include "IOCompletionPort.h"
#include "CatchMind.h"
#include "ChattingManager.h"
#include "LobbyManager.h"
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

	// Completion Port ��ü ����
	hIOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);

	// Worker Thread ����
	if (!CreateWorkerThread())
		return false;

	// ���� ����
	//clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	clientSocket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
	if (clientSocket == INVALID_SOCKET) {
		printf_s("[ERROR] ���� ���� ����\n");
		return false;
	}

	// ������ ���� ������ ������ ����ü
	SOCKADDR_IN serverAddr;
	serverAddr.sin_family = AF_INET;

	// ������ ���� ��Ʈ �� IP
	serverAddr.sin_port = htons(SERVER_PORT);
	serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

	// IOCP�� ���� ����
	CreateIoCompletionPort((HANDLE)clientSocket, hIOCP, 0, 0);

	//nResult = connect(clientSocket, (sockaddr*)&serverAddr, sizeof(sockaddr));
	nResult = WSAConnect(clientSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr), NULL, NULL, NULL, NULL);
	if (nResult == SOCKET_ERROR) {
		printf_s("[ERROR] connect ����\n");
		return false;
	}

	return true;
}

void IOCompletionPort::StartClient()
{
	int nResult;
	DWORD recvBytes;
	DWORD flags;

	//// Completion Port ��ü ����
	//hIOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);

	//// Worker Thread ����
	//if (!CreateWorkerThread()) 
	//	return;

	printf_s("[INFO] CatchMind Ŭ�� ����...\n");

	//hIOCP = CreateIoCompletionPort((HANDLE)clientSocket, hIOCP, 0, 0);

	socketInfo = new SOCKET_INFO();
	ZeroMemory(socketInfo, sizeof(SOCKET_INFO));
	socketInfo->socket = clientSocket;
	socketInfo->overlapped.hEvent = WSACreateEvent();
	socketInfo->dataBuf.buf = socketInfo->messageBuffer;
	socketInfo->dataBuf.len = sizeof(socketInfo->messageBuffer);

	DWORD dwNumRecv;
	if (WSARecv(clientSocket, &socketInfo->dataBuf, 1, &dwNumRecv, (LPDWORD)&socketInfo->recvBytes, &socketInfo->overlapped, NULL) == SOCKET_ERROR)
	{
		if (WSAGetLastError() != WSA_IO_PENDING)
		{
			delete packet;
			return;
		}
	}
}

bool IOCompletionPort::CreateWorkerThread()
{
	unsigned int threadId;

	// �ý��� ���� ������
	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);
	printf_s("[INFO] CPU ���� : %d\n", sysInfo.dwNumberOfProcessors);

	// Ŭ�� ������ ����
	//int nThreadCnt = sysInfo.dwNumberOfProcessors * 2;
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
	DWORD	recvBytes = 0;
	DWORD	sendBytes;

	// Completion Key�� ���� ������ ����
	SOCKET_INFO *	completionKey;

	// I/O �۾��� ���� ��û�� Overlapped ����ü�� ���� ������	
	SOCKET_INFO *	socketInfo;

	//send(clientSocket, (const char*)&packet, sizeof(packet), 0);

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

			if (WSARecv(clientSocket, &socketInfo->dataBuf, 1, &recvBytes, (LPDWORD)&socketInfo->recvBytes, &socketInfo->overlapped, NULL) == SOCKET_ERROR)
			{
				if (WSAGetLastError() != WSA_IO_PENDING)
				{
					delete packet;
					return;
				}
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

		LobbyManager::GetInstance()->roomNum = packet.lobyData.roomNum;
		LobbyManager::GetInstance()->maxRoomNum = packet.lobyData.maxRoomNum;

		LobbyManager::GetInstance()->ClearRooms();

		if (LobbyManager::GetInstance()->roomNum <= 0)
			break;
		LobbyManager::GetInstance()->roomCount = 0;

		for (int i = 0; i < LobbyManager::GetInstance()->roomNum; i++)
		{
			LobbyManager::GetInstance()->CreateRoom(packet.lobyData.roomsData[i].roomName, packet.lobyData.roomsData[i].inPlayerNum);
		}

		for (int i = 0; i < LobbyManager::GetInstance()->roomNum; i++)
		{
			LobbyManager::GetInstance()->SetInPlayer(i, packet.lobyData.roomsData[i].inPlayer);
			LobbyManager::GetInstance()->SetIsStart(i, packet.lobyData.roomsData[i].isStart);
			LobbyManager::GetInstance()->SetCanStart(i, packet.lobyData.roomsData[i].canStart);
		}
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

		ChattingManager::GetInstance()->PrintChat(packet.playerIndex, packet.chat);
	}
	break;

	}

	memcpy(&packet->buf, &packet->buf[header.len], packet->len - header.len);
	packet->len -= header.len;

	return true;
}
