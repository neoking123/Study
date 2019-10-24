#pragma once
#include <Windows.h>
#include <vector>
#include "..\..\Common\NetworkManager.h"
using namespace std;

/**
* @brief ����ġ�� �׸� �����͸� �����ϴ� Ŭ����
* @details ���콺�� �׷��� ���� �ȼ����� ���ͷ� �����Ѵ�
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

