#pragma once
#include "InputComponent.h"

/**
* @brief �÷��̾� �Է� Ŭ����
* @author Dayeol Hyeon
*/

class PlayerInputComponent : public InputComponent
{
public:
	virtual void Update(GameObject& gameObject) override;
};

