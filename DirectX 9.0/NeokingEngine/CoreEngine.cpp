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
	GraphicSystem::GetInstance()->InitD3D(windowSystem.GetWindowHandle());
}

void CoreEngine::Update(UpdateFunc Update)
{
	windowSystem.ProcessMessage(Update);
}

void CoreEngine::Release()
{
	GraphicSystem::GetInstance()->Release();
}
