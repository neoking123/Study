#include "IOCompletionPort.h"
#include "Macro.h"
#include <process.h>

unsigned int WINAPI CallWorkerThread(LPVOID p)
{
	IOCompletionPort* overlappedEvent = (IOCompletionPort*)p;
	overlappedEvent->WorkerThread();
	return 0;
}

unsigned int WINAPI CallAcceptThread(LPVOID p)
{
	IOCompletionPort* overlappedEvent = (IOCompletionPort*)p;
	overlappedEvent->AcceptThread();
	return 0;
}

IOCompletionPort::IOCompletionPort()
{
	bWorkerThread = true;
	bAcceptThread = true;
	bAccept = true;
}

IOCompletionPort::~IOCompletionPort()
{
	// winsock �� ����� ������
	WSACleanup();
	// �� ����� ��ü�� ����
	if (socketInfo)
	{
		/*delete[] m_pSocketInfo;
		m_pSocketInfo = NULL;*/
		SAFE_DELETE_ARRAY(socketInfo);
	}

	if (workerHandle)
	{
		/*delete[] m_pWorkerHandle;
		m_pWorkerHandle = NULL;*/
		SAFE_DELETE_ARRAY(workerHandle);
	}

	if (acceptHandle)
	{
		SAFE_DELETE(acceptHandle);
	}
}

bool IOCompletionPort::Initialize()
{
	WSADATA wsaData;
	int nResult;
	// winsock 2.2 �������� �ʱ�ȭ
	nResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

	if (nResult != 0)
	{
		printf_s("[ERROR] winsock �ʱ�ȭ ����\n");
		return false;
	}

	// ���� ����
	listenSocket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	if (listenSocket == INVALID_SOCKET)
	{
		printf_s("[ERROR] ���� ���� ����\n");
		return false;
	}

	// ���� ���� ����
	SOCKADDR_IN serverAddr;
	serverAddr.sin_family = PF_INET;
	serverAddr.sin_port = htons(SERVER_PORT);
	serverAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	// ���� ����
	nResult = bind(listenSocket, (struct sockaddr*)&serverAddr, sizeof(SOCKADDR_IN));
	if (nResult == SOCKET_ERROR)
	{
		printf_s("[ERROR] bind ����\n");
		closesocket(listenSocket);
		WSACleanup();
		return false;
	}

	// ���� ��⿭ ����
	nResult = listen(listenSocket, SOMAXCONN);
	if (nResult == SOCKET_ERROR)
	{
		printf_s("[ERROR] listen ����\n");
		closesocket(listenSocket);
		WSACleanup();
		return false;
	}

	return true;
}

void IOCompletionPort::StartServer()
{
	int nResult;
	// Ŭ���̾�Ʈ ����
	SOCKADDR_IN clientAddr;
	int addrLen = sizeof(SOCKADDR_IN);
	SOCKET clientSocket;
	DWORD recvBytes;
	DWORD flags;

	// Completion Port ��ü ����
	hIOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);

	// Accept Thread ����
	if (!CreateAcceptThread())
		return;

	// Worker Thread ����
	if (!CreateWorkerThread()) 
		return;

	printf_s("[INFO] ���� ����...\n");

	// Ŭ���̾�Ʈ ������ ����
	while (bAccept)
	{
		clientSocket = WSAAccept(
			listenSocket, (struct sockaddr *)&clientAddr, &addrLen, NULL, NULL
		);

		if (clientSocket == INVALID_SOCKET)
		{
			printf_s("[ERROR] Accept ����\n");
			return;
		}

		socketInfo = new SOCKETINFO();
		socketInfo->socket = clientSocket;
		socketInfo->recvBytes = 0;
		socketInfo->sendBytes = 0;
		socketInfo->dataBuf.len = MAX_BUFFER;
		socketInfo->dataBuf.buf = socketInfo->messageBuffer;
		flags = 0;

		hIOCP = CreateIoCompletionPort(
			(HANDLE)clientSocket, hIOCP, (DWORD)socketInfo, 0
		);

		// ��ø ������ �����ϰ� �Ϸ�� ����� �Լ��� �Ѱ���
		nResult = WSARecv(
			socketInfo->socket,
			&socketInfo->dataBuf,
			1,
			&recvBytes,
			&flags,
			&(socketInfo->overlapped),
			NULL
		);

		if (nResult == SOCKET_ERROR && WSAGetLastError() != WSA_IO_PENDING)
		{
			printf_s("[ERROR] IO Pending ���� : %d", WSAGetLastError());
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
	// ������ �۾� �������� ������ (CPU * 2) + 1
	int nThreadCnt = sysInfo.dwNumberOfProcessors * 2;

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

bool IOCompletionPort::CreateAcceptThread()
{
	unsigned int threadId;
	// thread handler ����
	acceptHandle = new HANDLE;
	// thread ����
	acceptHandle = (HANDLE *)_beginthreadex(
		NULL, 0, &CallAcceptThread, this, CREATE_SUSPENDED, &threadId);
	if (acceptHandle == NULL)
	{
		printf_s("[ERROR] Accept Thread ���� ����\n");
		return false;
	}
	ResumeThread(acceptHandle);
	printf_s("[INFO] Accept Thread ����...\n");
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
	SOCKETINFO *	completionKey;
	// I/O �۾��� ���� ��û�� Overlapped ����ü�� ���� ������	
	SOCKETINFO *	socketInfo;
	// 
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
			printf_s("[INFO] �޽��� ����- Socket : [%d], Bytes : [%d], Msg : [%s]\n",
				socketInfo->socket, socketInfo->dataBuf.len, socketInfo->dataBuf.buf);

			// Ŭ���̾�Ʈ�� ������ �״�� �۽�			
			nResult = WSASend(
				socketInfo->socket,
				&(socketInfo->dataBuf),
				1,
				&sendBytes,
				dwFlags,
				NULL,
				NULL
			);

			if (nResult == SOCKET_ERROR && WSAGetLastError() != WSA_IO_PENDING)
			{
				printf_s("[ERROR] WSASend ���� : ", WSAGetLastError());
			}

			printf_s("[INFO] �޽��� �۽� - Socket : [%d], Bytes : [%d], Msg : [%s]\n",
				socketInfo->socket, socketInfo->dataBuf.len, socketInfo->dataBuf.buf);

			// SOCKETINFO ������ �ʱ�ȭ
			ZeroMemory(&(socketInfo->overlapped), sizeof(OVERLAPPED));
			socketInfo->dataBuf.len = MAX_BUFFER;
			socketInfo->dataBuf.buf = socketInfo->messageBuffer;
			ZeroMemory(socketInfo->messageBuffer, MAX_BUFFER);
			socketInfo->recvBytes = 0;
			socketInfo->sendBytes = 0;

			dwFlags = 0;

			// Ŭ���̾�Ʈ�κ��� �ٽ� ������ �ޱ� ���� WSARecv �� ȣ������
			nResult = WSARecv(
				socketInfo->socket,
				&(socketInfo->dataBuf),
				1,
				&recvBytes,
				&dwFlags,
				(LPWSAOVERLAPPED)&(socketInfo->overlapped),
				NULL
			);

			if (nResult == SOCKET_ERROR && WSAGetLastError() != WSA_IO_PENDING)
			{
				printf_s("[ERROR] WSARecv ���� : ", WSAGetLastError());
			}
		}
	}
}

void IOCompletionPort::AcceptThread()
{
	while (bAcceptThread)
	{
		// ������ ��ſ� ����� ����
		SOCKET client_sock;
		SOCKADDR_IN clientaddr;
		int addrlen = 0;
		int	nResult = 0;
		addrlen = sizeof(clientaddr);
		client_sock = accept(listenSocket, (SOCKADDR*)&clientaddr, &addrlen);

		if (client_sock == INVALID_SOCKET)
		{
			printf_s("[ERROR] Accept ���� : ", WSAGetLastError());
			return;
		}
		printf("\n[CatchMind] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ��ȣ=%d\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
	}
}

// ��Ŷ ó�� �Լ�
//bool ProcessPacket(char* buf, int& len)
//{
//	if (len > 0)
//	{
//		memcpy(&userInfo->userBuf[userInfo->len], buf, len);
//		userInfo->len += len;
//		len = 0;
//	}
//
//	if (userInfo->len < sizeof(PACKET_HEADER))
//		return false;
//
//	PACKET_HEADER header;
//	memcpy(&header, userInfo->userBuf, sizeof(header));
//
//	if (userInfo->len < header.len)
//		return false;
//
//	switch (header.type)
//	{
//	case PACKET_TYPE::PACKET_TYPE_CREATE_ROOM:
//	{
//		PACKET_CREATE_ROOM packet;
//		memcpy(&packet, buf, header.len);
//
//		if (roomNum >= MAX_ROOM_NUM)
//			break;
//
//		ROOM_INFO* roomInfo = new ROOM_INFO();
//		strcpy(roomInfo->roomName, packet.roomData.roomName);
//		roomInfo->inPlayerNum = packet.roomData.inPlayerNum;
//		roomInfo->inPlayers[0] = packet.roomData.inPlayer[0];
//		InitChessBoard(roomInfo->board);
//		//InitSpectatorArray(roomInfo->spectators);
//		createdRooms.insert(make_pair(roomNum, roomInfo));
//
//		for (auto iter = connectedUsers.begin(); iter != connectedUsers.end(); iter++)
//		{
//			if (iter->second->index == packet.roomData.inPlayer[0])
//			{
//				iter->second->inRoomNum = roomNum;
//			}
//		}
//		roomNum++;
//
//		SendLobbyData();
//	}
//	break;
//
//	case PACKET_TYPE::PACKET_TYPE_ENTER_ROOM:
//	{
//		PACKET_ENTER_ROOM packet;
//		memcpy(&packet, buf, header.len);
//
//		for (auto iter = createdRooms.begin(); iter != createdRooms.end(); iter++)
//		{
//			if (iter->first == packet.roomNum)
//			{
//				if (iter->second->inPlayers[1] == -1)
//				{
//					iter->second->inPlayers[1] = packet.playerIndex;
//
//				}
//				else
//				{
//					/*for (int i = 0; i < 20; i++)
//					{
//						if (iter->second->spectators[i] == -1)
//						{
//							iter->second->spectators[i] = packet.playerIndex;
//							break;
//						}
//					}*/
//				}
//				iter->second->inPlayerNum++;
//			}
//		}
//
//		for (auto iter = connectedUsers.begin(); iter != connectedUsers.end(); iter++)
//		{
//			if (iter->second->index == packet.playerIndex)
//			{
//				iter->second->inRoomNum = packet.roomNum;
//			}
//		}
//
//		SendLobbyData();
//	}
//	break;
//
//	case PACKET_TYPE::PACKET_TYPE_ROOM_STATE:
//	{
//		PACKET_ROOM_STATE packet;
//		memcpy(&packet, buf, header.len);
//
//		createdRooms[packet.roomNum]->isStart = packet.isStart;
//		createdRooms[packet.roomNum]->canStart = packet.canStart;
//
//		SendLobbyData();
//	}
//	break;
//
//	case PACKET_TYPE::PACKET_TYPE_MOVE_TO:
//	{
//		PACKET_MOVE_TO packet;
//		memcpy(&packet, buf, header.len);
//
//		POINT curPos = packet.moveDate.curPos;
//		POINT targetPos = packet.moveDate.targetPos;
//
//		for (auto iter = createdRooms.begin(); iter != createdRooms.end(); iter++)
//		{
//			if (iter->first == packet.roomNum)
//			{
//				iter->second->board[targetPos.y][targetPos.x] = iter->second->board[curPos.y][curPos.x];
//				iter->second->board[curPos.y][curPos.x] = CHESS_PIECES::NONE;
//
//				for (auto userIter = connectedUsers.begin(); userIter != connectedUsers.end(); userIter++)
//				{
//					if (userIter->second->index == iter->second->inPlayers[0]
//						|| userIter->second->index == iter->second->inPlayers[1])
//					{
//						send(userIter->first, (const char*)&packet, header.len, 0);
//					}
//				}
//			}
//		}
//	}
//	break;
//
//	case PACKET_TYPE::PACKET_TYPE_CHAT:
//	{
//		PACKET_CHAT packet;
//		memcpy(&packet, buf, header.len);
//
//		for (auto iter = connectedUsers.begin(); iter != connectedUsers.end(); iter++)
//		{
//			if (iter->second->inRoomNum == packet.roomNum)
//			{
//				send(iter->first, (const char*)&packet, header.len, 0);
//			}
//		}
//	}
//	break;
//
//	case PACKET_TYPE::PACKET_TYPE_BACK_TO_LOBBY:
//	{
//		PACKET_BACK_TO_LOBBY packet;
//		memcpy(&packet, buf, header.len);
//
//		for (auto iter = createdRooms.begin(); iter != createdRooms.end(); iter++)
//		{
//			if (iter->first == packet.roomNum)
//			{
//				if (iter->second->inPlayers[0] == packet.playerIndex)
//				{
//					if (iter->second->inPlayers[1] == -1)
//					{
//						createdRooms.erase(iter->first);
//						roomNum--;
//						SendLobbyData();
//						break;
//					}
//					else
//					{
//						iter->second->inPlayers[0] = iter->second->inPlayers[1];
//						iter->second->inPlayers[1] = -1;
//						iter->second->inPlayerNum = 1;
//						iter->second->canStart = false;
//						iter->second->isStart = false;
//						SendLobbyData();
//					}
//
//				}
//				else if (iter->second->inPlayers[1] == packet.playerIndex)
//				{
//					//iter->second->inPlayer[0] = iter->second->inPlayer[1];
//					iter->second->inPlayers[1] = -1;
//					iter->second->inPlayerNum = 1;
//					iter->second->canStart = false;
//					iter->second->isStart = false;
//					SendLobbyData();
//				}
//			}
//		}
//
//		for (auto iter = connectedUsers.begin(); iter != connectedUsers.end(); iter++)
//		{
//			if (iter->second->index == packet.playerIndex)
//			{
//				iter->second->inRoomNum = -1;
//			}
//		}
//
//	}
//	break;
//
//	}
//
//	memcpy(&userInfo->userBuf, &userInfo->userBuf[header.len], userInfo->len - header.len);
//	userInfo->len -= header.len;
//
//	return true;
//}