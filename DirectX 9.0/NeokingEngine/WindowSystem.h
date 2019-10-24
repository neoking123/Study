#pragma once
#include <Windows.h>
#include "System.h"

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
	HWND hWnd;
	HINSTANCE hInstance;
	int exitState;
	char windowName[256];

public:
	WindowSystem();
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
	@param void(*Update)() ���� �����ӿ�ũ�� ������Ʈ �Լ�
	*/
	void ProcessMessage(void(*Update)());

	HWND GetWindowHandle()
	{
		return hWnd;
	}
};