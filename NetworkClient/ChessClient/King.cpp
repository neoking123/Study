#include "King.h"
#include "BitMapManager.h"

King::King()
{
}


King::~King()
{
}

void King::Init(CHESS_PIECE_COLOR pieceColor)
{
	this->pieceColor = pieceColor;
	pieceType = CHESS_PIECE_TYPE::PIECE_TYPE_KING;

	if (this->pieceColor == CHESS_PIECE_COLOR::PIECE_WHITE)
	{
		bitmap = BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::KING_W);
	}
	else if (this->pieceColor == CHESS_PIECE_COLOR::PIECE_BLACK)
	{
		bitmap = BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::KING_B);
	}
	
}

bool King::CheckMove(POINT curPos, POINT targetPos)
{
	if ((targetPos.x >= curPos.x - 1 && targetPos.x <= curPos.x + 1)
		|| (targetPos.y >= curPos.y - 1 && targetPos.y <= curPos.y + 1))
	{
		return true;
	}
	else
	{
		return false;
	}	
}

bool King::CheckAttack(POINT curPos, ChessPiece & targetPiece, POINT targetPos)
{
	if ((targetPos.x >= curPos.x - 1 && targetPos.x <= curPos.x + 1)
		|| (targetPos.y >= curPos.y - 1 && targetPos.y <= curPos.y + 1)
		&& targetPiece.GetColor() != pieceColor)
	{
		return true;
	}
	else
	{
		return false;
	}
}
