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

	// winsock 2.2 버전으로 초기화
	nResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

	if (nResult != 0)
	{
		printf_s("[ERROR] winsock 초기화 실패\n");
		return false;
	}

	// 소켓 생성
	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (clientSocket == INVALID_SOCKET) {
		printf_s("[ERROR] 소켓 생성 실패\n");
		return false;
	}

	// 접속할 서버 정보를 저장할 구조체
	SOCKADDR_IN serverAddr;
	char	szOutMsg[MAX_BUFFER];
	char	sz_socketbuf_[MAX_BUFFER];
	serverAddr.sin_family = AF_INET;

	// 접속할 서버 포트 및 IP
	serverAddr.sin_port = htons(SERVER_PORT);
	serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

	// 접속할 서버 포트 및 IP
	serverAddr.sin_port = htons(SERVER_PORT);
	serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

	nResult = connect(clientSocket, (sockaddr*)&serverAddr, sizeof(sockaddr));
	if (nResult == SOCKET_ERROR) {
		printf_s("[ERROR] connect 실패\n");
		return -1;
	}

	return true;
}

void IOCompletionPort::StartClient()
{
	// Completion Port 객체 생성
	hIOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);

	// Worker Thread 생성
	if (!CreateWorkerThread()) 
		return;

	printf_s("[INFO] CatchMind 클라 시작...\n");

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

	// 클라 스레드 갯수
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
			ProcessClientReceive(packet, socketInfo->dataBuf.buf, len);

			// SOCKET_INFO 데이터 초기화
			ZeroMemory(&(socketInfo->overlapped), sizeof(OVERLAPPED));
			socketInfo->dataBuf.len = MAX_BUFFER;
			socketInfo->dataBuf.buf = socketInfo->messageBuffer;
			ZeroMemory(socketInfo->messageBuffer, MAX_BUFFER);
			socketInfo->recvBytes = 0;
			socketInfo->sendBytes = 0;

			dwFlags = 0;

			if (nResult == SOCKET_ERROR && WSAGetLastError() != WSA_IO_PENDING)
			{
				printf_s("[ERROR] WSARecv 실패 : ", WSAGetLastError());
			}
		}
	}
}

void IOCompletionPort::ProcessClientReceive(PACKET_INFO * packet, char * buf, int & len)
{
	// 바이트 스트림 처리
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
