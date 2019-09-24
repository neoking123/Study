#include "Rook.h"
#include "BitMapManager.h"


Rook::Rook()
{
}


Rook::~Rook()
{
}

void Rook::Init(CHESSPIECE_COLOR pieceColor)
{
	this->pieceColor = pieceColor;
	pieceType = CHESS_PIECE_TYPE::PIECE_TYPE_KING;

	if (this->pieceColor == CHESSPIECE_COLOR::PIECE_WHITE)
	{
		bitmap = BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::ROOK_W);
	}
	else if (this->pieceColor == CHESSPIECE_COLOR::PIECE_BLACK)
	{
		bitmap = BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::ROOK_B);
	}
}

void Rook::Moveto(int x, int y, int targetX, int targetY)
{
}
