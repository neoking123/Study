#include <WinSock2.h>
#include <stdlib.h>
#include <stdio.h>
#include <map>
#include "..\..\Common\ChessPacket.h"
using namespace std;

#define SERVERPORT 9000
#define BUFSIZE 512
#define WM_SOCKET (WM_USER + 1)
char windowClassName[256] = "ChessServer";

class USER_INFO
{
public:
	int index;
	char userBuf[BUFSIZE];
	int len;
	int x;
	int y;
};

int userIndex = 0;
map<SOCKET, USER_INFO*> connectedUsers;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void ProcessSocketMessage(HWND, UINT, WPARAM, LPARAM);
bool ProcessPacket(SOCKET sock, USER_INFO* pUser, char* szBuf, int& len);
void err_display(const char* msg);
void err_display(int errcode);
void err_quit(const char* msg);

int main(int argc, char* argv[])
{
	// 윈도우 클래스 등록
	WNDCLASS wndClass;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = NULL;
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = windowClassName;
	if (!RegisterClass(&wndClass))
		return 1;

	// 윈도우 생성
	HWND hWnd = CreateWindow(windowClassName, windowClassName, WS_OVERLAPPEDWINDOW, 0, 0, 600, 200, NULL, NULL, NULL, NULL);
	if (hWnd == NULL)
		return 1;
	ShowWindow(hWnd, SW_SHOWNORMAL);
	UpdateWindow(hWnd);

	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	// socket()
	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sock == INVALID_SOCKET)
		err_quit("socket()");

	// bind()
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(SERVERPORT);
	int retval;
	retval = bind(listen_sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR)
		err_quit("bind()");

	// listen()
	retval = listen(listen_sock, SOMAXCONN);
	if (retval == SOCKET_ERROR)
		err_quit("listen()");

	// WSAAsyncSelect()
	retval = WSAAsyncSelect(listen_sock, hWnd, WM_SOCKET, FD_ACCEPT | FD_CLOSE);
	if (retval == SOCKET_ERROR)
		err_quit("WSAAsyncSelect()");

	// 메시지 루프
	MSG msg;
	while (GetMessage(&msg, 0, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// 윈속 종료
	WSACleanup();
	return msg.wParam;
}

// 윈도우 메시지 처리
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_SOCKET: // 소켓 관련 윈도우 메시지
		ProcessSocketMessage(hWnd, uMsg, wParam, lParam);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

// 소켓 관련 윈도우 메시지 처리
void ProcessSocketMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// 데이터 통신에 사용할 변수
	SOCKET client_sock;
	SOCKADDR_IN clientaddr;
	int addrlen = 0;
	int retval = 0;

	// 오류 발생 여부 확인
	if (WSAGETSELECTERROR(lParam))
	{
		err_display(WSAGETSELECTERROR(lParam));
		return;
	}

	// 메시지 처리
	switch (WSAGETSELECTEVENT(lParam))
	{
	case FD_ACCEPT:
	{
		addrlen = sizeof(clientaddr);
		client_sock = accept(wParam, (SOCKADDR*)&clientaddr, &addrlen);
		if (client_sock == INVALID_SOCKET)
		{
			err_display("accept()");
			return;
		}
		printf("\n[TCP 서버] 클라이언트 접속: IP 주소=%s, 포트번호=%d\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

		retval = WSAAsyncSelect(client_sock, hWnd, WM_SOCKET, FD_READ | FD_WRITE | FD_CLOSE);
		if (retval == SOCKET_ERROR)
		{
			err_display("WSAAsyncSelect()");
		}

		USER_INFO* pInfo = new USER_INFO();
		pInfo->index = userIndex++;
		pInfo->len = 0;
		pInfo->x = rand() % 600;
		pInfo->y = rand() % 400;
		connectedUsers.insert(make_pair(client_sock, pInfo));

		PACKET_LOGIN packet;
		packet.header.type = PACKET_TYPE_LOGIN;
		packet.header.len = sizeof(packet);
		packet.loginIndex = pInfo->index;
		send(client_sock, (const char*)&packet, packet.header.len, 0);

		Sleep(500);

		PACKET_USER_DATA user_packet;
		user_packet.header.type = PACKET_TYPE_USER_DATA;
		user_packet.header.len = sizeof(PACKET_HEADER) + sizeof(int) + sizeof(USER_DATA) * connectedUsers.size();
		user_packet.count = connectedUsers.size();
		int i = 0;
		for (auto iter = connectedUsers.begin(); iter != connectedUsers.end(); iter++, i++)
		{
			user_packet.data[i].userIndex = iter->second->index;
			user_packet.data[i].x = iter->second->x;
			user_packet.data[i].y = iter->second->y;
		}

		for (auto iter = connectedUsers.begin(); iter != connectedUsers.end(); iter++, i++)
		{
			send(iter->first, (const char*)&user_packet, user_packet.header.len, 0);
		}
	}
	break;

	case FD_READ:
	{
		char buf[BUFSIZE];

		// 데이터 받기
		retval = recv(wParam, buf, BUFSIZE, 0);
		if (retval == SOCKET_ERROR)
		{
			err_display("recv()");
			return;
		}

		USER_INFO* user = connectedUsers[wParam];

		while (true)
		{
			if (!ProcessPacket(wParam, user, buf, retval))
			{
				Sleep(100);
				//SendMessage(hWnd, uMsg, wParam, lParam);
				break;
			}
			else
			{
				if (user->len < sizeof(PACKET_HEADER))
					break;
			}
		}

	}
	break;

	case FD_CLOSE:
		closesocket(wParam);
		break;
	}
}


// 패킷 처리 함수
bool ProcessPacket(SOCKET sock, USER_INFO* userInfo, char* buf, int& len)
{
	if (len > 0)
	{
		memcpy(&userInfo->userBuf[userInfo->len], buf, len);
		userInfo->len += len;
		len = 0;
	}

	if (userInfo->len < sizeof(PACKET_HEADER))
		return false;

	PACKET_HEADER header;
	memcpy(&header, userInfo->userBuf, sizeof(header));

	if (userInfo->len < header.len)
		return false;

	switch (header.type)
	{
	case PACKET_TYPE_SEND_POS:
	{
		PACKET_SEND_POS packet;
		memcpy(&packet, buf, header.len);

		connectedUsers[sock]->x = packet.data.x;
		connectedUsers[sock]->y = packet.data.y;

		for (auto iter = connectedUsers.begin(); iter != connectedUsers.end(); iter++)
		{
			//if (iter->first == sock)
				//continue;

			send(iter->first, (const char*)&packet, header.len, 0);
		}
	}
	break;
	}

	memcpy(&userInfo->userBuf, &userInfo->userBuf[header.len], userInfo->len - header.len);
	userInfo->len -= header.len;

	return true;
}

// 소켓 함수 오류 출력
void err_display(const char* msg)
{
	LPVOID IpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&IpMsgBuf, 0, NULL);
	printf("[%s] %s", msg, (char*)IpMsgBuf);
	LocalFree(IpMsgBuf);
	exit(1);
}

// 소켓 함수 오류 출력
void err_display(int errcode)
{
	LPVOID IpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, errcode,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&IpMsgBuf, 0, NULL);
	printf("[%s] %s", (char*)IpMsgBuf);
	LocalFree(IpMsgBuf);
}

// 소켓 함수 오류 출력 후 종료
void err_quit(const char* msg)
{
	LPVOID IpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&IpMsgBuf, 0, NULL);
	MessageBox(NULL, (LPCTSTR)IpMsgBuf, msg, MB_ICONERROR);
	LocalFree(IpMsgBuf);
	exit(1);
}
