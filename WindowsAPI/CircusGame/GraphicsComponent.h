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

public:
	void Update(GameObject& gameObject, HDC hdc);
	void AddSprite(BitMap& bitmap);
};

