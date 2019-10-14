#pragma once
#include <Windows.h>
#pragma pack(1)

#define	MAX_BUFFER		1024
#define MAX_ROOM_NUM 10
#define MAX_ROOM_IN_NUM 8
#define MAX_PLAYER_NUM 100

enum PACKET_TYPE
{
	PACKET_TYPE_LOGIN_TO_CLIENT = 1,
	PACKET_TYPE_LOGIN_TO_SERVER,
	PACKET_TYPE_PLAYER_DATA,
	PACKET_TYPE_LOBBY_DATA,
	PACKET_TYPE_CREATE_ROOM,
	PACKET_TYPE_ENTER_ROOM,
	PACKET_TYPE_ROOM_STATE,
	PACKET_TYPE_MOVE_TO,
	PACKET_TYPE_CHAT,
	PACKET_TYPE_BACK_TO_LOBBY,
	PACKET_TYPE_DRAW_TO_SERVER,
	PACKET_TYPE_DRAW_TO_CLIENT,
	PACKET_TYPE_SKETCH_BOOK,
	PACKET_TYPE_ERASE_ALL_TO_SERVER,
	PACKET_TYPE_ERASE_ALL_TO_CLIENT,
};

struct RGB
{
	unsigned int r;
	unsigned int g;
	unsigned int b;
};

struct PACKET_INFO
{
public:
	char buf[MAX_BUFFER * 250 + 12];
	int len;
};

struct PACKET_HEADER
{
	int type;
	int len;
};

struct PLAYER_DATA
{
	int index;
	int inRoomNum;
	int kungyaNum;
	char nickName[32];
};

struct ROOM_DATA
{
	int roomNum;
	int inPlayerNum;
	int roomMasterNum;
	char roomName[32];
	char answerWord[32];
	int inPlayer[MAX_ROOM_IN_NUM];
	bool readyState[MAX_ROOM_IN_NUM];
	int curTurn;
	bool isStart;
	bool canStart;
};

struct LOBY_DATA
{
	int roomCount;
	int maxRoomNum;
	ROOM_DATA roomsData[MAX_ROOM_NUM];
};

struct MOVE_DATA
{
	int pieceType;
	int pieceColor;
	POINT curPos;
	POINT targetPos;
};

struct BRUSH_DATA
{
	POINT pos = { 0, 0 };
	RGB color = { 0, 0, 0 };
	int thickness = 0;
	bool isClickUp = false;
};

struct PACKET_LOGIN_TO_CLIENT
{
	PACKET_HEADER header;
	int loginIndex;
};

struct PACKET_LOGIN_TO_SERVER
{
	PACKET_HEADER header;
	int playerIndex;
	int kungyaNum;
	char nickName[32];
};

struct PACKET_LOBBY_DATA
{
	PACKET_HEADER header;
	LOBY_DATA lobyData;
};

struct PACKET_PLAYER_DATA
{
	PACKET_HEADER header;
	int playerCount;
	PLAYER_DATA playerData[MAX_PLAYER_NUM];
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
	int playerIndex;
	bool isReady;
	bool isStart;
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

struct PACKET_DRAW_TO_SERVER
{
	PACKET_HEADER header;
	int roomNum;
	BRUSH_DATA brushData;
};

struct PACKET_DRAW_TO_CLIENT
{
	PACKET_HEADER header;
	BRUSH_DATA brushData;
};

struct PACKET_SKETCH_BOOK
{
	PACKET_HEADER header;
	int mouseTrackLen;
	BRUSH_DATA mouseTrack[MAX_BUFFER * 10];
};

struct PACKET_ERASE_ALL_TO_SERVER
{
	PACKET_HEADER header;
	int roomNum;
};

struct PACKET_ERASE_ALL_TO_CLIENT
{
	PACKET_HEADER header;
};

#pragma pack()