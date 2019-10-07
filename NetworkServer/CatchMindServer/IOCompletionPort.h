#pragma once
#include <WinSock2.h>
#include <stdio.h>

#define	MAX_BUFFER		1024
#define SERVER_PORT		9000

struct SOCKETINFO
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
public:
	IOCompletionPort();
	~IOCompletionPort();

	// 소켓 등록 및 서버 정보 설정
	bool Initialize();
	// 서버 시작
	void StartServer();
	// 작업 스레드 생성
	bool CreateWorkerThread();
	// 접속 스레드 생성
	bool CreateAcceptThread();
	// 작업 스레드
	void WorkerThread();
	// 접속 스레드
	void AcceptThread();

private:
	SOCKETINFO *	socketInfo;		// 소켓 정보
	SOCKET			listenSocket;		// 서버 리슨 소켓
	HANDLE			hIOCP;			// IOCP 객체 핸들
	bool			bAccept;			// 요청 동작 플래그
	bool			bWorkerThread;	// 작업 스레드 동작 플래그
	bool			bAcceptThread;	// 접속 스레드 동작 플래그
	HANDLE *		workerHandle;	// 작업 스레드 핸들
	HANDLE *		acceptHandle;	// 접속 스레드 핸들
};