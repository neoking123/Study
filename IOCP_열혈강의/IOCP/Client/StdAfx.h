//	stdafx.h : include file for standard system include files,
//		or project specific include files that are used frequently, but
//		are changed infrequently
//

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>


//////////////////////////////////////////////////////////////////////////
//	상수 정의

#define BUFSIZE				1024


//////////////////////////////////////////////////////////////////////////
//	함수 원형 선언

void ErrorHandling( LPCSTR pszMessage );
