#include <WinSock2.h>
#include <windows.h>
#include <map>
#include "..\..\Common\ChessPacket.h"
using namespace std;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void ProcessSocketMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void ProcessPacket(char* szBuf, int len);
void err_display(const char* msg);
void err_display(int errcode);
void err_quit(const char* msg);

HINSTANCE g_hInst;
char g_szClassName[256] = "ChessClient";

#define SERVERIP "127.0.0.1"
#define SERVERPORT 9000
#define BUFSIZE 512
#define WM_SOCKET (WM_USER+1)

SOCKET sock;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS wndClass;
	g_hInst = hInstance;

	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = WndProc;
	wndClass.lpszClassName = g_szClassName;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wndClass);

	hWnd = CreateWindow(g_szClassName, g_szClassName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return -1;

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		//cout << "err on socket" << endl;
		err_quit("err on socket");
		return -1;
	}

	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(SERVERPORT);
	serveraddr.sin_addr.s_addr = inet_addr(SERVERIP);
	int retval = connect(sock, (sockaddr*)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR)
	{
		//cout << "err on connect" << endl;
		err_quit("err on connect");
		return -1;
	}

	retval = WSAAsyncSelect(sock, hWnd, WM_SOCKET, FD_READ | FD_CLOSE);
	if (retval == SOCKET_ERROR)
	{
		err_quit("WSAAsyncSelect()");
		return -1;
	}

	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	closesocket(sock);
	WSACleanup();

	return (int)Message.wParam;
}

class Player
{
public:
	int x;
	int y;
};

map<int, Player*> players;
int playerIndex = 0;

void SendPos()
{
	PACKET_SEND_POS packet;
	packet.header.type = PACKET_TYPE_SEND_POS;
	packet.header.len = sizeof(packet);
	packet.data.userIndex = playerIndex;
	packet.data.x = players[playerIndex]->x;
	packet.data.y = players[playerIndex]->y;
	send(sock, (const char*)&packet, sizeof(packet), 0);
	send(sock, (const char*)&packet, sizeof(packet), 0);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage)
	{
	case WM_CREATE:
		return 0;

	case WM_SOCKET:
		ProcessSocketMessage(hWnd, iMessage, wParam, lParam);
		InvalidateRect(hWnd, NULL, true);
		return 0;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT:
			players[playerIndex]->x -= 8;
			SendPos();
			break;
		case VK_RIGHT:
			players[playerIndex]->x += 8;
			SendPos();
			break;
		case VK_UP:
			players[playerIndex]->y -= 8;
			SendPos();
			break;
		case VK_DOWN:
			players[playerIndex]->y += 8;
			SendPos();
			break;
		}
		InvalidateRect(hWnd, NULL, true);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		for (auto iter = players.begin(); iter != players.end(); iter++)
		{
			char szPrint[128];
			wsprintf(szPrint, "%d", iter->first);
			TextOut(hdc, iter->second->x, iter->second->y, szPrint, strlen(szPrint));

		}
		EndPaint(hWnd, &ps);
		return 0;

	case WM_DESTROY:
		for (auto iter = players.begin(); iter != players.end(); iter++)
		{
			delete iter->second;
		}
		players.clear();
		PostQuitMessage(0);
		return 0;
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

void ProcessSocketMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	SOCKET client_sock;
	SOCKADDR_IN clientaddr;
	int addrlen = 0;
	int retval = 0;

	if (WSAGETSELECTERROR(lParam))
	{
		int err_code = WSAGETSELECTERROR(lParam);
		err_display(WSAGETSELECTERROR(lParam));
		return;
	}

	switch (WSAGETSELECTEVENT(lParam))
	{
	case FD_READ:
	{
		char szBuf[BUFSIZE];

		retval = recv(wParam, szBuf, BUFSIZE, 0);
		if (retval == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				//cout << "err on recv!!" << endl;
				err_quit("recv()");
			}
		}

		ProcessPacket(szBuf, retval);
	}
	break;

	case FD_CLOSE:
		closesocket(wParam);
		break;
	}
}

void ProcessPacket(char* szBuf, int len)
{
	PACKET_HEADER header;

	memcpy(&header, szBuf, sizeof(header));

	switch (header.type)
	{
	case PACKET_TYPE_LOGIN:
	{
		PACKET_LOGIN packet;
		memcpy(&packet, szBuf, header.len);

		playerIndex = packet.loginIndex;
	}
	break;
	case PACKET_TYPE_USER_DATA:
	{
		PACKET_USER_DATA packet;
		memcpy(&packet, szBuf, header.len);

		for (auto iter = players.begin(); iter != players.end(); iter++)
		{
			delete iter->second;
		}
		players.clear();

		for (int i = 0; i < packet.count; i++)
		{
			Player* pNew = new Player();
			pNew->x = packet.data[i].x;
			pNew->y = packet.data[i].y;
			players.insert(make_pair(packet.data[i].userIndex, pNew));
		}
	}
	break;
	case PACKET_TYPE_SEND_POS:
	{
		PACKET_SEND_POS packet;
		memcpy(&packet, szBuf, header.len);

		players[packet.data.userIndex]->x = packet.data.x;
		players[packet.data.userIndex]->y = packet.data.y;
	}
	break;
	}
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