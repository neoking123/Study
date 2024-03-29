#include <WinSock2.h>
#include <stdlib.h>
#include <sstream>
#include <stdio.h>
#include <map>
#include "..\..\Common\ChessPacket.h"
#include "Macro.h"

using namespace std;

#define SERVERPORT 9000
#define BUFSIZE 512
#define WM_SOCKET (WM_USER + 1)
#define MAX_ROOM_NUM 10
#define MAX_SPEC_NUM 2
char windowClassName[256] = "ChessServer";

enum CHESS_PIECES
{
	KING_W,
	QUEEN_W,
	ROOK_W,
	BISHOP_W,
	KNIGHT_W,
	PAWN_W,
	NONE,
	KING_B,
	QUEEN_B,
	ROOK_B,
	BISHOP_B,
	KNIGHT_B,
	PAWN_B
};

class PLAYER_INFO
{
public:
	int index;
	char userBuf[BUFSIZE];
	char nickName[128];
	int inRoomNum = -1;
	int len;
};

class ROOM_INFO
{
public:
	char roomName[128];
	int inPlayerNum;
	int inPlayers[2] = { -1, -1 };
	bool isStart = false;
	bool canStart = false;
	int board[8][8];
	//int spectators[MAX_SPEC_NUM];
	//int roomNameLen;
};

int userIndex = 0;
int roomNum = 0;
map<SOCKET, PLAYER_INFO*> connectedUsers;
map<int, ROOM_INFO*> createdRooms;
//int board[8][8];

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void ProcessSocketMessage(HWND, UINT, WPARAM, LPARAM);
bool ProcessPacket(PLAYER_INFO* pUser, char* szBuf, int& len);
void err_display(const char* msg);
void err_display(int errcode);
void err_quit(const char* msg);
void SendLobbyData();
void InitChessBoard(int board[][8]);
void InitSpectatorArray(int spectator[MAX_SPEC_NUM]);

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

	// 보드 초기화
	void InitChessBoard();

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
		printf("\n[Chess Server] 클라이언트 접속: IP 주소=%s, 포트번호=%d\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

		retval = WSAAsyncSelect(client_sock, hWnd, WM_SOCKET, FD_READ | FD_WRITE | FD_CLOSE);
		if (retval == SOCKET_ERROR)
		{
			err_display("WSAAsyncSelect()");
		}

		PLAYER_INFO* playerInfo = new PLAYER_INFO();
		playerInfo->index = userIndex++;
		playerInfo->len = 0;
		stringstream ss;
		ss << playerInfo->index;
		string str = "player" + ss.str();
		strcpy(playerInfo->nickName, str.c_str());
		connectedUsers.insert(make_pair(client_sock, playerInfo));

		// 로그인 정보 전송
		PACKET_LOGIN_TO_CLIENT packet;
		packet.header.type = PACKET_TYPE_LOGIN;
		packet.header.len = sizeof(PACKET_LOGIN_TO_CLIENT);
		packet.loginIndex = playerInfo->index;
		send(client_sock, (const char*)&packet, packet.header.len, 0);

		Sleep(500);

		// 유저 정보 전송
		PACKET_USER_DATA userDatePacket;
		userDatePacket.header.type = PACKET_TYPE_USER_DATA;
		userDatePacket.userCount = connectedUsers.size();
		int i = 0;
		for (auto iter = connectedUsers.begin(); iter != connectedUsers.end(); iter++, i++)
		{
			userDatePacket.userData[i].userIndex = iter->second->index;
		}

		int k = 0;
		for (auto iter = connectedUsers.begin(); iter != connectedUsers.end(); iter++, k++)
		{
			strcpy(userDatePacket.userData[k].userName, iter->second->nickName);
			userDatePacket.userData[k].inRoomNum = iter->second->inRoomNum;
		}

		userDatePacket.header.len = sizeof(PACKET_HEADER) + sizeof(int) + (sizeof(int) + sizeof(int) + sizeof(char) * 32) * connectedUsers.size();

		for (auto iter = connectedUsers.begin(); iter != connectedUsers.end(); iter++)
		{
			send(iter->first, (const char*)&userDatePacket, userDatePacket.header.len, 0);
		}

		Sleep(500);

		// 로비 정보 전송
		SendLobbyData();
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

		PLAYER_INFO* user = connectedUsers[wParam];

		while (true)
		{
			if (!ProcessPacket(user, buf, retval))
			{
				Sleep(100);
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
		SOCKADDR_IN clientaddr;
		int addrlen = sizeof(clientaddr);;
		getpeername(wParam, (SOCKADDR*)&clientaddr, &addrlen);
		closesocket(wParam);
		SAFE_DELETE(connectedUsers[wParam]);
		connectedUsers.erase(wParam);
		printf("[Chess Server] 클라이언트 종료: IP 주소=%s, 포트번호=%d\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
		
		break;
	}
}

// 패킷 처리 함수
bool ProcessPacket(PLAYER_INFO* userInfo, char* buf, int& len)
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
	case PACKET_TYPE::PACKET_TYPE_CREATE_ROOM:
	{
		PACKET_CREATE_ROOM packet;
		memcpy(&packet, buf, header.len);

		if (roomNum >= MAX_ROOM_NUM)
			break;

		ROOM_INFO* roomInfo = new ROOM_INFO();
		strcpy(roomInfo->roomName, packet.roomData.roomName);
		roomInfo->inPlayerNum = packet.roomData.inPlayerNum;
		roomInfo->inPlayers[0] = packet.roomData.inPlayer[0];
		InitChessBoard(roomInfo->board);
		//InitSpectatorArray(roomInfo->spectators);
		createdRooms.insert(make_pair(roomNum, roomInfo));

		for (auto iter = connectedUsers.begin(); iter != connectedUsers.end(); iter++)
		{
			if (iter->second->index == packet.roomData.inPlayer[0])
			{
				iter->second->inRoomNum = roomNum;
			}
		}
		roomNum++;

		SendLobbyData();
	}
	break;

	case PACKET_TYPE::PACKET_TYPE_ENTER_ROOM:
	{
		PACKET_ENTER_ROOM packet;
		memcpy(&packet, buf, header.len);
		
		for (auto iter = createdRooms.begin(); iter != createdRooms.end(); iter++)
		{
			if (iter->first == packet.roomNum)
			{
				if (iter->second->inPlayers[1] == -1)
				{
					iter->second->inPlayers[1] = packet.playerIndex;
					
				}
				else
				{
					/*for (int i = 0; i < 20; i++)
					{
						if (iter->second->spectators[i] == -1)
						{
							iter->second->spectators[i] = packet.playerIndex;
							break;
						}
					}*/
				}
				iter->second->inPlayerNum++;
			}
		}

		for (auto iter = connectedUsers.begin(); iter != connectedUsers.end(); iter++)
		{
			if (iter->second->index == packet.playerIndex)
			{
				iter->second->inRoomNum = packet.roomNum;
			}
		}

		SendLobbyData();
	}
	break;

	case PACKET_TYPE::PACKET_TYPE_ROOM_STATE:
	{
		PACKET_ROOM_STATE packet;
		memcpy(&packet, buf, header.len);

		createdRooms[packet.roomNum]->isStart = packet.isStart;
		createdRooms[packet.roomNum]->canStart = packet.canStart;

		SendLobbyData();
	}
	break;

	case PACKET_TYPE::PACKET_TYPE_MOVE_TO:
	{
		PACKET_MOVE_TO packet;
		memcpy(&packet, buf, header.len);

		POINT curPos = packet.moveDate.curPos;
		POINT targetPos = packet.moveDate.targetPos;

		for (auto iter = createdRooms.begin(); iter != createdRooms.end(); iter++)
		{
			if (iter->first == packet.roomNum)
			{
				iter->second->board[targetPos.y][targetPos.x] = iter->second->board[curPos.y][curPos.x];
				iter->second->board[curPos.y][curPos.x] = CHESS_PIECES::NONE;

				for (auto userIter = connectedUsers.begin(); userIter != connectedUsers.end(); userIter++)
				{
					if (userIter->second->index == iter->second->inPlayers[0] 
						|| userIter->second->index == iter->second->inPlayers[1])
					{
						send(userIter->first, (const char*)&packet, header.len, 0);
					}
				}
			}
		}
	}
	break;

	case PACKET_TYPE::PACKET_TYPE_CHAT:
	{
		PACKET_CHAT packet;
		memcpy(&packet, buf, header.len);

		for (auto iter = connectedUsers.begin(); iter != connectedUsers.end(); iter++)
		{
			if (iter->second->inRoomNum == packet.roomNum)
			{
				send(iter->first, (const char*)&packet, header.len, 0);
			}
		}
	}
	break;

	case PACKET_TYPE::PACKET_TYPE_BACK_TO_LOBBY:
	{
		PACKET_BACK_TO_LOBBY packet;
		memcpy(&packet, buf, header.len);

		for (auto iter = createdRooms.begin(); iter != createdRooms.end(); iter++)
		{
			if (iter->first == packet.roomNum)
			{
				if (iter->second->inPlayers[0] == packet.playerIndex)
				{
					if (iter->second->inPlayers[1] == -1)
					{
						createdRooms.erase(iter->first);
						roomNum--;
						SendLobbyData();
						break;
					}
					else
					{
						iter->second->inPlayers[0] = iter->second->inPlayers[1];
						iter->second->inPlayers[1] = -1;
						iter->second->inPlayerNum = 1;
						iter->second->canStart = false;
						iter->second->isStart = false;
						SendLobbyData();
					}
					
				}
				else if (iter->second->inPlayers[1] == packet.playerIndex)
				{
					//iter->second->inPlayer[0] = iter->second->inPlayer[1];
					iter->second->inPlayers[1] = -1;
					iter->second->inPlayerNum = 1;
					iter->second->canStart = false;
					iter->second->isStart = false;
					SendLobbyData();
				}
			}
		}

		for (auto iter = connectedUsers.begin(); iter != connectedUsers.end(); iter++)
		{
			if (iter->second->index == packet.playerIndex)
			{
				iter->second->inRoomNum = -1;
			}
		}

	}
	break;

	}

	memcpy(&userInfo->userBuf, &userInfo->userBuf[header.len], userInfo->len - header.len);
	userInfo->len -= header.len;

	return true;
}

void SendLobbyData()
{
	PACKET_LOBBY_DATA lobbyDataPacket;
	lobbyDataPacket.header.type = PACKET_TYPE::PACKET_TYPE_LOBBY_DATA;
	int i = 0;
	for (auto iter = createdRooms.begin(); iter != createdRooms.end(); iter++, i++)
	{
		strcpy(lobbyDataPacket.lobyData.roomsData[i].roomName, createdRooms[i]->roomName);
		lobbyDataPacket.lobyData.roomsData[i].inPlayerNum = createdRooms[i]->inPlayerNum;
		lobbyDataPacket.lobyData.roomsData[i].inPlayer[0] = createdRooms[i]->inPlayers[0];
		lobbyDataPacket.lobyData.roomsData[i].inPlayer[1] = createdRooms[i]->inPlayers[1];
		lobbyDataPacket.lobyData.roomsData[i].isStart = createdRooms[i]->isStart;
		lobbyDataPacket.lobyData.roomsData[i].canStart = createdRooms[i]->canStart;
	}
	lobbyDataPacket.lobyData.roomNum = roomNum;
	lobbyDataPacket.lobyData.maxRoomNum = MAX_ROOM_NUM;
	lobbyDataPacket.header.len = sizeof(PACKET_HEADER) + sizeof(int) + sizeof(int) + roomNum * sizeof(ROOM_DATA);

	for (auto iter = connectedUsers.begin(); iter != connectedUsers.end(); iter++)
	{
		send(iter->first, (const char*)&lobbyDataPacket, lobbyDataPacket.header.len, 0);
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

void InitChessBoard(int board[][8])
{

	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			board[y][x] = CHESS_PIECES::NONE;
		}
	}

	board[0][0] = CHESS_PIECES::ROOK_B;
	board[0][1] = CHESS_PIECES::KNIGHT_B;
	board[0][2] = CHESS_PIECES::BISHOP_B;
	board[0][3] = CHESS_PIECES::QUEEN_B;
	board[0][4] = CHESS_PIECES::KING_B;
	board[0][5] = CHESS_PIECES::BISHOP_B;
	board[0][6] = CHESS_PIECES::KNIGHT_B;
	board[0][7] = CHESS_PIECES::ROOK_B;

	board[1][0] = CHESS_PIECES::PAWN_B;
	board[1][1] = CHESS_PIECES::PAWN_B;
	board[1][2] = CHESS_PIECES::PAWN_B;
	board[1][3] = CHESS_PIECES::PAWN_B;
	board[1][4] = CHESS_PIECES::PAWN_B;
	board[1][5] = CHESS_PIECES::PAWN_B;
	board[1][6] = CHESS_PIECES::PAWN_B;
	board[1][7] = CHESS_PIECES::PAWN_B;

	board[7][0] = CHESS_PIECES::ROOK_W;
	board[7][1] = CHESS_PIECES::KNIGHT_W;
	board[7][2] = CHESS_PIECES::BISHOP_W;
	board[7][3] = CHESS_PIECES::QUEEN_W;
	board[7][4] = CHESS_PIECES::KING_W;
	board[7][5] = CHESS_PIECES::BISHOP_W;
	board[7][6] = CHESS_PIECES::KNIGHT_W;
	board[7][7] = CHESS_PIECES::ROOK_W;

	board[6][0] = CHESS_PIECES::PAWN_W;
	board[6][1] = CHESS_PIECES::PAWN_W;
	board[6][2] = CHESS_PIECES::PAWN_W;
	board[6][3] = CHESS_PIECES::PAWN_W;
	board[6][4] = CHESS_PIECES::PAWN_W;
	board[6][5] = CHESS_PIECES::PAWN_W;
	board[6][6] = CHESS_PIECES::PAWN_W;
	board[6][7] = CHESS_PIECES::PAWN_W;
}

void InitSpectatorArray(int spectator[MAX_SPEC_NUM])
{
	for (int i = 0; i < MAX_SPEC_NUM; i++)
	{
		spectator[i] = -1;
	}
}