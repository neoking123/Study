#include "Pawn.h"
#include "BitMapManager.h"
#include "ChessBoard.h"

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
	isFirst = false;

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
	if(pieceColor == CHESS_PIECE_COLOR::PIECE_WHITE)
	{
		if (!isFirst)
		{
			if (targetPos.y == curPos.y - 1 && targetPos.x == curPos.x)
			{
				isFirst = true;
				return true;
			}
			else if (targetPos.y == curPos.y - 2 && targetPos.x == curPos.x)
			{
				if (ChessBoard::GetInstance()->IsExist({ curPos.x, curPos.y - 1 }))
					return false;
				else
				{
					isFirst = true;
					return true;
				}
			}
			else
			{
				return false;
			}
		}
		else
		{
			if (targetPos.y == curPos.y - 1 && targetPos.x == curPos.x)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	else if (pieceColor == CHESS_PIECE_COLOR::PIECE_BLACK)
	{
		if (!isFirst)
		{
			if (targetPos.y == curPos.y + 1 && targetPos.x == curPos.x)
			{
				isFirst = true;
				return true;
			}
			else if (targetPos.y == curPos.y + 2 && targetPos.x == curPos.x)
			{
				if (ChessBoard::GetInstance()->IsExist({ curPos.x, curPos.y + 1 }))
					return false;
				else
				{
					isFirst = true;
					return true;
				}
			}
			else
			{
				return false;
			}
		}
		else
		{
			if (targetPos.y == curPos.y + 1 && targetPos.x == curPos.x)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	
}

bool Pawn::CheckAttack(POINT curPos, ChessPiece & targetPiece, POINT targetPos)
{
	if (pieceColor == CHESS_PIECE_COLOR::PIECE_WHITE)
	{
		if ((targetPos.y == curPos.y - 1 && (targetPos.x == curPos.x - 1 || targetPos.x == curPos.x + 1))
			&& targetPiece.GetColor() != pieceColor)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else if (pieceColor == CHESS_PIECE_COLOR::PIECE_BLACK)
	{
		if ((targetPos.y == curPos.y + 1 && (targetPos.x == curPos.x - 1 || targetPos.x == curPos.x + 1))
			&& targetPiece.GetColor() != pieceColor)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

void Pawn::DrawMovablePos(HDC hdc, POINT curPos)
{
	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::MOVABLE_POS)->Draw(hdc, curPos.x * CHESS_PIECE_SIZE + 24, curPos.y * CHESS_PIECE_SIZE + 24);

	if (pieceColor == CHESS_PIECE_COLOR::PIECE_WHITE)
	{
		if (!isFirst)
		{
			if (ChessBoard::GetInstance()->GetPiece({ curPos.x, curPos.y - 1 }) == nullptr
				&& ChessBoard::GetInstance()->GetPiece({ curPos.x, curPos.y - 2 }) == nullptr)
			{
				BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::MOVABLE_POS)->Draw(hdc, curPos.x * CHESS_PIECE_SIZE + 24, (curPos.y - 1) * CHESS_PIECE_SIZE + 24);
				BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::MOVABLE_POS)->Draw(hdc, curPos.x * CHESS_PIECE_SIZE + 24, (curPos.y - 2) * CHESS_PIECE_SIZE + 24);
			}
			else if (ChessBoard::GetInstance()->GetPiece({ curPos.x, curPos.y - 1 }) == nullptr)
			{
				BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::MOVABLE_POS)->Draw(hdc, curPos.x * CHESS_PIECE_SIZE + 24, (curPos.y - 1) * CHESS_PIECE_SIZE + 24);
			}

			if (ChessBoard::GetInstance()->GetPiece({ curPos.x - 1, curPos.y - 1 }) != nullptr)
			{
				if (ChessBoard::GetInstance()->GetPiece({ curPos.x - 1, curPos.y - 1 })->GetColor() != pieceColor)
				{
					BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::MOVABLE_POS)->Draw(hdc, (curPos.x - 1) * CHESS_PIECE_SIZE + 24, (curPos.y - 1) * CHESS_PIECE_SIZE + 24);
				}
			}

			if (ChessBoard::GetInstance()->GetPiece({ curPos.x + 1, curPos.y - 1 }) != nullptr)
			{
				if (ChessBoard::GetInstance()->GetPiece({ curPos.x + 1, curPos.y - 1 })->GetColor() != pieceColor)
				{
					BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::MOVABLE_POS)->Draw(hdc, (curPos.x + 1) * CHESS_PIECE_SIZE + 24, (curPos.y - 1) * CHESS_PIECE_SIZE + 24);
				}
			}
		}
		else
		{
			if (ChessBoard::GetInstance()->GetPiece({ curPos.x, curPos.y - 1 }) == nullptr)
			{
				BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::MOVABLE_POS)->Draw(hdc, curPos.x * CHESS_PIECE_SIZE + 24, (curPos.y - 1) * CHESS_PIECE_SIZE + 24);
			}

			if (ChessBoard::GetInstance()->GetPiece({ curPos.x - 1, curPos.y - 1 }) != nullptr)
			{
				if (ChessBoard::GetInstance()->GetPiece({ curPos.x - 1, curPos.y - 1 })->GetColor() != pieceColor)
				{
					BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::MOVABLE_POS)->Draw(hdc, (curPos.x - 1) * CHESS_PIECE_SIZE + 24, (curPos.y - 1) * CHESS_PIECE_SIZE + 24);
				}
			}

			if (ChessBoard::GetInstance()->GetPiece({ curPos.x + 1, curPos.y - 1 }) != nullptr)
			{
				if (ChessBoard::GetInstance()->GetPiece({ curPos.x + 1, curPos.y - 1 })->GetColor() != pieceColor)
				{
					BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::MOVABLE_POS)->Draw(hdc, (curPos.x + 1) * CHESS_PIECE_SIZE + 24, (curPos.y - 1) * CHESS_PIECE_SIZE + 24);
				}
			}
		}
	}
	else if (pieceColor == CHESS_PIECE_COLOR::PIECE_BLACK)
	{
		if (!isFirst)
		{
			if (ChessBoard::GetInstance()->GetPiece({ curPos.x, curPos.y +1 }) == nullptr
				&& ChessBoard::GetInstance()->GetPiece({ curPos.x, curPos.y + 2 }) == nullptr)
			{
				BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::MOVABLE_POS)->Draw(hdc, curPos.x * CHESS_PIECE_SIZE + 24, (curPos.y + 1) * CHESS_PIECE_SIZE + 24);
				BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::MOVABLE_POS)->Draw(hdc, curPos.x * CHESS_PIECE_SIZE + 24, (curPos.y + 2) * CHESS_PIECE_SIZE + 24);
			}
			else if (ChessBoard::GetInstance()->GetPiece({ curPos.x, curPos.y + 1 }) == nullptr)
			{
				BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::MOVABLE_POS)->Draw(hdc, curPos.x * CHESS_PIECE_SIZE + 24, (curPos.y + 1) * CHESS_PIECE_SIZE + 24);
			}

			if (ChessBoard::GetInstance()->GetPiece({ curPos.x - 1, curPos.y + 1 }) != nullptr)
			{
				if (ChessBoard::GetInstance()->GetPiece({ curPos.x - 1, curPos.y + 1 })->GetColor() != pieceColor)
				{
					BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::MOVABLE_POS)->Draw(hdc, (curPos.x - 1) * CHESS_PIECE_SIZE + 24, (curPos.y + 1) * CHESS_PIECE_SIZE + 24);
				}
			}

			if (ChessBoard::GetInstance()->GetPiece({ curPos.x + 1, curPos.y + 1 }) != nullptr)
			{
				if (ChessBoard::GetInstance()->GetPiece({ curPos.x + 1, curPos.y + 1 })->GetColor() != pieceColor)
				{
					BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::MOVABLE_POS)->Draw(hdc, (curPos.x + 1) * CHESS_PIECE_SIZE + 24, (curPos.y + 1) * CHESS_PIECE_SIZE + 24);
				}
			}
		}
		else
		{
			if (ChessBoard::GetInstance()->GetPiece({ curPos.x, curPos.y + 1 }) == nullptr)
			{
				BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::MOVABLE_POS)->Draw(hdc, curPos.x * CHESS_PIECE_SIZE + 24, (curPos.y + 1) * CHESS_PIECE_SIZE + 24);
			}

			if (ChessBoard::GetInstance()->GetPiece({ curPos.x - 1, curPos.y + 1 }) != nullptr)
			{
				if (ChessBoard::GetInstance()->GetPiece({ curPos.x - 1, curPos.y + 1 })->GetColor() != pieceColor)
				{
					BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::MOVABLE_POS)->Draw(hdc, (curPos.x - 1) * CHESS_PIECE_SIZE + 24, (curPos.y + 1) * CHESS_PIECE_SIZE + 24);
				}
			}

			if (ChessBoard::GetInstance()->GetPiece({ curPos.x + 1, curPos.y + 1 }) != nullptr)
			{
				if (ChessBoard::GetInstance()->GetPiece({ curPos.x + 1, curPos.y + 1 })->GetColor() != pieceColor)
				{
					BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::MOVABLE_POS)->Draw(hdc, (curPos.x + 1) * CHESS_PIECE_SIZE + 24, (curPos.y + 1) * CHESS_PIECE_SIZE + 24);
				}
			}
		}
	}
}
