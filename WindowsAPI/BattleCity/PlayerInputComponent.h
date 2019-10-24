#pragma once
#include "InputComponent.h"

/**
* @brief 플레이어 입력 클래스
* @author Dayeol Hyeon
*/

class PlayerInputComponent : public InputComponent
{
public:
	virtual void Update(GameObject& gameObject) override;
};

