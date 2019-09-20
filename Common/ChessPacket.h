#pragma once
#include <Windows.h>
#pragma pack(1)

enum PACKET_TYPE
{
	PACKET_TYPE_LOGIN = 1,
	PACKET_TYPE_USER_DATA,
	PACKET_TYPE_SEND_POS,
};

struct PACKET_HEADER
{
	int type;
	int len;
};

struct USER_DATA
{
	int userIndex;
	int x;
	int y;
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
	USER_DATA data[20];
};

struct PACKET_SEND_POS
{
	PACKET_HEADER header;
	USER_DATA data;
};


#pragma pack()