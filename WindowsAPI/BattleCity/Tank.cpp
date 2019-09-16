#include "Tank.h"
#include "BitMapManager.h"
#include "InputComponent.h"
#include "Missile.h"
#include "Macro.h"

Tank::Tank()
{
}

Tank::~Tank()
{
}

void Tank::Init(InputComponent* input, int x, int y, string tag)
{
	this->input = input;
	transform.position.x = x;
	transform.position.y = y;
	this->tag = tag;
	speed = 2;
	fireElapseTime = 0.0f;
	fireDelayTime = 0.1f;
	isCollide = false;
	isDead = false;
	isEndAnim = false;
	direction = DIRECTION::STOP;
	fireDirection = DIRECTION::UP;
	animState = TANK_ANIM_STATE::UP_00;

	graphics.AddSprite(*BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::TANK_UP_0));
	for (int i = BITMAP_RES::TANK_DOWN_0; i <= TANK_UP_1; i++)
	{
		graphics.AddSprite(*BitMapManager::GetInstance()->GetBitMap(i));
	}

	for (int i = BITMAP_RES::EXPLOSION_0; i <= EXPLOSION_4; i++)
	{
		graphics.AddSprite(*BitMapManager::GetInstance()->GetBitMap(i));
	}


	phsics.SetColliderBox(*this, SIZE{ 32, 32 }, 2, 2, -2, -2);

	Missile* newMissile = new Missile();
	newMissile->Init(nullptr, 0, 0, "missile_player");
	missilePool.push_back(newMissile);

	newMissile = new Missile();
	newMissile->Init(nullptr, 0, 0, "missile_player");
	missilePool.push_back(newMissile);
}

void Tank::Update(float elapseTime)
{
	if (!isDead)
	{
		input->Update(*this);
		phsics.Update(*this, elapseTime);
	}
	
	if(!isEndAnim)
		graphics.UpdateAnim(*this, elapseTime);

	for (auto iter = missilePool.begin(); iter != missilePool.end(); iter++)
	{
		if ((*iter)->isFired)
		{
			(*iter)->Update(elapseTime);
		}
	}

	fireElapseTime += elapseTime;
}

void Tank::Render(HDC hdc)
{
	if (!isDead)
	{
		//phsics.RenderColliderBox(hdc);
	}

	if (!isEndAnim)
		graphics.Render(*this, hdc);

	for (auto iter = missilePool.begin(); iter != missilePool.end(); iter++)
	{
		if ((*iter)->isFired)
		{
			(*iter)->Render(hdc);
		}
	}
}

void Tank::SetPosition(int x, int y)
{
	transform.position.x = x;
	transform.position.y = y;
}

void Tank::SetDirection(DIRECTION newDirection)
{
	direction = newDirection;
}

void Tank::SetSpeed(int newSpeed)
{
	speed = newSpeed;
}

void Tank::Release()
{
	for (auto iter = missilePool.begin(); iter != missilePool.end(); iter++)
	{
		SAFE_DELETE(*iter);
	}
}

void Tank::SetAnimState(TANK_ANIM_STATE newAnimState)
{
	animState = newAnimState;
}

void Tank::Fire()
{
	if (fireElapseTime < fireDelayTime)
		return;

	auto iter = missilePool.begin();
	for (; iter != missilePool.end(); iter++)
	{
		if (!(*iter)->isFired)
		{
			(*iter)->isFired = true;
			(*iter)->SetDirection(fireDirection);
			(*iter)->SetFirePosition(transform.position.x, transform.position.y);
			fireElapseTime = 0.0f;
			return;
		}
	}
}

void Tank::Die()
{
	isDead = true;
	phsics.SetColliderBox(*this, SIZE{ 0, 0 });
	SetDirection(DIRECTION::STOP);
	SetAnimState(TANK_ANIM_STATE::EXPLOSION_START);
}

vector<Missile*> Tank::GetMissiles()
{
	return missilePool;
}
