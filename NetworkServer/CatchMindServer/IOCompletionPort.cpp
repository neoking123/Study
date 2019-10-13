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
}

bool IOCompletionPort::Init()
{
	bWorkerThread = true;
	bAccept = true;

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
	nResult = ::bind(listenSocket, (struct sockaddr*)&serverAddr, sizeof(SOCKADDR_IN));
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

	// ���ؽ�
	mutex mutex;

	// Ŭ���̾�Ʈ ����
	SOCKADDR_IN clientAddr;
	int addrLen = sizeof(SOCKADDR_IN);
	SOCKET clientSocket;
	DWORD recvBytes;
	DWORD flags;

	// Completion Port ��ü ����
	hIOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);

	// Worker Thread ����
	if (!CreateWorkerThread()) 
		return;

	printf_s("[INFO] CatchMind ���� ����...\n");

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
		//mutex.lock();
		NetworkManager::GetInstance()->AddUser(clientSocket);
		//mutex.unlock();
		NetworkManager::GetInstance()->SendLoginToClient(clientSocket);
		NetworkManager::GetInstance()->BroadCastLobbyData();

		printf("\n[INFO] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ��ȣ=%d\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));

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
			NetworkManager::GetInstance()->EndUser(socketInfo->socket);
			NetworkManager::GetInstance()->BroadCastLobbyData();
			NetworkManager::GetInstance()->BroadCastPlayerData();
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
			PACKET_INFO* packet = NetworkManager::GetInstance()->GetUserPacket(socketInfo->socket);
			ProcessServerReceive(packet, socketInfo->dataBuf.buf, len);

			// SOCKET_INFO ������ �ʱ�ȭ
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

void IOCompletionPort::ProcessServerReceive(PACKET_INFO * packet, char * buf, int & len)
{
	// ����Ʈ ��Ʈ�� ó��
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
