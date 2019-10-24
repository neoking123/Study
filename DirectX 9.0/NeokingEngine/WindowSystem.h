#pragma once
#include <Windows.h>
#include "System.h"

class GraphicSystem;

/**
@brief 윈도우 시스템 클래스
@details WinMain 내부를 랩핑한 클래스
@details 윈도우를 생성하고 초기화한다
@details 윈도우의 메세지를 처리한다
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
	@brief 윈도우 초기화
	@details 윈도우 클래스 등록 작업
	@param HINSTANCE hInstance WinMain에 전달되는 첫 번째 인자값
	@param char* windowName 윈도우 이름
	*/
	void Init(HINSTANCE hInstance, const char* windowName);

	/**
	@brief 메인 윈도우 생성
	@details 메인 윈도우를 생성한다
	*/
	void InitWindow();

	/**
	@brief 메세지 처리
	@details 윈도우 메세지를 처리한다
	@details 게임 프레임 워크의 업데이트 함수를 파라미터로 받아
	@details 메세지 루프가 비었을 때 처리한다
	@param void(*Update)() 게임 프레임워크의 업데이트 함수
	*/
	void ProcessMessage(void(*Update)());

	HWND GetWindowHandle()
	{
		return hWnd;
	}
};