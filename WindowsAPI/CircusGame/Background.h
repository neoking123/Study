#pragma once
#include <Windows.h>
#include <vector>
using namespace std;

class Sprite;
class Camera;

class Background
{
private:
	vector<Sprite> BackgroundObjects;

	void DrawMiterCount(HDC gameDC, int miter, int x, int y);

public:
	Background();
	~Background();
	void Init();
	void Update(HDC gameDC, Camera& camera);
};

