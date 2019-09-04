#include "SceneManager.h"
#include "SceneObject.h"

SceneManager* SceneManager::pInstance = nullptr;

SceneManager::SceneManager()
{
}


void SceneManager::DrawBackground(HDC hdc)
{

}

SceneManager::~SceneManager()
{
}

void SceneManager::Init(SIZE size)
{
	sceneSize = size;
	objectsNum = 0;

}

void SceneManager::DrawScene(HDC hdc)
{
	DrawBackground(hdcScene);

	if (!sceneObjects.empty())
	{
		for (auto iter = sceneObjects.begin(); iter != sceneObjects.end(); iter++)
		{
			(*iter)->Draw(hdcScene);
		}
	}

	BitBlt(hdc, 0, 0, 1024, 768, hdcScene, 0, 0, SRCCOPY);
}

void SceneManager::AddSceneObject(SceneObject* newObj, POINT pos, int spriteNum)
{
	newObj->Init(objectsNum++, pos, spriteNum);
	sceneObjects.push_back(newObj);
}

void SceneManager::Relese()
{
}

int SceneManager::GetObjectsNum()
{
	return objectsNum;
}
