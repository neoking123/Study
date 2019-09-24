#pragma once
#include <Windows.h>

class BitMap;
class ChessPiece;

class ChessBoard
{
private:
	BitMap* bitmap;
	ChessPiece* board[8][8];

	bool CheckMove(int x, int y, int targetX, int targetY);
	bool CheckAttack(int x, int y, int targetX, int targetY);
	void DrawPieces(HDC hdc);
	void InitPieces();

public:
	ChessBoard();
	~ChessBoard();

	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();
	void CheckIsClickedPiece(int cusrsorX, int cursorY);
};

