#pragma once
#include <Windows.h>
#include <vector>
using namespace std;

class BitMap;
class GameObject;

class GraphicsComponent
{
private:
	vector<BitMap*> Sprites;
	DWORD lastChangeTime;

public:
	void Update(GameObject& gameObject, HDC hdc);
	void AddSprite(BitMap& bitmap);
	void UpdateAnim(GameObject& gameObject);
};

