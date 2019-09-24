#pragma once
#include "ChessPiece.h"

class Knight : public ChessPiece
{
public:
	Knight();
	~Knight();
	void Init(CHESSPIECE_COLOR pieceColor);
	virtual void Moveto(int x, int y, int targetX, int targetY) override;
};

