#pragma once
#include <Windows.h>
#include <vector>
using namespace std;

class BitMap;
class GameObject;

/**
* @brief 비트맵을 출력하고 애니메이션을 처리하는 컴포넌트 클래스
* @details 여러장의 비트맵 객체를 벡터로 관리하여 애니메이션 처리를 할 수 있다
* @author Dayeol Hyeon
*/

class GraphicsComponent
{
private:
	vector<BitMap*> Sprites;
	float bombTime = 0.0f;

public:
	void Render(GameObject& gameObject, HDC hdc);
	void AddSprite(BitMap& bitmap);
	void UpdateAnim(GameObject& gameObject, float elapseTime);
};

