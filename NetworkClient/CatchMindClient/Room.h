#pragma once
#include <Windows.h>
#include <string>
#include "UIObject.h"
#include "ButtonComponent.h"
using namespace std;

#define ROOM_WIDTH 280
#define ROOM_HEIGHT 85
#define ROOM_MARGINE_WIDTH 24
#define ROOM_MARGINE_HEIGHT 64
#define MAX_ROOM_IN_NUM 8

enum ROOM_STATE
{
	ROOM_WATING,
	ROOM_FULL,
	ROOM_PLAYING
};

/**
* @brief 로비의 방 정보를 관리
* @details 로비에서 생성된 방 객체
* @details 서버로 부터 받은 방 정보를 관리한다
* @author Dayeol Hyeon
*/

class Room : public UIObject
{
private:
	string roomName;
	string password;
	bool isSecret;
	ROOM_STATE roomState;
	ButtonComponent button;

	void DrawRoomFrame(HDC hdc);
	void DrawRoomName(HDC hdc);
	void DrawRoomNumber(HDC hdc);
	void DrawRoomIcon(HDC hdc);
	void DrawInPlayerNum(HDC hdc);
	void DrawRoomState(HDC hdc);
	void DarwPlayerIcon(HDC hdc);
	void DrawKeyIcon(HDC hdc);
	void CheckRoomState();

public:
	int roomNum;
	int roomAlignCount;
	int inPlayerNum;
	int inPlayer[MAX_ROOM_IN_NUM] = { -1, -1, -1, -1, -1, -1, -1, -1 };
	bool reayState[MAX_ROOM_IN_NUM] = { 0, 0, 0, 0, 0, 0, 0, 0 };
	char answerWord[32];
	int curTurn = -1;
	int turnCount = 0;
	int MaxInPlayerNum;
	int roomMasterIndex;
	bool isStart;
	bool canStart;

	Room();
	~Room();
	void Init(int roomNum, int roomAlignCount, string name, int x, int y, int curInplayerNum, int MaxInplayerNum, int roomMasterIndex, bool isSecret = false, string password = "");
	virtual void Init(int x, int y) override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

	bool CheckIsClicked(int x, int y);

	inline void SetRoomState(ROOM_STATE newRoomState)
	{
		roomState = newRoomState;
	}
};