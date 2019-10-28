#pragma once
#include "System.h"

#define INPUT_SYSTEM InputSystem::GetInstance()
#define KEYDOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000 ? 1 : 0))
#define KEYUP(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000 ? 0 : 1))

class InputSystem : public System
{
private:
	static InputSystem* instance;
	DWORD mouseX = 0;
	DWORD mouseY = 0;
	float cameraMoveForce;
	float moveForce;

	InputSystem();

public:
	virtual ~InputSystem();

	void Init();
	void ProcessInput();
	void ProcessMouse();
	void ProcessKey();

	static InputSystem* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new InputSystem();
		}
		return instance;
	}

	static void FreeInstance()
	{
		if (instance != nullptr)
		{
			SAFE_DELETE(instance);
		}
	}
};

