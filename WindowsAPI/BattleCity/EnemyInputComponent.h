#pragma once
#include "InputComponent.h"

/**
* @brief 적 탱크 입력 클래스
* @details 간단한 AI로 작성되어 적 탱크의 움직임을 관리한다
* @author Dayeol Hyeon
*/

class EnemyInputComponent : public InputComponent
{
private:
	int directionChangeCount = 0;
	int randomDirectionChangeDelayCount = 0;
	int randomDirection = 4;

public:
	virtual void Update(GameObject& gameObject) override;
};

