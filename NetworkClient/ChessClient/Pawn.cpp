#include "Pawn.h"
#include "BitMapManager.h"


Pawn::Pawn()
{
}


Pawn::~Pawn()
{
}

void Pawn::Init(CHESSPIECE_COLOR pieceColor)
{
	this->pieceColor = pieceColor;
	pieceType = CHESS_PIECE_TYPE::PIECE_TYPE_KING;

	if (this->pieceColor == CHESSPIECE_COLOR::PIECE_WHITE)
	{
		bitmap = BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::PAWN_W);
	}
	else if (this->pieceColor == CHESSPIECE_COLOR::PIECE_BLACK)
	{
		bitmap = BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::PAWN_B);
	}
}

void Pawn::Moveto(int x, int y, int targetX, int targetY)
{
}
