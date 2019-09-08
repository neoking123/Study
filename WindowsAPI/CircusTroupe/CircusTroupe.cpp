#include "CircusTroupe.h"
#include "SceneManager.h"
#include "Character.h"
#include "Enemy.h"
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
	// SceneManger �ʱ�ȭ
	SIZE sceneSize = { 515, 413 };
	//SIZE sceneSize = { 1280, 768 };
	SceneManager::GetInstance()->Init(hdc, sceneSize);

	//ĳ���� ����, �ʱ�ȭ
	player = new Character();
	player->Init(POINT{ 100, 305 }, 6);
	player->SetSpeed(5);
	SceneManager::GetInstance()->AddSceneObject(player);
	SceneManager::GetInstance()->SetOffset(player->GetPosition());


	//�� ����, �ʱ�ȭ
	enemy = new Enemy();
	enemy->Init(POINT{ 400, 190 }, 9);
	//enemy->SetSpeed(5);
	SceneManager::GetInstance()->AddSceneObject(enemy);

}

void CircusTroupe::Draw(HDC hdc)
{
	SceneManager::GetInstance()->DrawScene(hdc);
}

void CircusTroupe::Input(WPARAM wParam, KEY_STATE keyState)
{
	player->Input(wParam, keyState);
}

void CircusTroupe::Update()
{
	player->Jump();
	SceneManager::GetInstance()->Input(player->GetPosition());

	enemy->Move();
}

void CircusTroupe::Release()
{
	SAFE_DELETE(player);
	SAFE_DELETE(enemy);
}
