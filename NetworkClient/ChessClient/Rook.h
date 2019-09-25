#pragma once
#include "ChessPiece.h"

class Rook : public ChessPiece
{
public:
	Rook();
	~Rook();
	void Init(CHESS_PIECE_COLOR pieceColor);
	virtual bool CheckMove(POINT curPos, POINT targetPos) override;
	virtual bool CheckAttack(POINT curPos, ChessPiece& targetPiece, POINT targetPos) override;
};

