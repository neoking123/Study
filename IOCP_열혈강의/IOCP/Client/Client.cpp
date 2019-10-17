// Client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


//////////////////////////////////////////////////////////////////////////
//	main() �Լ� ����

int main(int argc, char* argv[])
{
	WSADATA wsaData;
	SOCKET  hSocket;
	SOCKADDR_IN recvAddr;

	WSABUF dataBuf;
	CHAR  message[] = "Network is Computer!";
	DWORD dwSendBytes = 0;

	WSAEVENT event;
	WSAOVERLAPPED overlapped;

	if( argc != 3 )
	{
		printf( "Usage : %s <ip> <port>\n", argv[0] );
		exit( 1 );
	}

	if( WSAStartup( MAKEWORD( 2, 2 ), &wsaData ) != 0 )
	{
		ErrorHandling( "WSAStartup() error!" );
	}

	hSocket = WSASocket( PF_INET, SOCK_STREAM, 0, NULL, 0,
		WSA_FLAG_OVERLAPPED );
	if( hSocket == INVALID_SOCKET )
	{
		ErrorHandling( "WSASocket() error!" );
	}

	memset( &recvAddr, 0, sizeof( recvAddr ) );
	recvAddr.sin_family      = AF_INET;
	recvAddr.sin_addr.s_addr = inet_addr( argv[1] );
	recvAddr.sin_port        = htons( atoi( argv[2] ) );

	if( connect( hSocket, (SOCKADDR *) &recvAddr, sizeof( recvAddr ) )
		== SOCKET_ERROR )
	{
		ErrorHandling( "connect() error!" );
	}

	event = WSACreateEvent();
	memset( &overlapped, 0, sizeof( overlapped ) );

	overlapped.hEvent = event;
	dataBuf.len = strlen( message );
	dataBuf.buf = message;

	if( WSASend( hSocket, &dataBuf, 1, &dwSendBytes, 0, &overlapped,
		NULL ) == SOCKET_ERROR )
	{
		if( WSAGetLastError() != WSA_IO_PENDING )
		{
			ErrorHandling( "WSASend() error!" );
		}
	}

	// ����Ÿ ���� ���� �߿� �ٸ� �۾��� �Ѵ�.
	puts( "����Ÿ ���� �߿� �ٸ� ���� �ϰ� �ֽ��ϴ�." );
	puts( "����Ÿ ������ Background �� ���� �߿� �ֽ��ϴ�." );

	WSAWaitForMultipleEvents( 1, &event, TRUE, WSA_INFINITE, FALSE );
	WSAGetOverlappedResult( hSocket, &overlapped, &dwSendBytes, FALSE,
		NULL );
	printf( "���۵� ����Ʈ �� : %d\n", dwSendBytes );

	closesocket( hSocket );
	WSACleanup();

	return 0;
}
