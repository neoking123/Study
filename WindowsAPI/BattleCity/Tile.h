#pragma once
#include "GameObject.h"
#include "PhysicsComponent.h"

#define QUARTER 16

enum TILE_ANIM_STATE
{
	EGLE_IDLE,
	EGLE_FLAG,
	EGLE_BOMB_0,
	EGLE_BOMB_1,
	EGLE_BOMB_2,
	EGLE_BOMB_3,
	EGLE_BOMB_4,
	EGLE_BOMB_START,
};

/**
* @brief Ÿ�� Ŭ����
* @author Dayeol Hyeon
*/

class Tile : public GameObject
{
public:
	PhysicsComponent phsics1;
	PhysicsComponent phsics2;
	PhysicsComponent phsics3;
	PhysicsComponent phsics4;
	TILE_ANIM_STATE animState;
	int tileNum;

public:
	Tile();
	~Tile();

	virtual void Init(InputComponent* input, int x = 0, int y = 0, string tag = "") override;
	void Init(InputComponent* input, int x = 0, int y = 0, string tag = "", int tileNum = 47);
	virtual void Update(float elapseTime) override;
	virtual void Render(HDC hdc) override;

	/**
	* @brief ��ġ ���� �Լ�
	* @details x, y�� ��ġ�� �����Ѵ�
	* @param int x x ��ǥ
	* @param int y y ��ǥ
	*/
	virtual void SetPosition(int x, int y) override;

	/**
	* @brief �ִϸ��̼� ���� ���� �Լ�
	* @details ���ο� �ִϸ��̼� ���·� �����Ѵ�
	* @param TILE_ANIM_STATE newState �ִϸ��̼� ����
	*/
	void SetAnimState(TILE_ANIM_STATE newState);
};

