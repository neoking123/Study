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
	// winsock 의 사용을 끝낸다
	WSACleanup();

	// 다 사용한 객체를 삭제
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

	// winsock 2.2 버전으로 초기화
	nResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

	if (nResult != 0)
	{
		printf_s("[ERROR] winsock 초기화 실패\n");
		return false;
	}

	// Completion Port 객체 생성
	hIOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);

	// Worker Thread 생성
	if (!CreateWorkerThread())
		return false;

	// 소켓 생성
	//clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	clientSocket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
	if (clientSocket == INVALID_SOCKET) {
		printf_s("[ERROR] 소켓 생성 실패\n");
		return false;
	}

	// 접속할 서버 정보를 저장할 구조체
	SOCKADDR_IN serverAddr;
	serverAddr.sin_family = AF_INET;

	// 접속할 서버 포트 및 IP
	serverAddr.sin_port = htons(SERVER_PORT);
	serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

	// IOCP와 소켓 연결
	hIOCP = CreateIoCompletionPort((HANDLE)clientSocket, hIOCP, 0, 0);

	//nResult = connect(clientSocket, (sockaddr*)&serverAddr, sizeof(sockaddr));
	nResult = WSAConnect(clientSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr), NULL, NULL, NULL, NULL);
	if (nResult == SOCKET_ERROR) {
		printf_s("[ERROR] connect 실패\n");
		return false;
	}

	return true;
}

void IOCompletionPort::StartClient()
{
	int nResult;
	DWORD recvBytes;
	DWORD flags;

	printf_s("[INFO] CatchMind 클라 시작...\n");

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

	// 시스템 정보 가져옴
	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);
	printf_s("[INFO] CPU 갯수 : %d\n", sysInfo.dwNumberOfProcessors);

	// 클라 스레드 갯수
	//int nThreadCnt = sysInfo.dwNumberOfProcessors * 2;
	int nThreadCnt = 1;

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

void IOCompletionPort::WorkerThread()
{
	// 함수 호출 성공 여부
	BOOL	bResult;
	int		nResult;

	// Overlapped I/O 작업에서 전송된 데이터 크기
	DWORD	recvBytes = 0;
	DWORD	sendBytes;

	// Completion Key를 받을 포인터 변수
	SOCKET_INFO *	completionKey;

	// I/O 작업을 위해 요청한 Overlapped 구조체를 받을 포인터	
	SOCKET_INFO *	socketInfo;

	//send(clientSocket, (const char*)&packetBuf, sizeof(packetBuf), 0);

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
			int len = recvBytes;

			// 패킷 처리
			ProcessClientReceive(packetBuf, socketInfo->dataBuf.buf, len);

			// PACKET_INFO 데이터 초기화
			//ZeroMemory(packetBuf->buf, 0);
			//packetBuf->len = 0;

			// SOCKET_INFO 데이터 초기화
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
	// 바이트 스트림 처리
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
