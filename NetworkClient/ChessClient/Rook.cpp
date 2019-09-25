#include "Rook.h"
#include "BitMapManager.h"


Rook::Rook()
{
}


Rook::~Rook()
{
}

void Rook::Init(CHESS_PIECE_COLOR pieceColor)
{
	this->pieceColor = pieceColor;
	pieceType = CHESS_PIECE_TYPE::PIECE_TYPE_ROOK;

	if (this->pieceColor == CHESS_PIECE_COLOR::PIECE_WHITE)
	{
		bitmap = BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::ROOK_W);
	}
	else if (this->pieceColor == CHESS_PIECE_COLOR::PIECE_BLACK)
	{
		bitmap = BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::ROOK_B);
	}
}

bool Rook::CheckMove(POINT curPos, POINT targetPos)
{
	return false;
}

bool Rook::CheckAttack(POINT curPos, ChessPiece & targetPiece, POINT targetPos)
{
	return false;
}
