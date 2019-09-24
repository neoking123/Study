#pragma once
#include "ChessPiece.h"

class King : public ChessPiece
{
public:
	King();
	~King();
	void Init(CHESSPIECE_COLOR pieceColor);
	virtual void Moveto(int x, int y, int targetX, int targetY) override;
};

