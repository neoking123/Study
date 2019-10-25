#include <Windows.h>
#include "CoreEngine.h"
#include "GameFrame.h"
//using namespace Object3D;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	// ���� �ʱ�ȭ
	CORE_ENGINE->Init(hInstance);

	// ���� �ʱ�ȭ �κ�
	GAME_FRAME->Init();

	// ���� ����
	CORE_ENGINE->Update();

	// ���� ����
	CORE_ENGINE->Release();
}