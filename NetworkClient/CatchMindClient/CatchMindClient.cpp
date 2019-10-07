#include <WinSock2.h>
#include <windows.h>
#include <map>
#include "..\..\Common\CatchMindPacket.h"
using namespace std;

#define	MAX_BUFFER		1024
#define SERVER_PORT		9000
#define SERVER_IP		"127.0.0.1"
#define WM_SOCKET (WM_USER+1)

class SERVER_INFO
{
public:
	char serverBuf[MAX_BUFFER];
	int len;
};

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void ProcessSocketMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
bool ProcessPacket(char* szBuf, int& len);
void err_display(const char* msg);
void err_display(int errcode);
void err_quit(const char* msg);

HINSTANCE g_hInst;
HBRUSH hBrush = NULL;
HWND hChatCtrl = NULL;

char g_szClassName[256] = "CatchMindClient";
SOCKET sock;
SERVER_INFO* server;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	//�޸� ��
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

	WSADATA wsaData;
	// ���� ������ 2.2�� �ʱ�ȭ
	int nRet = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (nRet != 0) {
		return -1;
	}

	// TCP ���� ����
	SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (clientSocket == INVALID_SOCKET) {
		err_quit("err on socket");
		return -1;
	}

	// ������ ���� ������ ������ ����ü
	SOCKADDR_IN stServerAddr;
	char	szOutMsg[MAX_BUFFER];
	char	sz_socketbuf_[MAX_BUFFER];
	stServerAddr.sin_family = AF_INET;
	// ������ ���� ��Ʈ �� IP
	stServerAddr.sin_port = htons(SERVER_PORT);
	stServerAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

	nRet = connect(clientSocket, (sockaddr*)&stServerAddr, sizeof(sockaddr));
	if (nRet == SOCKET_ERROR) {
		err_quit("err on connect");
		return -1;
	}
	//ChessGame::GetInstance()->Init(hWnd, sock, g_hInst);

	while (true)
	{
		/// �޽���ť�� �޽����� ������ �޽��� ó��
		if (PeekMessage(&Message, NULL, 0U, 0U, PM_REMOVE))
		{
			if (Message.message == WM_QUIT)
				break;

			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
		else
		{
			//ChessGame::GetInstance()->Update();
		}
	}

	//ChessGame::GetInstance()->Release();
	//SAFE_DELETE(server);
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
	case WM_CREATE:
		//ChattingManager::GetInstance()->Init(hWnd, g_hInst);
		//SetFocus(ChattingManager::GetInstance()->hChat);
		return 0;

	case WM_LBUTTONDOWN:
		//ChessGame::GetInstance()->MouseInput(LOWORD(lParam), HIWORD(lParam), MOUSE_STATE::CLICK_DOWN);
		return 0;

	case WM_LBUTTONUP:
		//ChessGame::GetInstance()->MouseInput(LOWORD(lParam), HIWORD(lParam), MOUSE_STATE::CLICK_UP);
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

	case WM_CTLCOLOREDIT:
		/*if ((HWND)lParam == ChattingManager::GetInstance()->hChat || (HWND)lParam == ChattingManager::GetInstance()->hChatList)
		{
			if (hBrush) { DeleteObject(hBrush); hBrush = NULL; }
			hBrush = CreateSolidBrush(RGB(0, 91, 184));
			SetBkColor((HDC)wParam, RGB(0, 91, 184));
			SetTextColor((HDC)wParam, RGB(255, 255, 255));
			return (LRESULT)hBrush;
		}*/

	case WM_DESTROY:
		DeleteObject(hBrush);
		/*for (auto iter = players.begin(); iter != players.end(); iter++)
		{
			SAFE_DELETE(iter->second);
		}
		players.clear();*/
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
		char buf[MAX_BUFFER];

		retval = recv(wParam, buf, MAX_BUFFER, 0);
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
		//ChessGame::GetInstance()->playerIndex = packet.loginIndex;
	}
	break;

	case PACKET_TYPE::PACKET_TYPE_USER_DATA:
	{
		PACKET_USER_DATA packet;
		memcpy(&packet, buf, header.len);
	}
	break;

	case PACKET_TYPE::PACKET_TYPE_LOBBY_DATA:
	{
		PACKET_LOBBY_DATA packet;
		memcpy(&packet, buf, header.len);
	}
	break;

	case PACKET_TYPE::PACKET_TYPE_MOVE_TO:
	{
		PACKET_MOVE_TO packet;
		memcpy(&packet, buf, header.len);
	}
	break;

	case PACKET_TYPE::PACKET_TYPE_CHAT:
	{
		PACKET_CHAT packet;
		memcpy(&packet, buf, header.len);
	}
	break;

	}

	memcpy(&server->serverBuf, &server->serverBuf[header.len], server->len - header.len);
	server->len -= header.len;

	return true;
}

// ���� �Լ� ���� ���
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

// ���� �Լ� ���� ���
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

// ���� �Լ� ���� ��� �� ����
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
