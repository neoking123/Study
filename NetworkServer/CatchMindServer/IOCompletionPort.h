#pragma once
#include <WinSock2.h>
#include "..\..\Common\NetworkManager.h"

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

class IOCompletionPort
{
private:
	static IOCompletionPort* instance;

	IOCompletionPort();

public:
	~IOCompletionPort();

	// 소켓 등록 및 서버 정보 설정
	bool Init();
	// 서버 시작
	void StartServer();
	// 작업 스레드 생성
	bool CreateWorkerThread();
	// 작업 스레드
	void WorkerThread();
	// 패킷 바이트 스트림 처리
	void ProcessServerReceive(PACKET_INFO* packet, char * buf, int & len);
	// 패킷 처리
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
		if (instance != nullptr)
		{
			SAFE_DELETE(instance);
		}
	}

private:
	SOCKET_INFO *	socketInfo;		// 소켓 정보
	SOCKET			listenSocket;		// 서버 리슨 소켓
	HANDLE			hIOCP;			// IOCP 객체 핸들
	bool			bAccept;			// 요청 동작 플래그
	bool			bWorkerThread;	// 작업 스레드 동작 플래그
	HANDLE *		workerHandle;	// 작업 스레드 핸들
};