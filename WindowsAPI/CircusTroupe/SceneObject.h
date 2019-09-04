#pragma once
#include <Windows.h>
#include <vector>
using namespace std;

class BitMap;

class SceneObject
{
private:
	int index;

protected:
	vector<BitMap*> sprites;
	POINT position;

public:
	SceneObject();
	~SceneObject();

	virtual void Init(int index, POINT pos = { 0, 0 }, int spriteNum = 0);
	void Draw(HDC hdc);
	void AddSprite(BitMap* bitmap);
	POINT GetPosition();
};

