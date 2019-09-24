#include "Bishop.h"
#include "BitMapManager.h"


Bishop::Bishop()
{

}


Bishop::~Bishop()
{
	
}

void Bishop::Init(CHESSPIECE_COLOR pieceColor)
{
	this->pieceColor = pieceColor;
	pieceType = CHESS_PIECE_TYPE::PIECE_TYPE_KING;

	if (this->pieceColor == CHESSPIECE_COLOR::PIECE_WHITE)
	{
		bitmap = BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::BISHOP_W);
	}
	else if (this->pieceColor == CHESSPIECE_COLOR::PIECE_BLACK)
	{
		bitmap = BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::BISHOP_B);
	}
}

void Bishop::Moveto(int x, int y, int targetX, int targetY)
{
}
