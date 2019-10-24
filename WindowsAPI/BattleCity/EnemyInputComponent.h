#pragma once
#include "InputComponent.h"

/**
* @brief �� ��ũ �Է� Ŭ����
* @details ������ AI�� �ۼ��Ǿ� �� ��ũ�� �������� �����Ѵ�
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

