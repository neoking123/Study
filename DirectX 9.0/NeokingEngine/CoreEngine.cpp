#include "CoreEngine.h"
#include "GraphicSystem.h"

CoreEngine* CoreEngine::instance = nullptr;


CoreEngine::CoreEngine()
{

}

CoreEngine::~CoreEngine()
{
}

void CoreEngine::Init(HINSTANCE hInstance)
{
	windowSystem.Init(hInstance, "Neoking Engine");
	windowSystem.InitWindow();
	GRAPHIC_SYSTEM->InitD3D(windowSystem.GetWindowHandle());
}

void CoreEngine::Update()
{
	windowSystem.ProcessMessage();
}

void CoreEngine::Release()
{
	GRAPHIC_SYSTEM->Release();
}
