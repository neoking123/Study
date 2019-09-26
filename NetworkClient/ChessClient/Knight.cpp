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
	if ((abs(targetPos.x - curPos.x) == 2 && abs(targetPos.y - curPos.y) == 1)
		|| (abs(targetPos.x - curPos.x) == 1 && abs(targetPos.y - curPos.y) == 2))
	{
		return true;
	}
	else
		return false;
}

bool Knight::CheckAttack(POINT curPos, ChessPiece & targetPiece, POINT targetPos)
{
	if ((abs(targetPos.x - curPos.x) == 2 && abs(targetPos.y - curPos.y) == 1 && targetPiece.GetColor() != pieceColor)
		|| (abs(targetPos.x - curPos.x) == 1 && abs(targetPos.y - curPos.y) == 2 && targetPiece.GetColor() != pieceColor))
	{
		return true;
	}
	else
		return false;
}

void Knight::DrawMovablePos(HDC hdc, POINT curPos)
{
	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::MOVABLE_POS)->Draw(hdc, curPos.x * CHESS_PIECE_SIZE + 24, curPos.y * CHESS_PIECE_SIZE + 24);

}

