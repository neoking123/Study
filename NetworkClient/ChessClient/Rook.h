#pragma once
#include "ChessPiece.h"

class Rook : public ChessPiece
{
public:
	Rook();
	~Rook();
	void Init(CHESSPIECE_COLOR pieceColor);
	virtual void Moveto(int x, int y, int targetX, int targetY) override;
};

