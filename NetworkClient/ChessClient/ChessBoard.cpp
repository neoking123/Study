#include "ChessBoard.h"
#include "..\..\Common\ChessPacket.h"
#include "ChessGame.h"
#include "LobbyManager.h"
#include "BitMapManager.h"
#include "Macro.h"
#include "ChessPiece.h"
#include "King.h"
#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "Pawn.h"

bool ChessBoard::CheckMove(ChessPiece& piece, POINT curPos, POINT targetPos)
{
	if (piece.CheckMove(curPos, targetPos))
	{
		return true;
	}
	return false;
}

bool ChessBoard::CheckAttack(ChessPiece & curPiece, POINT curPos, ChessPiece & targetPiece, POINT targetPos)
{
	if (curPiece.CheckAttack(curPos, targetPiece, targetPos))
	{
		return true;
	}

	return false;
}

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
	king_w->Init(CHESS_PIECE_COLOR::PIECE_WHITE);
	board[7][4] = king_w;

	Queen* queen_w = new Queen();
	queen_w->Init(CHESS_PIECE_COLOR::PIECE_WHITE);
	board[7][3] = queen_w;

	Bishop* bishop1_w = new Bishop();
	bishop1_w->Init(CHESS_PIECE_COLOR::PIECE_WHITE);
	board[7][2] = bishop1_w;

	Bishop* bishop2_w = new Bishop();
	bishop2_w->Init(CHESS_PIECE_COLOR::PIECE_WHITE);
	board[7][5] = bishop2_w;

	Knight* knight1_w = new Knight();
	knight1_w->Init(CHESS_PIECE_COLOR::PIECE_WHITE);
	board[7][1] = knight1_w;

	Knight* knight2_w = new Knight();
	knight2_w->Init(CHESS_PIECE_COLOR::PIECE_WHITE);
	board[7][6] = knight2_w;

	Rook* rook1_w = new Rook();
	rook1_w->Init(CHESS_PIECE_COLOR::PIECE_WHITE);
	board[7][0] = rook1_w;

	Rook* rook2_w = new Rook();
	rook2_w->Init(CHESS_PIECE_COLOR::PIECE_WHITE);
	board[7][7] = rook2_w;

	/*for (int i = 0; i < 8; i++)
	{
		Pawn* pawn_w = new Pawn();
		pawn_w->Init(CHESS_PIECE_COLOR::PIECE_WHITE);
		board[6][i] = pawn_w;
	}*/
	
	King* king_b = new King();
	king_b->Init(CHESS_PIECE_COLOR::PIECE_BLACK);
	board[0][4] = king_b;

	Queen* queen_b = new Queen();
	queen_b->Init(CHESS_PIECE_COLOR::PIECE_BLACK);
	board[0][3] = queen_b;

	Bishop* bishop1_b = new Bishop();
	bishop1_b->Init(CHESS_PIECE_COLOR::PIECE_BLACK);
	board[0][2] = bishop1_b;

	Bishop* bishop2_b = new Bishop();
	bishop2_b->Init(CHESS_PIECE_COLOR::PIECE_BLACK);
	board[0][5] = bishop2_b;

	Knight* knight1_b = new Knight();
	knight1_b->Init(CHESS_PIECE_COLOR::PIECE_BLACK);
	board[0][1] = knight1_b;

	Knight* knight2_b = new Knight();
	knight2_b->Init(CHESS_PIECE_COLOR::PIECE_BLACK);
	board[0][6] = knight2_b;

	Rook* rook1_b = new Rook();
	rook1_b->Init(CHESS_PIECE_COLOR::PIECE_BLACK);
	board[0][0] = rook1_b;

	Rook* rook2_b = new Rook();
	rook2_b->Init(CHESS_PIECE_COLOR::PIECE_BLACK);
	board[0][7] = rook2_b;

	for (int i = 0; i < 8; i++)
	{
		Pawn* pawn_b = new Pawn();
		pawn_b->Init(CHESS_PIECE_COLOR::PIECE_BLACK);
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
	clickState = CLICK_STATE::CLICK_NONE;
	clickFirstPos = { -1, -1 };
	clickSecondPos = { -1, -1 };
	clickFirstType = CHESS_PIECE_TYPE::PIECE_TYPE_NONE;
	clickFirstColor = CHESS_PIECE_COLOR::PIECE_NONE;
	clickSecondType = CHESS_PIECE_TYPE::PIECE_TYPE_NONE;
	clickSecondColor = CHESS_PIECE_COLOR::PIECE_NONE;
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

void ChessBoard::MouseInput(int x, int y)
{
	//ClickCheck cc;

	if (CheckIsClickedPiece(x, y))
	{
		//cc = CheckIsClickedPiece(x, y);

		switch (clickState)
		{
		case CLICK_STATE::CLICK_NONE:
			clickState = CLICK_STATE::CLICK_FIRST;
			break;

		case CLICK_STATE::CLICK_FIRST:
			clickState = CLICK_STATE::CLICK_NONE;
			
			if ((clickFirstPos.x != clickSecondPos.x) || (clickFirstPos.y != clickSecondPos.y))
			{
				if (board[clickSecondPos.y][clickSecondPos.x] == nullptr)
				{
					if (CheckMove(*board[clickFirstPos.y][clickFirstPos.x], clickFirstPos, clickSecondPos))
					{
						SendMoveTo(clickFirstType, clickFirstColor, clickFirstPos, clickSecondPos);
					}
				}
				else
				{
					if (CheckAttack(*board[clickFirstPos.y][clickFirstPos.x], clickFirstPos, *board[clickSecondPos.y][clickSecondPos.x], clickSecondPos)
						|| CheckMove(*board[clickFirstPos.y][clickFirstPos.x], clickFirstPos, clickSecondPos))
					{
						SendMoveTo(clickFirstType, clickFirstColor, clickFirstPos, clickSecondPos);
					}
				}
			}
			
			clickFirstPos = { -1, -1 };
			clickSecondPos = { -1, -1 };
			clickFirstType = CHESS_PIECE_TYPE::PIECE_TYPE_NONE;
			clickFirstColor = CHESS_PIECE_COLOR::PIECE_NONE;
			break;
		}
	}
}

void ChessBoard::MoveTo(POINT curPos, POINT targetPos)
{
	SAFE_DELETE(board[targetPos.y][targetPos.x]);
	board[targetPos.y][targetPos.x] = board[curPos.y][curPos.x];
	board[curPos.y][curPos.x] = nullptr;
}

bool ChessBoard::CheckIsClickedPiece(int cusrsorX, int cursorY)
{
	//ClickCheck cc = { {-1, -1} , false, CHESS_PIECE_TYPE::PIECE_TYPE_NONE, CHESSPIECE_COLOR::PIECE_NONE };

	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			if (x * CHESS_PIECE_SIZE + 24 < cusrsorX && cusrsorX < x * CHESS_PIECE_SIZE + 24 + CHESS_PIECE_SIZE
				&& y * CHESS_PIECE_SIZE + 24 < cursorY && cursorY < y * CHESS_PIECE_SIZE + 24 + CHESS_PIECE_SIZE)
			{
				if (clickState == CLICK_STATE::CLICK_NONE)
				{
					if (board[y][x] != nullptr)
					{
						clickFirstPos = { x, y };
						clickFirstType = board[y][x]->GetType();
						clickFirstColor = board[y][x]->GetColor();
						return true;
					}
				}
				else if (clickState == CLICK_STATE::CLICK_FIRST)
				{
					clickSecondPos = { x, y };
					if (board[y][x] != nullptr)
					{
						clickSecondType = board[y][x]->GetType();
						clickSecondColor = board[y][x]->GetColor();
					}
					return true;
				}
			}
		}
	}

	return false;
}

void ChessBoard::SendMoveTo(int type, int color, POINT curPos, POINT targetPos)
{
	PACKET_MOVE_TO packet;
	packet.header.type = PACKET_TYPE::PACKET_TYPE_MOVE_TO;
	packet.header.len = sizeof(packet);
	packet.roomNum = LobbyManager::GetInstance()->GetRoomNum(ChessGame::GetInstance()->playerIndex);
	packet.moveDate.curPos = curPos;
	packet.moveDate.targetPos = targetPos;
	packet.moveDate.pieceType = type;
	packet.moveDate.pieceColor = color;
	send(ChessGame::GetInstance()->GetSock(), (const char*)&packet, packet.header.len, 0);
}
