#include "Rook.h"
#include "BitMapManager.h"
#include "ChessBoard.h"

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
	if (targetPos.x == curPos.x)
	{
		int i, j;
		if (targetPos.y > curPos.y)
		{
			i = curPos.y + 1;
			j = targetPos.y;
		}
		else
		{
			i = targetPos.y + 1;
			j = curPos.y;
		}

		for (; i < j; i++)
		{
			if (ChessBoard::GetInstance()->IsExist({ curPos.x, i }))
			{
				return false;
			}
		}
		return true;
	}
	else if (targetPos.y == curPos.y)
	{
		int i, j;
		if (targetPos.x > curPos.x)
		{
			i = curPos.x + 1;
			j = targetPos.x;
		}
		else
		{
			i = targetPos.x + 1;
			j = curPos.x;
		}

		for (; i < j; i++)
		{
			if (ChessBoard::GetInstance()->IsExist({ i, curPos.y }))
			{
				return false;
			}
		}
		return true;
	}
	else
	{
		return false;
	}
}

bool Rook::CheckAttack(POINT curPos, ChessPiece & targetPiece, POINT targetPos)
{
	if (targetPos.x == curPos.x)
	{
		int i, j;
		if (targetPos.y > curPos.y)
		{
			i = curPos.y + 1;
			j = targetPos.y;
		}
		else
		{
			i = targetPos.y + 1;
			j = curPos.y;
		}

		for (; i < j; i++)
		{
			if (ChessBoard::GetInstance()->IsExist({ curPos.x, i }))
			{
				return false;
			}
		}

		if (targetPiece.GetColor() != pieceColor)
		{
			return true;
		}
		else
			return false;
		
	}
	else if (targetPos.y == curPos.y)
	{
		int i, j;
		if (targetPos.x > curPos.x)
		{
			i = curPos.x + 1;
			j = targetPos.x;
		}
		else
		{
			i = targetPos.x + 1;
			j = curPos.x;
		}

		for (; i < j; i++)
		{
			if (ChessBoard::GetInstance()->IsExist({ i, curPos.y }))
			{
				return false;
			}
		}

		if (targetPiece.GetColor() != pieceColor)
		{
			return true;
		}
		else
			return false;
	}
	else
	{
		return false;
	}
}
