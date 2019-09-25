#include "Bishop.h"
#include "BitMapManager.h"


Bishop::Bishop()
{

}


Bishop::~Bishop()
{
	
}

void Bishop::Init(CHESS_PIECE_COLOR pieceColor)
{
	this->pieceColor = pieceColor;
	pieceType = CHESS_PIECE_TYPE::PIECE_TYPE_BISHOP;

	if (this->pieceColor == CHESS_PIECE_COLOR::PIECE_WHITE)
	{
		bitmap = BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::BISHOP_W);
	}
	else if (this->pieceColor == CHESS_PIECE_COLOR::PIECE_BLACK)
	{
		bitmap = BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::BISHOP_B);
	}
}

bool Bishop::CheckMove(POINT curPos, POINT targetPos)
{
	return false;
}

bool Bishop::CheckAttack(POINT curPos, ChessPiece & targetPiece, POINT targetPos)
{
	return false;
}
