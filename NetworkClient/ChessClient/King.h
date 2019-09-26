#pragma once
#include "ChessPiece.h"

class King : public ChessPiece
{
public:
	King();
	~King();
	void Init(CHESS_PIECE_COLOR pieceColor);
	virtual bool CheckMove(POINT curPos, POINT targetPos) override;
	virtual bool CheckAttack(POINT curPos, ChessPiece& targetPiece, POINT targetPos) override;
	virtual void DrawMovablePos(HDC hdc, POINT curPos) override;
};

