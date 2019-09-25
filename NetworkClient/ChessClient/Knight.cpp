#include "Knight.h"
#include "BitMapManager.h"


Knight::Knight()
{
}


Knight::~Knight()
{
}

void Knight::Init(CHESS_PIECE_COLOR pieceColor)
{
	this->pieceColor = pieceColor;
	pieceType = CHESS_PIECE_TYPE::PIECE_TYPE_KNIGHT;

	if (this->pieceColor == CHESS_PIECE_COLOR::PIECE_WHITE)
	{
		bitmap = BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::KNIGHT_W);
	}
	else if (this->pieceColor == CHESS_PIECE_COLOR::PIECE_BLACK)
	{
		bitmap = BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::KNIGHT_B);
	}
}

bool Knight::CheckMove(POINT curPos, POINT targetPos)
{
	return false;
}

bool Knight::CheckAttack(POINT curPos, ChessPiece & targetPiece, POINT targetPos)
{
	return false;
}

