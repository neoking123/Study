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

enum ROOM_STATE
{
	ROOM_WATING,
	ROOM_FULL,
	ROOM_PLAYING
};

class Room : public UIObject
{
private:
	string roomName;
	string password;
	int inPlayerNum;
	int MaxInPlayerNum;
	bool isSecret;
	bool isStart;
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

	Room();
	~Room();
	void Init(int roomNum, string name, int x, int y, int MaxInplayerNum, bool isSecret = false, string password = "");
	virtual void Init(int x, int y) override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

	void CheckIsCliked(int x, int y);
};