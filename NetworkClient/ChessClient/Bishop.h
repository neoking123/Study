#pragma once
#include "ChessPiece.h"

class Bishop : public ChessPiece
{
public:
	Bishop();
	~Bishop();
	void Init(CHESSPIECE_COLOR pieceColor);
	virtual void Moveto(int x, int y, int targetX, int targetY) override;
};

