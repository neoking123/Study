#include "CircusTroupe.h"
#include "SceneManager.h"
#include "BitMapManager.h"
#include "Character.h"

CircusTroupe* CircusTroupe::pInstance = nullptr;

CircusTroupe::CircusTroupe()
{
}

CircusTroupe::~CircusTroupe()
{
}

void CircusTroupe::Init(HWND hWnd, HINSTANCE hInst, HDC hdc)
{
	// BitMapManager 초기화
	BitMapManager::GetInstance()->Init(hInst, hdc);

	// SceneManger 초기화
	SIZE sceneSize = { 1024, 768 };
	SceneManager::GetInstance()->Init(sceneSize);

	//캐릭터 생성, 초기화
	player = new Character();
	SceneManager::GetInstance()->AddSceneObject(player, POINT{100, 100}, 5);
}

void CircusTroupe::Draw(HDC hdc)
{
	SceneManager::GetInstance()->DrawScene(hdc);
}

void CircusTroupe::Input(WPARAM wParam)
{
	player->Input(wParam);
}

void CircusTroupe::Update()
{
}

void CircusTroupe::Release()
{
}
