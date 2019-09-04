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
	SIZE sceneSize = { 576, 413 };
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

void CircusTroupe::Input(WPARAM wParam)
{
	player->Input(wParam);
	SceneManager::GetInstance()->Input(player->GetPosition());
}

void CircusTroupe::Update()
{
}

void CircusTroupe::Release()
{
	SAFE_DELETE(player);
}
