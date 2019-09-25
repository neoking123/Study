#pragma once
#include "ChessPiece.h"

class Queen : public ChessPiece
{
public:
	Queen();
	~Queen();
	void Init(CHESS_PIECE_COLOR pieceColor);
	virtual bool CheckMove(POINT curPos, POINT targetPos) override;
	virtual bool CheckAttack(POINT curPos, ChessPiece& targetPiece, POINT targetPos) override;
};

