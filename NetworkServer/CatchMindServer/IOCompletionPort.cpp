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
	// winsock 의 사용을 끝낸다
	WSACleanup();
	// 다 사용한 객체를 삭제
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
	// winsock 2.2 버전으로 초기화
	nResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

	if (nResult != 0)
	{
		printf_s("[ERROR] winsock 초기화 실패\n");
		return false;
	}

	// 소켓 생성
	listenSocket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	if (listenSocket == INVALID_SOCKET)
	{
		printf_s("[ERROR] 소켓 생성 실패\n");
		return false;
	}

	// 서버 정보 설정
	SOCKADDR_IN serverAddr;
	serverAddr.sin_family = PF_INET;
	serverAddr.sin_port = htons(SERVER_PORT);
	serverAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	// 소켓 설정
	nResult = bind(listenSocket, (struct sockaddr*)&serverAddr, sizeof(SOCKADDR_IN));
	if (nResult == SOCKET_ERROR)
	{
		printf_s("[ERROR] bind 실패\n");
		closesocket(listenSocket);
		WSACleanup();
		return false;
	}

	// 수신 대기열 생성
	nResult = listen(listenSocket, SOMAXCONN);
	if (nResult == SOCKET_ERROR)
	{
		printf_s("[ERROR] listen 실패\n");
		closesocket(listenSocket);
		WSACleanup();
		return false;
	}

	return true;
}

void IOCompletionPort::StartServer()
{
	int nResult;
	// 클라이언트 정보
	SOCKADDR_IN clientAddr;
	int addrLen = sizeof(SOCKADDR_IN);
	SOCKET clientSocket;
	DWORD recvBytes;
	DWORD flags;

	// Completion Port 객체 생성
	hIOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);

	// Accept Thread 생성
	if (!CreateAcceptThread())
		return;

	// Worker Thread 생성
	if (!CreateWorkerThread()) 
		return;

	printf_s("[INFO] 서버 시작...\n");

	// 클라이언트 접속을 받음
	while (bAccept)
	{
		clientSocket = WSAAccept(
			listenSocket, (struct sockaddr *)&clientAddr, &addrLen, NULL, NULL
		);

		if (clientSocket == INVALID_SOCKET)
		{
			printf_s("[ERROR] Accept 실패\n");
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

		// 중첩 소켓을 지정하고 완료시 실행될 함수를 넘겨줌
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
			printf_s("[ERROR] IO Pending 실패 : %d", WSAGetLastError());
			return;
		}
	}
}

bool IOCompletionPort::CreateWorkerThread()
{
	unsigned int threadId;
	// 시스템 정보 가져옴
	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);
	printf_s("[INFO] CPU 갯수 : %d\n", sysInfo.dwNumberOfProcessors);
	// 적절한 작업 스레드의 갯수는 (CPU * 2) + 1
	int nThreadCnt = sysInfo.dwNumberOfProcessors * 2;

	// thread handler 선언
	workerHandle = new HANDLE[nThreadCnt];
	// thread 생성
	for (int i = 0; i < nThreadCnt; i++)
	{
		workerHandle[i] = (HANDLE *)_beginthreadex(
			NULL, 0, &CallWorkerThread, this, CREATE_SUSPENDED, &threadId);
		if (workerHandle[i] == NULL)
		{
			printf_s("[ERROR] Worker Thread 생성 실패\n");
			return false;
		}
		ResumeThread(workerHandle[i]);
	}
	printf_s("[INFO] Worker Thread 시작...\n");
	return true;
}

bool IOCompletionPort::CreateAcceptThread()
{
	unsigned int threadId;
	// thread handler 선언
	acceptHandle = new HANDLE;
	// thread 생성
	acceptHandle = (HANDLE *)_beginthreadex(
		NULL, 0, &CallAcceptThread, this, CREATE_SUSPENDED, &threadId);
	if (acceptHandle == NULL)
	{
		printf_s("[ERROR] Accept Thread 생성 실패\n");
		return false;
	}
	ResumeThread(acceptHandle);
	printf_s("[INFO] Accept Thread 시작...\n");
	return true;
}

void IOCompletionPort::WorkerThread()
{
	// 함수 호출 성공 여부
	BOOL	bResult;
	int		nResult;
	// Overlapped I/O 작업에서 전송된 데이터 크기
	DWORD	recvBytes;
	DWORD	sendBytes;
	// Completion Key를 받을 포인터 변수
	SOCKETINFO *	completionKey;
	// I/O 작업을 위해 요청한 Overlapped 구조체를 받을 포인터	
	SOCKETINFO *	socketInfo;
	// 
	DWORD	dwFlags = 0;

	while (bWorkerThread)
	{
		/**
		 * 이 함수로 인해 쓰레드들은 WaitingThread Queue 에 대기상태로 들어가게 됨
		 * 완료된 Overlapped I/O 작업이 발생하면 IOCP Queue 에서 완료된 작업을 가져와
		 * 뒷처리를 함
		 */
		bResult = GetQueuedCompletionStatus(hIOCP,
			&recvBytes,						// 실제로 전송된 바이트
			(LPDWORD)&completionKey,		// completion key
			(LPOVERLAPPED *)&socketInfo,    // overlapped I/O 객체
			INFINITE						// 대기할 시간
		);

		if (!bResult && recvBytes == 0)
		{
			printf_s("[INFO] socket(%d) 접속 끊김\n", socketInfo->socket);
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
			printf_s("[INFO] 메시지 수신- Socket : [%d], Bytes : [%d], Msg : [%s]\n",
				socketInfo->socket, socketInfo->dataBuf.len, socketInfo->dataBuf.buf);

			// 클라이언트의 응답을 그대로 송신			
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
				printf_s("[ERROR] WSASend 실패 : ", WSAGetLastError());
			}

			printf_s("[INFO] 메시지 송신 - Socket : [%d], Bytes : [%d], Msg : [%s]\n",
				socketInfo->socket, socketInfo->dataBuf.len, socketInfo->dataBuf.buf);

			// SOCKETINFO 데이터 초기화
			ZeroMemory(&(socketInfo->overlapped), sizeof(OVERLAPPED));
			socketInfo->dataBuf.len = MAX_BUFFER;
			socketInfo->dataBuf.buf = socketInfo->messageBuffer;
			ZeroMemory(socketInfo->messageBuffer, MAX_BUFFER);
			socketInfo->recvBytes = 0;
			socketInfo->sendBytes = 0;

			dwFlags = 0;

			// 클라이언트로부터 다시 응답을 받기 위해 WSARecv 를 호출해줌
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
				printf_s("[ERROR] WSARecv 실패 : ", WSAGetLastError());
			}
		}
	}
}

void IOCompletionPort::AcceptThread()
{
	while (bAcceptThread)
	{
		// 데이터 통신에 사용할 변수
		SOCKET client_sock;
		SOCKADDR_IN clientaddr;
		int addrlen = 0;
		int	nResult = 0;
		addrlen = sizeof(clientaddr);
		client_sock = accept(listenSocket, (SOCKADDR*)&clientaddr, &addrlen);

		if (client_sock == INVALID_SOCKET)
		{
			printf_s("[ERROR] Accept 실패 : ", WSAGetLastError());
			return;
		}
		printf("\n[CatchMind] 클라이언트 접속: IP 주소=%s, 포트번호=%d\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
	}
}

// 패킷 처리 함수
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