#pragma once
#include <WinSock2.h>
#include "..\..\Common\NetworkManager.h"
using namespace std;

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

/**
* @brief Input/Output Completion Port 클래스
* @details 소켓 등록 및 서버 정보 설정
* @details 작업 스레드 생성 및 패킷 처리
* @author Dayeol Hyeon
*/

class IOCompletionPort
{
private:
	static IOCompletionPort* instance;

	IOCompletionPort();

public:
	~IOCompletionPort();

	/**
	* @brief 소켓 등록 및 서버 정보 설정
	* @details 소켓 등록하고 서버 정보 설정한다
	*/
	bool Init();

	/**
	* @brief 서버 시작
	* @details 서버를 시작한다
	* @details Completion Port 객체, Worker Thread를 생성한다
	* @details WSAAccept로 클라이언트의 접속을 받는다
	*/
	void StartServer();

	/**
	* @brief 작업 스레드 생성
	* @details 작업 스레드를 생성한다
	* @details 적절한 작업 스레드의 갯수는 (CPU * 2) + 1
	*/
	bool CreateWorkerThread();

	/**
	* @brief 작업 스레드
	* @details 작업 스레드의 동작을 처리한다
	* @details GetQueuedCompletionStatus 이 함수로 인해 쓰레드들은 WaitingThread Queue 에 대기상태로 들어가게 된다
	* @details 완료된 Overlapped I/O 작업이 발생하면 IOCP Queue 에서 완료된 작업을 가져와 뒷처리를 한다
	*/
	void WorkerThread();
	
	/**
	* @brief 패킷 바이트 스트림 처리
	* @details 패킷이 헤더 크기보다 큰 경우 패킷 처리를 한다
	*/
	void ProcessServerReceive(PACKET_INFO* packet, char * buf, int & len);

	/**
	* @brief 패킷 처리
	* @details 수신한 패킷의 헤더에 담긴 내용을 읽어 타입별 패킷을 처리한다
	*/
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
		SAFE_DELETE(instance);
	}

private:
	SOCKET_INFO *	socketInfo;		// 소켓 정보
	SOCKET			listenSocket;		// 서버 리슨 소켓
	HANDLE			hIOCP;			// IOCP 객체 핸들
	bool			bAccept;			// 요청 동작 플래그
	bool			bWorkerThread;	// 작업 스레드 동작 플래그
	HANDLE *		workerHandle;	// 작업 스레드 핸들
};