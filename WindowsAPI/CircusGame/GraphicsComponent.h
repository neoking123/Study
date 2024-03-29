#pragma once
#include <Windows.h>
#include <vector>
using namespace std;

class BitMap;
class GameObject;
class Character;
class FireRing;
class FirePot;

class GraphicsComponent
{
private:
	vector<BitMap*> Sprites;
	DWORD lastChangeTime;

public:
	void Update(GameObject& gameObject, HDC hdc);
	void AddSprite(BitMap& bitmap);
	void UpdateAnim(Character& character);
	void UpdateAnim(FireRing& fireRing);
	void UpdateAnim(FirePot& firePot);
	void DrawBack(FireRing& fireRing, HDC hdc);
};

