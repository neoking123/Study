#pragma once
#include <Windows.h>

class GameObject;

/**
* @brief �̵�, �浹�� ó���ϴ� ������Ʈ Ŭ����
* @author Dayeol Hyeon
*/

class PhysicsComponent
{
private:
	RECT colliderBox;
	SIZE colliderSize;
	
	/**
	* @brief �̵� ó�� �Լ�
	* @details ���� ������Ʈ�� ������Ʈ�� ���� �������� �̵���Ų��
	* @param GameObject& gameObject �̵���ų ������Ʈ
	* @param float elapseTime ��� �ð�
	*/
	void Move(GameObject& gameObject, float elapseTime);

	/**
	* @brief ��� �浹 ó�� �Լ�
	* @details ����� �浹 ���θ� üũ�Ѵ�
	* @param GameObject& gameObject �̵���ų ������Ʈ
	*/
	bool CheckBlockCollision(GameObject& gameObject);

	/**
	* @brief ��ũ �浹 ó�� �Լ�
	* @details ��ũ�� �浹 ���θ� üũ�Ѵ�
	* @param GameObject& gameObject �̵���ų ������Ʈ
	*/
	bool CheckTankCollision(GameObject& gameObject);

	/**
	* @brief �̻��� �浹 ó�� �Լ�
	* @details �̻����� �浹 ���θ� üũ�Ѵ�
	* @param GameObject& gameObject �̵���ų ������Ʈ
	*/
	bool CheckMissileCollision(GameObject& gameObject);

public:
	int left;
	int top;
	int right;
	int bottom;

public:
	void Update(GameObject& gameObject, float elapseTime);
	void SetColliderBox(SIZE boxSize);
	void SetColliderBox(GameObject& gameObject, SIZE boxSize, int left = 0, int top = 0, int right = 0, int bottom = 0);
	RECT GetColliderBox();
	SIZE GetColliderSize();

	/**
	* @brief �浹 �ڽ� ��ġ ����ȭ �Լ�
	* @details �浹 �ڽ��� ��ġ�� ���� ������Ʈ�� ��ġ�� ����ȭ�Ѵ�
	* @param GameObject& gameObject ���� ������Ʈ
	*/
	void SyncClliderPos(GameObject& gameObject);

	/**
	* @brief �浹 �ڽ� ��� �Լ�
	* @details �浹 �ڽ��� ����Ѵ�
	* @param HDC hdc Device Context �ڵ�
	*/
	void RenderColliderBox(HDC hdc);
};

