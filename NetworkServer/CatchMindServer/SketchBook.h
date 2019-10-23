#pragma once
#include <Windows.h>
#include <vector>
#include "..\..\Common\NetworkManager.h"
using namespace std;

/**
* @brief 스케치북 그림 데이터를 관리하는 클래스
* @details 마우스로 그려진 여러 픽셀들을 벡터로 관리한다
* @author Dayeol Hyeon
*/

class SketchBook
{
private:
	static SketchBook* instance;
	vector<BRUSH_DATA*> mouseTrack;

	SketchBook();

public:
	~SketchBook();

	void DrawToSketchBook(BRUSH_DATA* brushData);

	inline static SketchBook* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new SketchBook();
		}
		return instance;
	}

	inline static void FreeInstance()
	{
		SAFE_DELETE(instance);
	}
};

