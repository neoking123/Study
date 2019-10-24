#include <Windows.h>
#include "CoreEngine.h"
//using namespace Object3D;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	// 엔진 초기화
	CoreEngine::GetInstance()->Init(hInstance);

	// 게임 초기화 부분 작성

	CUSTOMVERTEX vertices[] =
	{
		{ { -1 , 1 , 1 }, 0xffff0000 } ,
		{ { 1 , 1 , 1 }, 0xff00ff00 } ,
		{ { 1 ,   1 ,  -1 }, 0xff0000ff },
		{ { -1 , 1 ,  -1 }, 0xffffff00 },

		{ { -1 , -1 , 1 }, 0xff00ffff } ,
		{ { 1 , -1 , 1 }, 0xffff00ff } ,
		{ { 1 , -1 ,  -1 }, 0xff000000 },
		{ { -1 , -1 ,  -1 }, 0xffffffff },
	};

	CUSTOMINDEX indeices[] =
	{
		{0,1,2},{0,2,3},//윗면
		{4,6,5},{4,7,6},//아랫면
		{0,3,7},{0,7,4},//왼면
		{1,5,6},{1,6,2},//오른면
		{3,2,6},{3,6,7},//앞면
		{0,4,5},{0,5,1}//뒷면
	};

	Object3D::Polygon p;
	p.InitVB(vertices);
	p.InitIB(indeices);

	// 게임 루프
	CoreEngine::GetInstance()->Update(nullptr);

	// 엔진 해제
	CoreEngine::GetInstance()->Release();
}