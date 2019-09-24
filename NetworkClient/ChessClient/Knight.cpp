#include "Knight.h"
#include "BitMapManager.h"


Knight::Knight()
{
}


Knight::~Knight()
{
}

void Knight::Init(CHESSPIECE_COLOR pieceColor)
{
	this->pieceColor = pieceColor;
	pieceType = CHESS_PIECE_TYPE::PIECE_TYPE_KING;

	if (this->pieceColor == CHESSPIECE_COLOR::PIECE_WHITE)
	{
		bitmap = BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::KNIGHT_W);
	}
	else if (this->pieceColor == CHESSPIECE_COLOR::PIECE_BLACK)
	{
		bitmap = BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::KNIGHT_B);
	}
}

void Knight::Moveto(int x, int y, int targetX, int targetY)
{
}
