#pragma once
#include <Windows.h>
#include <vector>
using namespace std;

class BitMap;

class SceneObject
{
private:

protected:
	vector<BitMap*> sprites;
	POINT position;
	bool isCharacter;

	void AddSprite(BitMap* bitmap);
	void SetSprite(int index);

public:
	SceneObject();
	~SceneObject();

	virtual void Init(POINT pos = { 0, 0 }, int spriteNum = 0);
	void Draw(HDC hdc);
	void DrawFixedPosition(HDC hdc, int x);
	bool IsCharacter();
	POINT GetPosition();
};

