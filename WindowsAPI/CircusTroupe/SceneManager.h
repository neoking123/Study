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
	int objectsNum;
	SIZE sceneSize;
	HDC hdcScene;

	void DrawBackground(HDC hdc);
	

public:
	~SceneManager();
	
	void Init(SIZE size);
	void DrawScene(HDC hdc);
	void AddSceneObject(SceneObject* newObj, POINT pos = { 0, 0 }, int spriteNum = 0);
	void Relese();
	int GetObjectsNum();

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

