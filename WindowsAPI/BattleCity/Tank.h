#pragma once
#include "GameObject.h"
#include "PhysicsComponent.h"

enum TANK_ANIM_STATE
{
	DOWN_00,
	DOWN_01,
	LEFT_00,
	LEFT_01,
	RIGHT_00,
	RIGHT_01,
	UP_00,
	UP_01,
	BOMB_00,
	BOMB_01,
	BOMB_02,
	BOMB_03,
	BOMB_04,
	EXPLOSION_START
};

class Missile;

/**
* @brief 플레이어 탱크 클래스
* @author Dayeol Hyeon
*/

class Tank : public GameObject
{
protected:
	vector<Missile*> missilePool;
	float fireElapseTime;
	float fireDelayTime;
	float revivalElapseTime;
	float revivalDelayTime;

	/**
	* @brief 탱크 부활 함수
	* @details 일정 딜레이 간격으로 플레이어 탱크를 부활시킨다
	* @param float elapseTime 경과 시간
	*/
	void Revive(float elapseTime);

public:
	Tank();
	~Tank();

	int speed;
	bool isCollide;
	bool isDead;
	bool isEndAnim;
	bool isEndBomb;
	PhysicsComponent phsics;
	DIRECTION direction;
	TANK_ANIM_STATE animState;
	DIRECTION fireDirection;

	virtual void Init(InputComponent* input, int x, int y, string tag) override;
	virtual void Update(float elapseTime) override;
	virtual void Render(HDC hdc) override;
	virtual void SetPosition(int x, int y) override;

	/**
	* @brief 방향 설정 함수
	* @details 새로운 방향으로 설정한다
	* @param DIRECTION newDirection 방향
	*/
	void SetDirection(DIRECTION newDirection);

	/**
	* @brief 속도 설정 함수
	* @details 새로운 속도로 설정한다
	* @param int newSpeed 속도
	*/
	void SetSpeed(int newSpeed);
	void Release();
	void SetAnimState(TANK_ANIM_STATE newAnimState);

	/**
	* @brief 미사일 발사 함수
	* @details 미사일을 발사한다
	* @details 미사일은 오브젝트 풀링(Object Pooling)하여 관리한다
	* @details 미리 필요한 만큼 생성후 파괴하지 않고 재활용한다
	*/
	void Fire();

	/**
	* @brief 죽음 처리 함수
	* @details 플레이어를 죽음 처리한다
	*/
	void Die();

	/**
	* @brief 미사일풀 리턴 함수
	* @details 미사일 풀을 리턴한다
	* @return missilePool
	*/
	vector<Missile*> GetMissiles();
};

