#pragma once
#include <Windows.h>
#include <vector>
using namespace std;

class BitMap;
class GameObject;

/**
* @brief ��Ʈ���� ����ϰ� �ִϸ��̼��� ó���ϴ� ������Ʈ Ŭ����
* @details �������� ��Ʈ�� ��ü�� ���ͷ� �����Ͽ� �ִϸ��̼� ó���� �� �� �ִ�
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

