#include <Windows.h>
#include "CoreEngine.h"
#include "GameFrame.h"
//using namespace Object3D;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	// 엔진 초기화
	CORE_ENGINE->Init(hInstance);

	// 게임 초기화
	GAME_FRAME->Init();

	// 게임 루프
	CORE_ENGINE->Update();

	// 엔진 종료
	CORE_ENGINE->Release();
}