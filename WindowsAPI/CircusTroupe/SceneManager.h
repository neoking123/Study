#pragma once
#include <Windows.h>
#include <vector>
using namespace std;

class SceneObject;

class SceneManager
{
private:
	SceneManager();

	static SceneManager* pInstance;

	vector<SceneObject*> sceneObjects;
	SIZE sceneSize;
	HDC SceneHDC;
	HBITMAP hBitMap;
	HBITMAP hOldBitMap;
	int drawPointX;
	int posX;
	int offset;

	void DrawBackground(HDC hdc);

public:
	~SceneManager();
	
	void Init(HDC hdc, SIZE size);
	void DrawScene(HDC hdc);
	void CheckBoundary(POINT pos);
	void AddSceneObject(SceneObject* newObj);
	void Relese();
	void Input(POINT pos);
	int GetObjectsNum();
	void SetOffset(POINT pos);

	static SceneManager* GetInstance()
	{
		if (pInstance == nullptr)
		{
			pInstance = new SceneManager();
		}
		return pInstance;
	}

	static void FreeInstance()
	{
		if (pInstance != nullptr)
		{
			delete pInstance;
			pInstance = nullptr;
		}
	}
};

