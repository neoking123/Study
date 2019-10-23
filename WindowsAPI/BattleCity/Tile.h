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
* @brief 타일 클래스
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
	* @brief 위치 설정 함수
	* @details x, y의 위치로 설정한다
	* @param int x x 좌표
	* @param int y y 좌표
	*/
	virtual void SetPosition(int x, int y) override;

	/**
	* @brief 애니메이션 상태 설정 함수
	* @details 새로운 애니메이션 상태로 설정한다
	* @param TILE_ANIM_STATE newState 애니메이션 상태
	*/
	void SetAnimState(TILE_ANIM_STATE newState);
};

