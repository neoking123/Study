#include "CoreEngine.h"
#include "GraphicSystem.h"
#include "WindowSystem.h"
#include "InputSystem.h"

CoreEngine* CoreEngine::instance = nullptr;


CoreEngine::CoreEngine()
{

}

CoreEngine::~CoreEngine()
{
}

void CoreEngine::Init(HINSTANCE hInstance)
{
	WINDOW_SYSTEM->Init(hInstance, "Neoking Engine");
	WINDOW_SYSTEM->InitWindow();
	GRAPHIC_SYSTEM->InitD3D(WINDOW_SYSTEM->GetWindowHandle());
	GRAPHIC_SYSTEM->InitMatrix();
	INPUT_SYSTEM->Init();
}

void CoreEngine::Update()
{
	WINDOW_SYSTEM->ProcessMessage();
}

void CoreEngine::Release()
{
	GRAPHIC_SYSTEM->Release();

	WINDOW_SYSTEM->FreeInstance();
	GRAPHIC_SYSTEM->FreeInstance();
	INPUT_SYSTEM->FreeInstance();
}
