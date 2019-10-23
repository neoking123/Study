#pragma once
#include <Windows.h>

class GameObject;

/**
* @brief 이동, 충돌을 처리하는 컴포넌트 클래스
* @author Dayeol Hyeon
*/

class PhysicsComponent
{
private:
	RECT colliderBox;
	SIZE colliderSize;
	
	/**
	* @brief 이동 처리 함수
	* @details 게임 오브젝트를 오브젝트가 가진 방향으로 이동시킨다
	* @param GameObject& gameObject 이동시킬 오브젝트
	* @param float elapseTime 경과 시간
	*/
	void Move(GameObject& gameObject, float elapseTime);

	/**
	* @brief 블록 충돌 처리 함수
	* @details 블록의 충돌 여부를 체크한다
	* @param GameObject& gameObject 이동시킬 오브젝트
	*/
	bool CheckBlockCollision(GameObject& gameObject);

	/**
	* @brief 탱크 충돌 처리 함수
	* @details 탱크의 충돌 여부를 체크한다
	* @param GameObject& gameObject 이동시킬 오브젝트
	*/
	bool CheckTankCollision(GameObject& gameObject);

	/**
	* @brief 미사일 충돌 처리 함수
	* @details 미사일의 충돌 여부를 체크한다
	* @param GameObject& gameObject 이동시킬 오브젝트
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
	* @brief 충돌 박스 위치 동기화 함수
	* @details 충돌 박스의 위치를 게임 오브젝트의 위치와 동기화한다
	* @param GameObject& gameObject 게임 오브젝트
	*/
	void SyncClliderPos(GameObject& gameObject);

	/**
	* @brief 충돌 박스 출력 함수
	* @details 충돌 박스를 출력한다
	* @param HDC hdc Device Context 핸들
	*/
	void RenderColliderBox(HDC hdc);
};

