#pragma once
#include <Windows.h>
#include "System.h"

#define WINDOW_SYSTEM WindowSystem::GetInstance()
#define WINDOW_HANDLE WindowSystem::GetInstance()->GetWindowHandle()

class GraphicSystem;

/**
@brief ������ �ý��� Ŭ����
@details WinMain ���θ� ������ Ŭ����
@details �����츦 �����ϰ� �ʱ�ȭ�Ѵ�
@details �������� �޼����� ó���Ѵ�
@author Dayeol Hyeon
*/
class WindowSystem : public System
{
private:
	static WindowSystem* instance;

	HWND hWnd;
	HINSTANCE hInstance;
	int exitState;
	char windowName[256];

	WindowSystem();

public:
	virtual ~WindowSystem();

	/**
	@brief ������ �ʱ�ȭ
	@details ������ Ŭ���� ��� �۾�
	@param HINSTANCE hInstance WinMain�� ���޵Ǵ� ù ��° ���ڰ�
	@param char* windowName ������ �̸�
	*/
	void Init(HINSTANCE hInstance, const char* windowName);

	/**
	@brief ���� ������ ����
	@details ���� �����츦 �����Ѵ�
	*/
	void InitWindow();

	/**
	@brief �޼��� ó��
	@details ������ �޼����� ó���Ѵ�
	@details ���� ������ ��ũ�� ������Ʈ �Լ��� �Ķ���ͷ� �޾�
	@details �޼��� ������ ����� �� ó���Ѵ�
	*/
	void ProcessMessage();

	HWND GetWindowHandle()
	{
		return hWnd;
	}

	static WindowSystem* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new WindowSystem();
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