#include "CircusTroupe.h"
#include "SceneManager.h"
#include "Character.h"
#include "Macro.h"

CircusTroupe* CircusTroupe::pInstance = nullptr;

CircusTroupe::CircusTroupe()
{
}

CircusTroupe::~CircusTroupe()
{
}

void CircusTroupe::Init(HWND hWnd, HDC hdc)
{
	// SceneManger 초기화
	SIZE sceneSize = { 515, 413 };
	//SIZE sceneSize = { 1280, 768 };
	SceneManager::GetInstance()->Init(hdc, sceneSize);

	//캐릭터 생성, 초기화
	player = new Character();
	player->Init(POINT{ 100, 305 }, 6);
	player->SetSpeed(5);
	SceneManager::GetInstance()->AddSceneObject(player);

	SceneManager::GetInstance()->SetOffset(player->GetPosition());
}

void CircusTroupe::Draw(HDC hdc)
{
	SceneManager::GetInstance()->DrawScene(hdc);
}

void CircusTroupe::Input(WPARAM wParam, KEY_STATE keyState)
{
	player->Input(wParam, keyState);
	SceneManager::GetInstance()->Input(player->GetPosition(),keyState);
}

void CircusTroupe::Update()
{
	player->Jump();
	player->ForceGravity();
}

void CircusTroupe::Release()
{
	SAFE_DELETE(player);
}
