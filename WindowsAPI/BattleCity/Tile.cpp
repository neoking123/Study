#include "Tile.h"

Tile::Tile()
{
}


Tile::~Tile()
{
}

void Tile::Init(InputComponent * input, int x, int y, string tag)
{
	input = nullptr;
	transform.position.x = x;
	transform.position.y = y;
	this->tag = tag;

	phsics1.SetColliderBox(*this, SIZE{ 16,16 });
	phsics2.SetColliderBox(*this, SIZE{ 16,16 }, 16, 0, 16, 0);
	phsics3.SetColliderBox(*this, SIZE{ 16,16 }, 0, 16, 0, 16);
	phsics4.SetColliderBox(*this, SIZE{ 16,16 }, 16, 16, 16, 16);
}

void Tile::Init(InputComponent * input, int x, int y, string tag, int tileNum)
{
	input = nullptr;
	transform.position.x = x;
	transform.position.y = y;
	this->tag = tag;

	phsics1.SetColliderBox(*this, SIZE{ 16,16 });
	phsics2.SetColliderBox(*this, SIZE{ 16,16 }, 16, 0, 16, 0);
	phsics3.SetColliderBox(*this, SIZE{ 16,16 }, 0, 16, 0, 16);
	phsics4.SetColliderBox(*this, SIZE{ 16,16 }, 16, 16, 16, 16);

	this->tileNum = tileNum;
}

void Tile::Update(float elapseTime)
{
}

void Tile::Render(HDC hdc)
{
}

void Tile::SetPosition(int x, int y)
{
}

void Tile::SetDirection(DIRECTION newDirection)
{
}
