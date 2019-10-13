#include "IOCompletionPort.h"
#include <process.h>
#include <mutex>
#include "SketchBook.h"

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
}

bool IOCompletionPort::Init()
{
	bWorkerThread = true;
	bAccept = true;

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
	nResult = ::bind(listenSocket, (struct sockaddr*)&serverAddr, sizeof(SOCKADDR_IN));
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

	// 뮤텍스
	mutex mutex;

	// 클라이언트 정보
	SOCKADDR_IN clientAddr;
	int addrLen = sizeof(SOCKADDR_IN);
	SOCKET clientSocket;
	DWORD recvBytes;
	DWORD flags;

	// Completion Port 객체 생성
	hIOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);

	// Worker Thread 생성
	if (!CreateWorkerThread()) 
		return;

	printf_s("[INFO] CatchMind 서버 시작...\n");

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
		//mutex.lock();
		NetworkManager::GetInstance()->AddUser(clientSocket);
		//mutex.unlock();
		NetworkManager::GetInstance()->SendLoginToClient(clientSocket);
		NetworkManager::GetInstance()->BroadCastLobbyData();

		printf("\n[INFO] 클라이언트 접속: IP 주소=%s, 포트번호=%d\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));

		socketInfo = new SOCKET_INFO();
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

void IOCompletionPort::WorkerThread()
{
	// 함수 호출 성공 여부
	BOOL	bResult;
	int		nResult;

	// Overlapped I/O 작업에서 전송된 데이터 크기
	DWORD	recvBytes;
	DWORD	sendBytes;

	// Completion Key를 받을 포인터 변수
	SOCKET_INFO *	completionKey;

	// I/O 작업을 위해 요청한 Overlapped 구조체를 받을 포인터	
	SOCKET_INFO *	socketInfo;
	
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
			NetworkManager::GetInstance()->EndUser(socketInfo->socket);
			NetworkManager::GetInstance()->BroadCastLobbyData();
			NetworkManager::GetInstance()->BroadCastPlayerData();
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
			PACKET_INFO* packet = NetworkManager::GetInstance()->GetUserPacket(socketInfo->socket);
			ProcessServerReceive(packet, socketInfo->dataBuf.buf, len);

			// SOCKET_INFO 데이터 초기화
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

void IOCompletionPort::ProcessServerReceive(PACKET_INFO * packet, char * buf, int & len)
{
	// 바이트 스트림 처리
	while (true)
	{
		if (!ProcessServerPacket(packet, buf, len))
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

bool IOCompletionPort::ProcessServerPacket(PACKET_INFO * packet, char * buf, int & len)
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

	if (packet->len < header.len)
		return false;

	switch (header.type)
	{
	case PACKET_TYPE::PACKET_TYPE_LOGIN_TO_SERVER:
	{
		PACKET_LOGIN_TO_SERVER packet;
		memcpy(&packet, buf, header.len);

		NetworkManager::GetInstance()->SetNickName(packet.playerIndex, packet.nickName);
		NetworkManager::GetInstance()->BroadCastPlayerData();
	}
	break;

	case PACKET_TYPE::PACKET_TYPE_CREATE_ROOM:
	{
		PACKET_CREATE_ROOM packet;
		memcpy(&packet, buf, header.len);

		if (NetworkManager::GetInstance()->CreateRoom(packet))
		{
			NetworkManager::GetInstance()->BroadCastLobbyData();
			NetworkManager::GetInstance()->BroadCastPlayerData();
		}
	}
	break;

	case PACKET_TYPE::PACKET_TYPE_ENTER_ROOM:
	{
		PACKET_ENTER_ROOM packet;
		memcpy(&packet, buf, header.len);

		NetworkManager::GetInstance()->EnterRoom(packet.roomNum, packet.playerIndex);
		NetworkManager::GetInstance()->BroadCastLobbyData();
		NetworkManager::GetInstance()->BroadCastPlayerData();
		NetworkManager::GetInstance()->SendSketchBookToEnterUser(packet.roomNum, packet.playerIndex);
	}
	break;

	case PACKET_TYPE::PACKET_TYPE_CHAT:
	{
		PACKET_CHAT packet;
		memcpy(&packet, buf, header.len);

		NetworkManager::GetInstance()->SendChatToRoom(packet);
	}
	break;

	case PACKET_TYPE::PACKET_TYPE_BACK_TO_LOBBY:
	{
		PACKET_BACK_TO_LOBBY packet;
		memcpy(&packet, buf, header.len);

		NetworkManager::GetInstance()->BackToLobby(packet.roomNum, packet.playerIndex);
		NetworkManager::GetInstance()->BroadCastLobbyData();
		NetworkManager::GetInstance()->BroadCastPlayerData();
	}
	break;

	case PACKET_TYPE::PACKET_TYPE_DRAW_TO_SERVER:
	{
		PACKET_DRAW_TO_SERVER packet;
		memcpy(&packet, buf, header.len);

		NetworkManager::GetInstance()->DrawToSketchBook(packet.roomNum , packet.brushData);
		NetworkManager::GetInstance()->SendDrawToClient(packet.roomNum);
	}
	break;

	}
	memcpy(&packet->buf, &packet->buf[header.len], packet->len - header.len);
	packet->len -= header.len;

	return true;
}
