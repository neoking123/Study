#include <WinSock2.h>
#include <windows.h>
#include <map>
#include "..\..\Common\ChessPacket.h"
#include "ChessGame.h"
#include "Player.h"
#include "Macro.h"
#include "LobbyManager.h"
#include "ChessBoard.h"
using namespace std;

#define SERVERIP "127.0.0.1"
#define SERVERPORT 9000
#define BUFSIZE 512
#define WM_SOCKET (WM_USER+1)

class SERVER_INFO
{
public:
	char serverBuf[BUFSIZE];
	int len;
};

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void ProcessSocketMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
bool ProcessPacket(char* szBuf, int& len);
void err_display(const char* msg);
void err_display(int errcode);
void err_quit(const char* msg);

HINSTANCE g_hInst;
char g_szClassName[256] = "ChessClient";
SOCKET sock;
SERVER_INFO* server;
map<int, Player*> players;
MOUSE_STATE mouseState = MOUSE_STATE::CLICK_UP;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	//메모리 릭
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtDumpMemoryLeaks();
	//_CrtSetBreakAlloc(160);

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

	hWnd = CreateWindow(g_szClassName, g_szClassName, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, CW_USEDEFAULT, CW_USEDEFAULT,
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

	server = new SERVER_INFO();
	server->len = 0;
	ChessGame::GetInstance()->Init(hWnd, sock);
	
	while (true)
	{
		/// 메시지큐에 메시지가 있으면 메시지 처리
		if (PeekMessage(&Message, NULL, 0U, 0U, PM_REMOVE))
		{
			if (Message.message == WM_QUIT)
				break;

			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
		else
		{
			ChessGame::GetInstance()->Update();
		}
	}

	ChessGame::GetInstance()->Release();
	SAFE_DELETE(server);
	closesocket(sock);
	WSACleanup();

	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage)
	{
	case WM_LBUTTONDOWN:
		if (mouseState == MOUSE_STATE::CLICK_DOWN)
			return 0;

		mouseState = MOUSE_STATE::CLICK_DOWN;
		ChessGame::GetInstance()->MouseInput(LOWORD(lParam), HIWORD(lParam), MOUSE_STATE::CLICK_DOWN);
		return 0;

	case WM_LBUTTONUP:
		mouseState = MOUSE_STATE::CLICK_UP;
		ChessGame::GetInstance()->MouseInput(LOWORD(lParam), HIWORD(lParam), MOUSE_STATE::CLICK_UP);
		return 0;

	case WM_GETMINMAXINFO:
		((MINMAXINFO*)lParam)->ptMaxTrackSize.x = 1280;
		((MINMAXINFO*)lParam)->ptMaxTrackSize.y = 995;
		((MINMAXINFO*)lParam)->ptMinTrackSize.x = 1280;
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = 995;
		return 0;

	case WM_SOCKET:
		ProcessSocketMessage(hWnd, iMessage, wParam, lParam);
		//InvalidateRect(hWnd, NULL, true);
		return 0;

	case WM_DESTROY:
		for (auto iter = players.begin(); iter != players.end(); iter++)
		{
			SAFE_DELETE(iter->second);
		}
		players.clear();
		PostQuitMessage(0);
		return 0;
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

void ProcessSocketMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
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
		char buf[BUFSIZE];

		retval = recv(wParam, buf, BUFSIZE, 0);
		if (retval == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				//cout << "err on recv!!" << endl;
				err_quit("recv()");
			}
		}

		while (true)
		{
			if (!ProcessPacket(buf, retval))
			{
				Sleep(100);
				break;
			}
			else
			{
				if (server->len < sizeof(PACKET_HEADER))
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

bool ProcessPacket(char* buf, int& len)
{
	if (len > 0)
	{
		memcpy(&server->serverBuf[server->len], buf, len);
		server->len += len;
		len = 0;
	}

	if (server->len < sizeof(PACKET_HEADER))
		return false;

	PACKET_HEADER header;
	memcpy(&header, server->serverBuf, sizeof(header));

	switch (header.type)
	{
	case PACKET_TYPE::PACKET_TYPE_LOGIN:
	{
		PACKET_LOGIN packet;
		memcpy(&packet, buf, header.len);
		ChessGame::GetInstance()->playerIndex = packet.loginIndex;
	}
	break;

	case PACKET_TYPE::PACKET_TYPE_USER_DATA:
	{
		PACKET_USER_DATA packet;
		memcpy(&packet, buf, header.len);

		for (auto iter = players.begin(); iter != players.end(); iter++)
		{
			SAFE_DELETE(iter->second);
		}
		players.clear();

		if (packet.userCount <= 0)
			break;

		for (int i = 0; i < packet.userCount; i++)
		{
			Player* player = new Player();
			player->name = packet.userData->userName;
			players.insert(make_pair(packet.userData[i].userIndex, player));
		}

	}
	break;

	case PACKET_TYPE::PACKET_TYPE_LOBBY_DATA:
	{
		PACKET_LOBBY_DATA packet;
		memcpy(&packet, buf, header.len);

		LobbyManager::GetInstance()->roomNum = packet.lobyData.roomNum;
		LobbyManager::GetInstance()->maxRoomNum = packet.lobyData.maxRoomNum;

		if (LobbyManager::GetInstance()->roomNum <= 0)
			break;

		LobbyManager::GetInstance()->ClearRooms();
		LobbyManager::GetInstance()->roomCount = 0;
		for (int i = 0; i < LobbyManager::GetInstance()->roomNum; i++)
		{
			LobbyManager::GetInstance()->CreateRoom(packet.lobyData.roomsData[i].roomName, packet.lobyData.roomsData[i].inPlayerNum);
		}

		for (int i = 0; i < LobbyManager::GetInstance()->roomNum; i++)
		{
			LobbyManager::GetInstance()->SetInPlayer(i, packet.lobyData.roomsData[i].inPlayer[0], packet.lobyData.roomsData[i].inPlayer[1]);
			LobbyManager::GetInstance()->SetIsStart(i, packet.lobyData.roomsData[i].isStart);
			LobbyManager::GetInstance()->SetCanStart(i, packet.lobyData.roomsData[i].canStart);
		}

	}
	break;

	case PACKET_TYPE::PACKET_TYPE_MOVE_TO:
	{
		PACKET_MOVE_TO packet;
		memcpy(&packet, buf, header.len);

		ChessGame::GetInstance()->curTurn = packet.turn;
		ChessBoard::GetInstance()->checkState = packet.check;
		ChessBoard::GetInstance()->checkmate = packet.checkmate;
		ChessBoard::GetInstance()->MoveTo(packet.moveDate.curPos, packet.moveDate.targetPos);
	}
	break;
	}

	memcpy(&server->serverBuf, &server->serverBuf[header.len], server->len - header.len);
	server->len -= header.len;

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