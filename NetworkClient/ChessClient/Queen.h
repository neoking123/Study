#pragma once
#include "ChessPiece.h"

class Queen : public ChessPiece
{
public:
	Queen();
	~Queen();
	void Init(CHESSPIECE_COLOR pieceColor);
	virtual void Moveto(int x, int y, int targetX, int targetY) override;
};

