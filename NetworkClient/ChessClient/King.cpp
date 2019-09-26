#include "King.h"
#include "BitMapManager.h"
#include "ChessBoard.h"

King::King()
{
}


King::~King()
{
}

void King::Init(CHESS_PIECE_COLOR pieceColor)
{
	this->pieceColor = pieceColor;
	pieceType = CHESS_PIECE_TYPE::PIECE_TYPE_KING;

	if (this->pieceColor == CHESS_PIECE_COLOR::PIECE_WHITE)
	{
		bitmap = BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::KING_W);
	}
	else if (this->pieceColor == CHESS_PIECE_COLOR::PIECE_BLACK)
	{
		bitmap = BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::KING_B);
	}
	
}

bool King::CheckMove(POINT curPos, POINT targetPos)
{
	if ((targetPos.x >= curPos.x - 1 && targetPos.x <= curPos.x + 1)
		&& (targetPos.y >= curPos.y - 1 && targetPos.y <= curPos.y + 1))
	{
		return true;
	}
	else
	{
		return false;
	}	
}

bool King::CheckAttack(POINT curPos, ChessPiece & targetPiece, POINT targetPos)
{
	if ((targetPos.x >= curPos.x - 1 && targetPos.x <= curPos.x + 1)
		&& (targetPos.y >= curPos.y - 1 && targetPos.y <= curPos.y + 1)
		&& targetPiece.GetColor() != pieceColor)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void King::DrawMovablePos(HDC hdc, POINT curPos)
{
	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::MOVABLE_POS)->Draw(hdc, curPos.x * CHESS_PIECE_SIZE + 24, curPos.y * CHESS_PIECE_SIZE + 24);

	if (curPos.x + 1 < 8)
	{
		if (ChessBoard::GetInstance()->GetPiece({ curPos.x + 1, curPos.y }) == nullptr)
		{
			BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::MOVABLE_POS)->Draw(hdc, (curPos.x + 1) * CHESS_PIECE_SIZE + 24, curPos.y * CHESS_PIECE_SIZE + 24);
		}
		else if(ChessBoard::GetInstance()->GetPiece({ curPos.x + 1, curPos.y })->GetColor() != pieceColor)
		{
			BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::MOVABLE_POS)->Draw(hdc, (curPos.x + 1) * CHESS_PIECE_SIZE + 24, curPos.y * CHESS_PIECE_SIZE + 24);
		}
	}

	if (curPos.x - 1 >= 0)
	{
		if (ChessBoard::GetInstance()->GetPiece({ curPos.x - 1, curPos.y }) == nullptr)
		{
			BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::MOVABLE_POS)->Draw(hdc, (curPos.x - 1) * CHESS_PIECE_SIZE + 24, curPos.y * CHESS_PIECE_SIZE + 24);
		}
		else if (ChessBoard::GetInstance()->GetPiece({ curPos.x - 1, curPos.y })->GetColor() != pieceColor)
		{
			BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::MOVABLE_POS)->Draw(hdc, (curPos.x - 1) * CHESS_PIECE_SIZE + 24, curPos.y * CHESS_PIECE_SIZE + 24);
		}
	}

	if (curPos.y + 1 < 8)
	{
		if (ChessBoard::GetInstance()->GetPiece({ curPos.x, curPos.y + 1 }) == nullptr)
		{
			BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::MOVABLE_POS)->Draw(hdc, curPos.x * CHESS_PIECE_SIZE + 24, (curPos.y + 1) * CHESS_PIECE_SIZE + 24);
		}
		else if (ChessBoard::GetInstance()->GetPiece({ curPos.x, curPos.y + 1 })->GetColor() != pieceColor)
		{
			BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::MOVABLE_POS)->Draw(hdc, curPos.x * CHESS_PIECE_SIZE + 24, (curPos.y + 1) * CHESS_PIECE_SIZE + 24);
		}
	}

	if (curPos.y - 1 >= 0)
	{
		if (ChessBoard::GetInstance()->GetPiece({ curPos.x, curPos.y - 1 }) == nullptr)
		{
			BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::MOVABLE_POS)->Draw(hdc, curPos.x * CHESS_PIECE_SIZE + 24, (curPos.y - 1) * CHESS_PIECE_SIZE + 24);
		}
		else if (ChessBoard::GetInstance()->GetPiece({ curPos.x, curPos.y - 1 })->GetColor() != pieceColor)
		{
			BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::MOVABLE_POS)->Draw(hdc, curPos.x * CHESS_PIECE_SIZE + 24, (curPos.y - 1) * CHESS_PIECE_SIZE + 24);
		}
	}
	
	if (curPos.x + 1 < 8 && curPos.y - 1 >= 0)
	{
		if (ChessBoard::GetInstance()->GetPiece({ curPos.x + 1, curPos.y - 1 }) == nullptr)
		{
			BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::MOVABLE_POS)->Draw(hdc, (curPos.x + 1) * CHESS_PIECE_SIZE + 24, (curPos.y - 1) * CHESS_PIECE_SIZE + 24);
		}
		else if (ChessBoard::GetInstance()->GetPiece({ curPos.x + 1, curPos.y - 1 })->GetColor() != pieceColor)
		{
			BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::MOVABLE_POS)->Draw(hdc, (curPos.x + 1) * CHESS_PIECE_SIZE + 24, (curPos.y - 1) * CHESS_PIECE_SIZE + 24);
		}
	}

	if (curPos.x + 1 < 8 && curPos.y + 1 < 8)
	{
		if (ChessBoard::GetInstance()->GetPiece({ curPos.x + 1, curPos.y + 1 }) == nullptr)
		{
			BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::MOVABLE_POS)->Draw(hdc, (curPos.x + 1) * CHESS_PIECE_SIZE + 24, (curPos.y + 1) * CHESS_PIECE_SIZE + 24);
		}
		else if (ChessBoard::GetInstance()->GetPiece({ curPos.x + 1, curPos.y + 1 })->GetColor() != pieceColor)
		{
			BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::MOVABLE_POS)->Draw(hdc, (curPos.x + 1) * CHESS_PIECE_SIZE + 24, (curPos.y + 1) * CHESS_PIECE_SIZE + 24);
		}
	}

	if (curPos.x - 1 >= 0 && curPos.y + 1 < 8)
	{
		if (ChessBoard::GetInstance()->GetPiece({ curPos.x - 1, curPos.y + 1 }) == nullptr)
		{
			BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::MOVABLE_POS)->Draw(hdc, (curPos.x - 1) * CHESS_PIECE_SIZE + 24, (curPos.y + 1) * CHESS_PIECE_SIZE + 24);
		}
		else if (ChessBoard::GetInstance()->GetPiece({ curPos.x - 1, curPos.y + 1 })->GetColor() != pieceColor)
		{
			BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::MOVABLE_POS)->Draw(hdc, (curPos.x - 1) * CHESS_PIECE_SIZE + 24, (curPos.y + 1) * CHESS_PIECE_SIZE + 24);
		}
	}

	if (curPos.x - 1 >= 0 && curPos.y - 1 >= 0)
	{
		if (ChessBoard::GetInstance()->GetPiece({ curPos.x - 1, curPos.y - 1 }) == nullptr)
		{
			BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::MOVABLE_POS)->Draw(hdc, (curPos.x - 1) * CHESS_PIECE_SIZE + 24, (curPos.y - 1) * CHESS_PIECE_SIZE + 24);
		}
		else if (ChessBoard::GetInstance()->GetPiece({ curPos.x - 1, curPos.y - 1 })->GetColor() != pieceColor)
		{
			BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::MOVABLE_POS)->Draw(hdc, (curPos.x - 1) * CHESS_PIECE_SIZE + 24, (curPos.y - 1) * CHESS_PIECE_SIZE + 24);
		}
	}

}
