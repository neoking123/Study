#include "IOCompletionPort.h"
#include "CatchMind.h"
#include "ChattingManager.h"
#include "LobbyManager.h"
#include "SketchBook.h"
#include <process.h>
#include <mutex>

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

	if (packetBuf)
	{
		SAFE_DELETE(packetBuf);
	}
}

bool IOCompletionPort::Init()
{
	bWorkerThread = true;
	bAccept = true;

	WSADATA wsaData;
	int nResult;
	packetBuf = new PACKET_INFO();
	packetBuf->len = 0;

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
	hIOCP = CreateIoCompletionPort((HANDLE)clientSocket, hIOCP, 0, 0);

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

	printf_s("[INFO] CatchMind Ŭ�� ����...\n");

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

	//send(clientSocket, (const char*)&packetBuf, sizeof(packetBuf), 0);

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
			ProcessClientReceive(packetBuf, socketInfo->dataBuf.buf, len);

			// PACKET_INFO ������ �ʱ�ȭ
			//ZeroMemory(packetBuf->buf, 0);
			//packetBuf->len = 0;

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
					return;
				}
			}
		}
	}
}

void IOCompletionPort::ProcessClientReceive(PACKET_INFO * packetBuf, char * buf, int & len)
{
	// ����Ʈ ��Ʈ�� ó��
	while (true)
	{
		if (!ProcessClientPacket(packetBuf, buf, len))
		{
			Sleep(100);
			break;
		}
		else
		{
			if (packetBuf->len < sizeof(PACKET_HEADER))
				break;
		}
	}
}

bool IOCompletionPort::ProcessClientPacket(PACKET_INFO * packetBuf, char * buf, int & len)
{
	if (len > 0)
	{
		memcpy(&packetBuf->buf[packetBuf->len], buf, len);
		packetBuf->len += len;
		len = 0;
	}

	if (packetBuf->len < sizeof(PACKET_HEADER))
		return false;

	PACKET_HEADER header;
	memcpy(&header, packetBuf->buf, sizeof(header));

	if (packetBuf->len < header.len)
		return false;

	switch (header.type)
	{
	case PACKET_TYPE::PACKET_TYPE_LOGIN_TO_CLIENT:
	{
		PACKET_LOGIN_TO_CLIENT packet;
		memcpy(&packet, packetBuf->buf, header.len);

		CatchMind::GetInstance()->playerIndex = packet.loginIndex;
	}
	break;

	case PACKET_TYPE::PACKET_TYPE_PLAYER_DATA:
	{
		PACKET_PLAYER_DATA packet;
		memcpy(&packet, packetBuf->buf, header.len);

		LobbyManager::GetInstanceLock()->SetPlayerCount(packet.playerCount);

		LobbyManager::GetInstanceLock()->ClearPlayers();

		for (int i = 0; i < LobbyManager::GetInstance()->GetPlayerCount(); i++)
		{
			LobbyManager::GetInstanceLock()->SetPlayers(packet.playerData[i].index, packet.playerData[i].nickName, packet.playerData[i].inRoomNum, packet.playerData[i].kungyaNum);
		}
	}
	break;

	case PACKET_TYPE::PACKET_TYPE_LOBBY_DATA:
	{
		PACKET_LOBBY_DATA packet;
		memcpy(&packet, packetBuf->buf, header.len);

		LobbyManager::GetInstanceLock()->SetRoomCount(packet.lobyData.roomCount);
		LobbyManager::GetInstanceLock()->SetMaxRoomNum(packet.lobyData.maxRoomNum);

		LobbyManager::GetInstanceLock()->ClearRooms();

		if (LobbyManager::GetInstance()->GetRoomCount() <= 0)
			break;
		LobbyManager::GetInstanceLock()->SetRoomAlignCount(0);

		for (int i = 0; i < LobbyManager::GetInstance()->GetRoomCount(); i++)
		{
			LobbyManager::GetInstanceLock()->CreateRoom(packet.lobyData.roomsData[i].roomNum, packet.lobyData.roomsData[i].roomName, packet.lobyData.roomsData[i].inPlayerNum, packet.lobyData.roomsData[i].roomMasterNum);
		}

		for (int i = 0; i < LobbyManager::GetInstance()->GetRoomCount(); i++)
		{
			LobbyManager::GetInstanceLock()->SetAnswerWordInClient(packet.lobyData.roomsData[i].roomNum, packet.lobyData.roomsData[i].answerWord);
			LobbyManager::GetInstanceLock()->SetCurrentTurn(packet.lobyData.roomsData[i].roomNum, packet.lobyData.roomsData[i].curTurn);
			LobbyManager::GetInstanceLock()->SetTurnCount(packet.lobyData.roomsData[i].roomNum, packet.lobyData.roomsData[i].turnCount);
			LobbyManager::GetInstanceLock()->SetInPlayer(packet.lobyData.roomsData[i].roomNum, packet.lobyData.roomsData[i].inPlayer, packet.lobyData.roomsData[i].readyState);
			LobbyManager::GetInstanceLock()->SetIsStart(packet.lobyData.roomsData[i].roomNum, packet.lobyData.roomsData[i].isStart);
			LobbyManager::GetInstanceLock()->SetCanStart(packet.lobyData.roomsData[i].roomNum, packet.lobyData.roomsData[i].canStart);
		}
	}
	break;

	case PACKET_TYPE::PACKET_TYPE_CHAT:
	{
		PACKET_CHAT packet;
		memcpy(&packet, packetBuf->buf, header.len);

		ChattingManager::GetInstance()->PrintChat(packet.playerIndex, packet.chat);
	}
	break;

	case PACKET_TYPE::PACKET_TYPE_DRAW_TO_CLIENT:
	{
		PACKET_DRAW_TO_CLIENT packet;
		memcpy(&packet, packetBuf->buf, header.len);
		
		SketchBook::GetInstanceLock()->PushBackSketchBook(packet.brushData);
	}
	break;

	case PACKET_TYPE::PACKET_TYPE_SKETCH_BOOK:
	{
		PACKET_SKETCH_BOOK packet;
		memcpy(&packet, packetBuf->buf, header.len);

		SketchBook::GetInstance()->CleanSketchBook();
		SketchBook::GetInstanceLock()->SetSketchBook(packet.mouseTrack, packet.mouseTrackLen);
	}
	break;

	case PACKET_TYPE::PACKET_TYPE_ANSWER_PLAYER:
	{
		PACKET_ANSWER_PLAYER packet;
		memcpy(&packet, packetBuf->buf, header.len);

		ChattingManager::GetInstance()->PrintAnswer(packet.playerIndex, packet.answerWord);
	}
	break;

	}

	memcpy(&packetBuf->buf, &packetBuf->buf[header.len], packetBuf->len - header.len);
	packetBuf->len -= header.len;

	return true;
}
