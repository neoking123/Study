#pragma once
#include <Windows.h>
#pragma pack(1)

enum PACKET_TYPE
{
	PACKET_TYPE_LOGIN = 1,
	PACKET_TYPE_USER_DATA,
	PACKET_TYPE_LOBBY_DATA,
	PACKET_TYPE_SEND_POS,
	PACKET_TYPE_CREATE_ROOM,
};

struct PACKET_HEADER
{
	int type;
	int len;
};

struct USER_DATA
{
	int userIndex;
	int userNameLen;
	char userName[128];
	//int x;
	//int y;
};

struct ROOM_DATA
{
	char roomName[128];
};

struct LOBY_DATA
{
	int roomNum;
	ROOM_DATA roomsData[20];
};

struct PACKET_LOGIN
{
	PACKET_HEADER header;
	int loginIndex;
};

struct PACKET_USER_DATA
{
	PACKET_HEADER header;
	int count;
	USER_DATA userData[20];
};

struct PACKET_LOBBY_DATA
{
	PACKET_HEADER header;
	LOBY_DATA lobyData;
};

struct PACKET_SEND_POS
{
	PACKET_HEADER header;
	USER_DATA userData;
};

struct PACKET_CREATE_ROOM
{
	PACKET_HEADER header;
	ROOM_DATA roomData;
};


#pragma pack()