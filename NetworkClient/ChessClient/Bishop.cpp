#include "Bishop.h"
#include "BitMapManager.h"
#include "ChessBoard.h"

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
	if (abs(targetPos.x - curPos.x) == abs(targetPos.y - curPos.y))
	{
		int i, j, k;
		if (targetPos.x > curPos.x && targetPos.y > curPos.y)
		{
			i = curPos.x + 1;
			j = targetPos.x;
			k = curPos.y + 1;

			for (; i < j; i++, k++)
			{
				if (ChessBoard::GetInstance()->IsExist({ i, k }))
				{
					return false;
				}
			}
		}
		else if (targetPos.x > curPos.x && targetPos.y < curPos.y)
		{
			i = curPos.x + 1;
			j = targetPos.x;
			k = curPos.y - 1;

			for (; i < j; i++, k--)
			{
				if (ChessBoard::GetInstance()->IsExist({ i, k }))
				{
					return false;
				}
			}
		}
		else if (targetPos.x < curPos.x && targetPos.y > curPos.y)
		{
			i = targetPos.x + 1;
			j = curPos.x;
			k = targetPos.y - 1;

			for (; i < j; i++, k--)
			{
				if (ChessBoard::GetInstance()->IsExist({ i, k }))
				{
					return false;
				}
			}
		}
		else if (targetPos.x < curPos.x && targetPos.y < curPos.y)
		{
			i = targetPos.x + 1;
			j = curPos.x;
			k = targetPos.y + 1;

			for (; i < j; i++, k++)
			{
				if (ChessBoard::GetInstance()->IsExist({ i, k }))
				{
					return false;
				}
			}
		}

		return true;
	}
	else
	{
	return false;
	}
}

bool Bishop::CheckAttack(POINT curPos, ChessPiece & targetPiece, POINT targetPos)
{
	if (abs(targetPos.x - curPos.x) == abs(targetPos.y - curPos.y))
	{
		int i, j, k;
		if (targetPos.x > curPos.x && targetPos.y > curPos.y)
		{
			i = curPos.x + 1;
			j = targetPos.x;
			k = curPos.y + 1;

			for (; i < j; i++, k++)
			{
				if (ChessBoard::GetInstance()->IsExist({ i, k }))
				{
					return false;
				}
			}
		}
		else if (targetPos.x > curPos.x && targetPos.y < curPos.y)
		{
			i = curPos.x + 1;
			j = targetPos.x;
			k = curPos.y - 1;

			for (; i < j; i++, k--)
			{
				if (ChessBoard::GetInstance()->IsExist({ i, k }))
				{
					return false;
				}
			}
		}
		else if (targetPos.x < curPos.x && targetPos.y > curPos.y)
		{
			i = targetPos.x + 1;
			j = curPos.x;
			k = targetPos.y - 1;

			for (; i < j; i++, k--)
			{
				if (ChessBoard::GetInstance()->IsExist({ i, k }))
				{
					return false;
				}
			}
		}
		else if (targetPos.x < curPos.x && targetPos.y < curPos.y)
		{
			i = targetPos.x + 1;
			j = curPos.x;
			k = targetPos.y + 1;

			for (; i < j; i++, k++)
			{
				if (ChessBoard::GetInstance()->IsExist({ i, k }))
				{
					return false;
				}
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

void Bishop::DrawMovablePos(HDC hdc, POINT curPos)
{
	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::MOVABLE_POS)->Draw(hdc, curPos.x * CHESS_PIECE_SIZE + 24, curPos.y * CHESS_PIECE_SIZE + 24);

	int i = curPos.x;
	int j = curPos.y;
	for (; i < 8; i++, j++)
	{
		if (j >= 8)
			break;

		if (ChessBoard::GetInstance()->GetPiece({ i, j }) == nullptr)
		{
			BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::MOVABLE_POS)->Draw(hdc, i * CHESS_PIECE_SIZE + 24, j * CHESS_PIECE_SIZE + 24);
		}
		else if (ChessBoard::GetInstance()->GetPiece({ i, j })->GetColor() != pieceColor)
		{
			BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::MOVABLE_POS)->Draw(hdc, i * CHESS_PIECE_SIZE + 24, j * CHESS_PIECE_SIZE + 24);
			break;
		}
		else if (ChessBoard::GetInstance()->GetPiece({ i, j }) != this)
		{
			break;
		}
	}

	i = curPos.x;
	j = curPos.y;
	for (; i < 8; i++, j--)
	{
		if (j < 0)
			break;

		if (ChessBoard::GetInstance()->GetPiece({ i, j }) == nullptr)
		{
			BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::MOVABLE_POS)->Draw(hdc, i * CHESS_PIECE_SIZE + 24, j * CHESS_PIECE_SIZE + 24);
		}
		else if (ChessBoard::GetInstance()->GetPiece({ i, j })->GetColor() != pieceColor)
		{
			BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::MOVABLE_POS)->Draw(hdc, i * CHESS_PIECE_SIZE + 24, j * CHESS_PIECE_SIZE + 24);
			break;
		}
		else if (ChessBoard::GetInstance()->GetPiece({ i, j }) != this)
		{
			break;
		}
	}

	i = curPos.x;
	j = curPos.y;
	for (; i >= 0; i--, j--)
	{
		if (j < 0)
			break;

		if (ChessBoard::GetInstance()->GetPiece({ i, j }) == nullptr)
		{
			BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::MOVABLE_POS)->Draw(hdc, i * CHESS_PIECE_SIZE + 24, j * CHESS_PIECE_SIZE + 24);
		}
		else if (ChessBoard::GetInstance()->GetPiece({ i, j })->GetColor() != pieceColor)
		{
			BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::MOVABLE_POS)->Draw(hdc, i * CHESS_PIECE_SIZE + 24, j * CHESS_PIECE_SIZE + 24);
			break;
		}
		else if (ChessBoard::GetInstance()->GetPiece({ i, j }) != this)
		{
			break;
		}
	}

	i = curPos.x;
	j = curPos.y;
	for (; i >= 0; i--, j++)
	{
		if (j >= 8)
			break;

		if (ChessBoard::GetInstance()->GetPiece({ i, j }) == nullptr)
		{
			BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::MOVABLE_POS)->Draw(hdc, i * CHESS_PIECE_SIZE + 24, j * CHESS_PIECE_SIZE + 24);
		}
		else if (ChessBoard::GetInstance()->GetPiece({ i, j })->GetColor() != pieceColor)
		{
			BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::MOVABLE_POS)->Draw(hdc, i * CHESS_PIECE_SIZE + 24, j * CHESS_PIECE_SIZE + 24);
			break;
		}
		else if (ChessBoard::GetInstance()->GetPiece({ i, j }) != this)
		{
			break;
		}
	}
}
