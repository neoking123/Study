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
* @brief �÷��̾� ��ũ Ŭ����
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
	* @brief ��ũ ��Ȱ �Լ�
	* @details ���� ������ �������� �÷��̾� ��ũ�� ��Ȱ��Ų��
	* @param float elapseTime ��� �ð�
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
	* @brief ���� ���� �Լ�
	* @details ���ο� �������� �����Ѵ�
	* @param DIRECTION newDirection ����
	*/
	void SetDirection(DIRECTION newDirection);

	/**
	* @brief �ӵ� ���� �Լ�
	* @details ���ο� �ӵ��� �����Ѵ�
	* @param int newSpeed �ӵ�
	*/
	void SetSpeed(int newSpeed);
	void Release();
	void SetAnimState(TANK_ANIM_STATE newAnimState);

	/**
	* @brief �̻��� �߻� �Լ�
	* @details �̻����� �߻��Ѵ�
	* @details �̻����� ������Ʈ Ǯ��(Object Pooling)�Ͽ� �����Ѵ�
	* @details �̸� �ʿ��� ��ŭ ������ �ı����� �ʰ� ��Ȱ���Ѵ�
	*/
	void Fire();

	/**
	* @brief ���� ó�� �Լ�
	* @details �÷��̾ ���� ó���Ѵ�
	*/
	void Die();

	/**
	* @brief �̻���Ǯ ���� �Լ�
	* @details �̻��� Ǯ�� �����Ѵ�
	* @return missilePool
	*/
	vector<Missile*> GetMissiles();
};

