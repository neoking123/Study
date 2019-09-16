#include "Tile.h"
#include "BitMapManager.h"

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

	phsics1.SetColliderBox(*this, SIZE{ QUARTER,QUARTER });
	phsics2.SetColliderBox(*this, SIZE{ QUARTER,QUARTER }, QUARTER, 0, QUARTER, 0);
	phsics3.SetColliderBox(*this, SIZE{ QUARTER,QUARTER }, 0, QUARTER, 0, QUARTER);
	phsics4.SetColliderBox(*this, SIZE{ QUARTER,QUARTER }, QUARTER, QUARTER, QUARTER, QUARTER);
}

void Tile::Init(InputComponent * input, int x, int y, string tag, int tileNum)
{
	input = nullptr;
	transform.position.x = x;
	transform.position.y = y;
	this->tag = tag;

	if (tileNum == BITMAP_RES::BLOCK_1 || tileNum == BITMAP_RES::BLOCK_9)
	{
		phsics1.SetColliderBox(*this, SIZE{ QUARTER,QUARTER });
		phsics2.SetColliderBox(*this, SIZE{ QUARTER,QUARTER }, QUARTER, 0, QUARTER, 0);
	}
	else if (tileNum == BITMAP_RES::BLOCK_2 || tileNum == BITMAP_RES::BLOCK_12)
	{
		phsics1.SetColliderBox(*this, SIZE{ QUARTER,QUARTER });
		phsics3.SetColliderBox(*this, SIZE{ QUARTER,QUARTER }, 0, QUARTER, 0, QUARTER);
	}
	else if (tileNum == BITMAP_RES::BLOCK_3 || tileNum == BITMAP_RES::BLOCK_11)
	{
		phsics3.SetColliderBox(*this, SIZE{ QUARTER,QUARTER }, 0, QUARTER, 0, QUARTER);
		phsics4.SetColliderBox(*this, SIZE{ QUARTER,QUARTER }, QUARTER, QUARTER, QUARTER, QUARTER);
	}
	else if (tileNum == BITMAP_RES::BLOCK_4 || tileNum == BITMAP_RES::BLOCK_10)
	{
		phsics2.SetColliderBox(*this, SIZE{ QUARTER,QUARTER }, QUARTER, 0, QUARTER, 0);
		phsics4.SetColliderBox(*this, SIZE{ QUARTER,QUARTER }, QUARTER, QUARTER, QUARTER, QUARTER);
	}
	else
	{
		phsics1.SetColliderBox(*this, SIZE{ QUARTER,QUARTER });
		phsics2.SetColliderBox(*this, SIZE{ QUARTER,QUARTER }, QUARTER, 0, QUARTER, 0);
		phsics3.SetColliderBox(*this, SIZE{ QUARTER,QUARTER }, 0, QUARTER, 0, QUARTER);
		phsics4.SetColliderBox(*this, SIZE{ QUARTER,QUARTER }, QUARTER, QUARTER, QUARTER, QUARTER);
	}

	this->tileNum = tileNum;
	graphics.AddSprite(*BitMapManager::GetInstance()->GetBitMap(this->tileNum));
}

void Tile::Update(float elapseTime)
{

}

void Tile::Render(HDC hdc)
{
	//phsics1.RenderColliderBox(hdc);
	//phsics2.RenderColliderBox(hdc);
	//phsics3.RenderColliderBox(hdc);
	//phsics4.RenderColliderBox(hdc);
	graphics.Render(*this, hdc);
}

void Tile::SetPosition(int x, int y)
{
}