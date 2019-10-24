#pragma once
#include "..\..\Common\Macro.h"
#include "WindowSystem.h"
#include "PhysicsSystem.h"
#include "InputSystem.h"
#include "MessageManager.h"
#include "Polygon.h"

typedef void(*UpdateFunc)();

class CoreEngine
{
private:
	static CoreEngine* instance;

	CoreEngine();

public:
	WindowSystem windowSystem;
	InputSystem inputSystem;
	PhysicsSystem phsicsSystem;
	MessageManager messageManager;

public:
	~CoreEngine();

	void Init(HINSTANCE hInstance);
	void Update(UpdateFunc Update);
	void Release();

	static CoreEngine* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new CoreEngine();
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

// 윈도우 랩핑
//http://tipssoft.com/bulletin/board.php?bo_table=FAQ&wr_id=2200 참고