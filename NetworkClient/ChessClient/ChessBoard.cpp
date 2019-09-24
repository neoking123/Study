#include "ChessBoard.h"
#include "BitMapManager.h"
#include "Macro.h"
#include "ChessPiece.h"
#include "King.h"
#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "Pawn.h"

void ChessBoard::DrawPieces(HDC hdc)
{
	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			if (board[y][x] != nullptr)
			{
				board[y][x]->bitmap->Draw(hdc, x * CHESS_PIECE_SIZE + 24, y * CHESS_PIECE_SIZE + 24);
			}	
		}
	}
}

void ChessBoard::InitPieces()
{
	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			board[y][x] = nullptr;
		}
	}

	King* king_w = new King();
	king_w->Init(CHESSPIECE_COLOR::PIECE_WHITE);
	board[7][4] = king_w;

	Queen* queen_w = new Queen();
	queen_w->Init(CHESSPIECE_COLOR::PIECE_WHITE);
	board[7][3] = queen_w;

	Bishop* bishop1_w = new Bishop();
	bishop1_w->Init(CHESSPIECE_COLOR::PIECE_WHITE);
	board[7][2] = bishop1_w;

	Bishop* bishop2_w = new Bishop();
	bishop2_w->Init(CHESSPIECE_COLOR::PIECE_WHITE);
	board[7][5] = bishop2_w;

	Knight* knight1_w = new Knight();
	knight1_w->Init(CHESSPIECE_COLOR::PIECE_WHITE);
	board[7][1] = knight1_w;

	Knight* knight2_w = new Knight();
	knight2_w->Init(CHESSPIECE_COLOR::PIECE_WHITE);
	board[7][6] = knight2_w;

	Rook* rook1_w = new Rook();
	rook1_w->Init(CHESSPIECE_COLOR::PIECE_WHITE);
	board[7][0] = rook1_w;

	Rook* rook2_w = new Rook();
	rook2_w->Init(CHESSPIECE_COLOR::PIECE_WHITE);
	board[7][7] = rook2_w;

	for (int i = 0; i < 8; i++)
	{
		Pawn* pawn_w = new Pawn();
		pawn_w->Init(CHESSPIECE_COLOR::PIECE_WHITE);
		board[6][i] = pawn_w;
	}
	
	King* king_b = new King();
	king_b->Init(CHESSPIECE_COLOR::PIECE_BLACK);
	board[0][4] = king_b;

	Queen* queen_b = new Queen();
	queen_b->Init(CHESSPIECE_COLOR::PIECE_BLACK);
	board[0][3] = queen_b;

	Bishop* bishop1_b = new Bishop();
	bishop1_b->Init(CHESSPIECE_COLOR::PIECE_BLACK);
	board[0][2] = bishop1_b;

	Bishop* bishop2_b = new Bishop();
	bishop2_b->Init(CHESSPIECE_COLOR::PIECE_BLACK);
	board[0][5] = bishop2_b;

	Knight* knight1_b = new Knight();
	knight1_b->Init(CHESSPIECE_COLOR::PIECE_BLACK);
	board[0][1] = knight1_b;

	Knight* knight2_b = new Knight();
	knight2_b->Init(CHESSPIECE_COLOR::PIECE_BLACK);
	board[0][6] = knight2_b;

	Rook* rook1_b = new Rook();
	rook1_b->Init(CHESSPIECE_COLOR::PIECE_BLACK);
	board[0][0] = rook1_b;

	Rook* rook2_b = new Rook();
	rook2_b->Init(CHESSPIECE_COLOR::PIECE_BLACK);
	board[0][7] = rook2_b;

	for (int i = 0; i < 8; i++)
	{
		Pawn* pawn_b = new Pawn();
		pawn_b->Init(CHESSPIECE_COLOR::PIECE_BLACK);
		board[1][i] = pawn_b;
	}

}

ChessBoard::ChessBoard()
{
}


ChessBoard::~ChessBoard()
{
}

void ChessBoard::Init()
{
	bitmap = BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::CHESS_BOARD);
	InitPieces();
}

void ChessBoard::Render(HDC hdc)
{
	bitmap->Draw(hdc, 24, 24);
	DrawPieces(hdc);
}

void ChessBoard::Release()
{
	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			SAFE_DELETE(board[y][x]);
		}
	}
}

void ChessBoard::CheckIsClickedPiece(int cusrsorX, int cursorY)
{
	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			if (x * CHESS_PIECE_SIZE + 24 < cusrsorX && cusrsorX < x * CHESS_PIECE_SIZE + 24 + CHESS_PIECE_SIZE
				&& y * CHESS_PIECE_SIZE + 24 < cursorY && cursorY < y * CHESS_PIECE_SIZE + 24 + CHESS_PIECE_SIZE)
			{
				/*Pawn* pawn_w = new Pawn();
				pawn_w->Init(CHESSPIECE_COLOR::PIECE_WHITE);
				board[y][x] = pawn_w;*/
				return;
			}
		}
	}
}
