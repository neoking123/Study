#include "Sprite.h"
#include "BitMap.h"

Sprite::Sprite()
{
}


Sprite::~Sprite()
{
}

void Sprite::Init(BitMap * bitmap)
{
	this->bitmap = bitmap;
}

void Sprite::Draw(HDC gameDC, int x, int y)
{
	bitmap->Draw(gameDC, x, y);
}
