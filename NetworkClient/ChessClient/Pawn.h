#pragma once
#include "ChessPiece.h"

class Pawn : public ChessPiece
{
public:
	Pawn();
	~Pawn();
	void Init(CHESS_PIECE_COLOR pieceColor);
	virtual bool CheckMove(POINT curPos, POINT targetPos) override;
	virtual bool CheckAttack(POINT curPos, ChessPiece& targetPiece, POINT targetPos) override;
};

