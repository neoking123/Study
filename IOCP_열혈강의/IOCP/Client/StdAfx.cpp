//	stdafx.cpp : source file that includes just the standard includes
//		Server.pch will be the pre-compiled header
//		stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"


//////////////////////////////////////////////////////////////////////////
//	ErrorHandling() �Լ� ����

void ErrorHandling( LPCSTR pszMessage )
{
	fputs( pszMessage, stderr );
	fputc( '\n', stderr );
	exit( 1 );
}
