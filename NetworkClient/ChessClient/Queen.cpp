#include "Queen.h"
#include "BitMapManager.h"

Queen::Queen()
{
}

Queen::~Queen()
{
}

void Queen::Init(CHESS_PIECE_COLOR pieceColor)
{
	this->pieceColor = pieceColor;
	pieceType = CHESS_PIECE_TYPE::PIECE_TYPE_QUEEN;

	if (this->pieceColor == CHESS_PIECE_COLOR::PIECE_WHITE)
	{
		bitmap = BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::QUEEN_W);
	}
	else if (this->pieceColor == CHESS_PIECE_COLOR::PIECE_BLACK)
	{
		bitmap = BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::QUEEN_B);
	}
}

bool Queen::CheckMove(POINT curPos, POINT targetPos)
{
	return false;
}

bool Queen::CheckAttack(POINT curPos, ChessPiece & targetPiece, POINT targetPos)
{
	return false;
}
