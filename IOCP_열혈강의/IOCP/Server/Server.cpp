// Server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


//////////////////////////////////////////////////////////////////////////
//	�Լ� ���� ����

UINT WINAPI CompletionThread( LPVOID pCompletionPortIO );


//////////////////////////////////////////////////////////////////////////
//	main() �Լ� ����

int main(int argc, char* argv[])
{
	WSADATA wsaData;
	HANDLE  hCompletionPort;

	SYSTEM_INFO systemInfo;
	SOCKADDR_IN servAddr;

	LPPER_IO_DATA     perIoData;
	LPPER_HANDLE_DATA perHandleData;

	SOCKET hServSock;
	DWORD  dwRecvBytes;
	DWORD  i, dwFlags;

	if( argc != 2 )
	{
		printf( "Usage : %s <port>\n", argv[0] );
		exit( 1 );
	}

	if( WSAStartup( MAKEWORD( 2, 2 ), &wsaData ) != 0 )
	{	// Load Winsock 2.2 DLL
		ErrorHandling( "WSAStartup() error!" );
	}

	// 1. Completion Port ����
	hCompletionPort = CreateIoCompletionPort( INVALID_HANDLE_VALUE, NULL,
		0, 0 );
	GetSystemInfo( &systemInfo );

	// 2. �����带 CPU ������ŭ ����
	for( i=0; i<systemInfo.dwNumberOfProcessors; i++ )
	{
		_beginthreadex( NULL, 0, CompletionThread,
			(LPVOID) hCompletionPort, 0, NULL );
	}

	hServSock = WSASocket( PF_INET, SOCK_STREAM, 0, NULL, 0,
		WSA_FLAG_OVERLAPPED );
	if( hServSock == INVALID_SOCKET )
	{
		ErrorHandling( "WSASocket() error!" );
	}

	memset( &servAddr, 0, sizeof( servAddr ) );
	servAddr.sin_family      = AF_INET;
	servAddr.sin_addr.s_addr = htonl( INADDR_ANY );
	servAddr.sin_port        = htons( atoi( argv[1] ) );

	if( bind( hServSock, (SOCKADDR *) &servAddr, sizeof( servAddr ) )
		== SOCKET_ERROR )
	{
		ErrorHandling( "bind() error!" );
	}

	if( listen( hServSock, 5 ) == SOCKET_ERROR )
	{
		ErrorHandling( "listen() error!" );
	}

	while( TRUE )
	{
		SOCKET      hClntSock;
		SOCKADDR_IN clntAddr;
		int         nAddrLen = sizeof( clntAddr );

		hClntSock = accept( hServSock, (SOCKADDR *) &clntAddr,
			&nAddrLen );
		if( hClntSock == INVALID_SOCKET )
		{
			ErrorHandling( "accept() error!" );
		}

		// ����� Ŭ���̾�Ʈ�� ���� �ڵ� ������ �ּ� ������ ����
		perHandleData = new PER_HANDLE_DATA;
		perHandleData->hClntSock = hClntSock;
		memcpy( &(perHandleData->clntAddr), &clntAddr, nAddrLen );

		// 3. Overlapped ���ϰ� Completion Port �� ����
		CreateIoCompletionPort( (HANDLE) hClntSock, hCompletionPort,
			(DWORD) perHandleData, 0 );

		// Ŭ���̾�Ʈ�� ���� ���۸� ����, OVERLAPPED ���� �ʱ�ȭ
		perIoData = new PER_IO_DATA;
		memset( &(perIoData->overlapped), 0, sizeof( OVERLAPPED ) );
		perIoData->wsaBuf.len = BUFSIZE;
		perIoData->wsaBuf.buf = perIoData->buffer;
		dwFlags = 0;

		// 4. ��ø�� ����Ÿ �Է�
		WSARecv( perHandleData->hClntSock,		// ����Ÿ �Է� ����
			&(perIoData->wsaBuf),				// ����Ÿ �Է� ���� ������
			1,									// ����Ÿ �Է� ������ ��
			&dwRecvBytes,
			&dwFlags,
			&(perIoData->overlapped),			// OVERLAPPED ���� ������
			NULL
		);
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////
//	CompletionThread() �Լ� ����

UINT WINAPI CompletionThread( LPVOID pCompletionPortIO )
{
	HANDLE hCompletionPort = (HANDLE) pCompletionPortIO;
	DWORD  dwBytesTransferred;
	LPPER_HANDLE_DATA perHandleData;
	LPPER_IO_DATA     perIoData;
	DWORD  dwFlags;

	while( TRUE )
	{
		// 5. ��.����� �Ϸ�� ������ ���� ����
		GetQueuedCompletionStatus( hCompletionPort,		// Completion Port
			&dwBytesTransferred,						// ���۵� ����Ʈ ��
			(LPDWORD) &perHandleData,
			(LPOVERLAPPED *) &perIoData,
			INFINITE
		);

		if( dwBytesTransferred == 0 )		// EOF ���� ��
		{
			closesocket( perHandleData->hClntSock );

			delete perHandleData;
			delete perIoData;

			continue;
		}

		// 6. �޼���. Ŭ���̾�Ʈ�� ����
		perIoData->wsaBuf.len = dwBytesTransferred;
		WSASend( perHandleData->hClntSock, &(perIoData->wsaBuf), 1, NULL,
			0, NULL, NULL );

		// RECEIVE AGAIN
		memset( &(perIoData->overlapped), 0, sizeof( OVERLAPPED ) );
		perIoData->wsaBuf.len = BUFSIZE;
		perIoData->wsaBuf.buf = perIoData->buffer;

		dwFlags = 0;
		WSARecv( perHandleData->hClntSock,
			&(perIoData->wsaBuf),
			1,
			NULL,
			&dwFlags,
			&(perIoData->overlapped),
			NULL
		);
	}

	return 0;
}
