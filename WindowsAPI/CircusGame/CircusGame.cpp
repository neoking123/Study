#include "CircusGame.h"
#include "BitMapManager.h"
#include "PlayerInputComponent.h"
#include "Character.h"
#include "Camera.h"
#include "Background.h"

CircusGame* CircusGame::pInstance = nullptr;

CircusGame::CircusGame()
{
}


CircusGame::~CircusGame()
{
}

void CircusGame::Init(HDC hdc, SIZE gameSize)
{
	gameDCSize = gameSize;
	gameDC = CreateCompatibleDC(hdc);
	hBitMap = CreateCompatibleBitmap(hdc, gameDCSize.cx, gameDCSize.cy);
	hOldBitMap = (HBITMAP)SelectObject(gameDC, hBitMap);
	BitMapManager::GetInstance()->Init(gameDC);

	gameObjects.reserve(1000);

	//캐릭터
	playerInput = new PlayerInputComponent();
	player = new Character();
	player->Init(playerInput, 100, 485);
	gameObjects.push_back(player);

	//카메라
	camera = new Camera();
	camera->Init(gameDC, SIZE{ 800, 600 }, 400, 300);
	gameObjects.push_back(camera);
	camera->SetTarget(*player);

	//배경화면
	background = new Background();
	background->Init();
}

void CircusGame::Update()
{
	background->Update(gameDC, *camera);
	player->Update(gameDC);
	camera->Update(gameDC);
}

void CircusGame::Draw(HDC hdc)
{
	BitBlt(hdc, 0, 0, camera->GetSize().cx, camera->GetSize().cy, camera->GetDC(), 0, 0, SRCCOPY);
}

void CircusGame::Input(UINT iMessage, WPARAM wParam)
{
	playerInput->Input(iMessage, wParam);
}

void CircusGame::Release()
{
	SelectObject(gameDC, hOldBitMap);
	DeleteObject(hBitMap);
	DeleteDC(gameDC);

	SAFE_DELETE(playerInput);
	SAFE_DELETE(camera);

	for (auto iter = gameObjects.begin(); iter != gameObjects.end(); iter++)
	{
		SAFE_DELETE(*iter);
	}
}

vector<GameObject*> CircusGame::GetAllObjects()
{
	return gameObjects;
}
