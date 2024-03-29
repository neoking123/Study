#pragma once
#include <Windows.h>
#pragma pack(1)

enum PACKET_TYPE
{
	PACKET_TYPE_LOGIN = 1,
	PACKET_TYPE_USER_DATA,
	PACKET_TYPE_LOBBY_DATA,
	PACKET_TYPE_CREATE_ROOM,
	PACKET_TYPE_ENTER_ROOM,
	PACKET_TYPE_ROOM_STATE,
	PACKET_TYPE_MOVE_TO,
	PACKET_TYPE_CHAT,
	PACKET_TYPE_BACK_TO_LOBBY
};

struct PACKET_HEADER
{
	int type;
	int len;
};

struct USER_DATA
{
	int userIndex;
	int inRoomNum;
	//int userNameLen;
	char userName[32];
	//int x;
	//int y;
};

struct ROOM_DATA
{
	int inPlayerNum;
	char roomName[32];
	int inPlayer[2];
	bool isStart;
	bool canStart;
};

struct LOBY_DATA
{
	int roomNum;
	int maxRoomNum;
	ROOM_DATA roomsData[20];
};

struct MOVE_DATA
{
	int pieceType;
	int pieceColor;
	POINT curPos;
	POINT targetPos;
};

struct PACKET_LOGIN_TO_CLIENT
{
	PACKET_HEADER header;
	int loginIndex;
};

struct PACKET_USER_DATA
{
	PACKET_HEADER header;
	int userCount;
	USER_DATA userData[20];
};

struct PACKET_LOBBY_DATA
{
	PACKET_HEADER header;
	LOBY_DATA lobyData;
};

struct PACKET_CREATE_ROOM
{
	PACKET_HEADER header;
	ROOM_DATA roomData;
};

struct PACKET_ENTER_ROOM
{
	PACKET_HEADER header;
	int roomNum;
	int playerIndex;
};

struct PACKET_ROOM_STATE
{
	PACKET_HEADER header;
	int roomNum;
	bool isStart;
	bool canStart;
};

struct PACKET_MOVE_TO
{
	PACKET_HEADER header;
	int roomNum;
	int turn;
	bool check;
	int checkmate;
	MOVE_DATA moveDate;
};

struct PACKET_CHAT
{
	PACKET_HEADER header;
	int playerIndex;
	int roomNum;
	char chat[128];
};

struct PACKET_BACK_TO_LOBBY
{
	PACKET_HEADER header;
	int roomNum;
	int playerIndex;
};

#pragma pack()