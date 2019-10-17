//	stdafx.h : include file for standard system include files,
//		or project specific include files that are used frequently, but
//		are changed infrequently
//

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <winsock2.h>


//////////////////////////////////////////////////////////////////////////
//	��� ����

#define BUFSIZE				100


//////////////////////////////////////////////////////////////////////////
//	����ü ����

typedef struct			// ���� ������ ����üȭ
{
	SOCKET      hClntSock;
	SOCKADDR_IN clntAddr;
} PER_HANDLE_DATA, *LPPER_HANDLE_DATA;

typedef struct			// ������ ���� ������ ����üȭ
{
	OVERLAPPED overlapped;
	CHAR       buffer[ BUFSIZE ];
	WSABUF     wsaBuf;
} PER_IO_DATA, *LPPER_IO_DATA;


//////////////////////////////////////////////////////////////////////////
//	�Լ� ���� ����

void ErrorHandling( LPCSTR pszMessage );
