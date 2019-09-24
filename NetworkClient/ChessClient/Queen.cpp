#include "Queen.h"
#include "BitMapManager.h"

Queen::Queen()
{
}

Queen::~Queen()
{
}

void Queen::Init(CHESSPIECE_COLOR pieceColor)
{
	this->pieceColor = pieceColor;
	pieceType = CHESS_PIECE_TYPE::PIECE_TYPE_KING;

	if (this->pieceColor == CHESSPIECE_COLOR::PIECE_WHITE)
	{
		bitmap = BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::QUEEN_W);
	}
	else if (this->pieceColor == CHESSPIECE_COLOR::PIECE_BLACK)
	{
		bitmap = BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::QUEEN_B);
	}
}

void Queen::Moveto(int x, int y, int targetX, int targetY)
{
}
