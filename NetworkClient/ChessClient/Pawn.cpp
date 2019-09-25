#include "Pawn.h"
#include "BitMapManager.h"


Pawn::Pawn()
{
}


Pawn::~Pawn()
{
}

void Pawn::Init(CHESS_PIECE_COLOR pieceColor)
{
	this->pieceColor = pieceColor;
	pieceType = CHESS_PIECE_TYPE::PIECE_TYPE_PAWN;

	if (this->pieceColor == CHESS_PIECE_COLOR::PIECE_WHITE)
	{
		bitmap = BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::PAWN_W);
	}
	else if (this->pieceColor == CHESS_PIECE_COLOR::PIECE_BLACK)
	{
		bitmap = BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::PAWN_B);
	}
}

bool Pawn::CheckMove(POINT curPos, POINT targetPos)
{
	return false;
}

bool Pawn::CheckAttack(POINT curPos, ChessPiece & targetPiece, POINT targetPos)
{
	return false;
}
