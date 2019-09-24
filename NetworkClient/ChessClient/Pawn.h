#pragma once
#include "ChessPiece.h"

class Pawn : public ChessPiece
{
public:
	Pawn();
	~Pawn();
	void Init(CHESSPIECE_COLOR pieceColor);
	virtual void Moveto(int x, int y, int targetX, int targetY) override;
};

