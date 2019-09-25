#pragma once
#include <Windows.h>

class BitMap;
class ChessPiece;

enum CLICK_STATE
{
	CLICK_FIRST,
	CLICK_NONE
};

struct ClickCheck
{
	POINT pos;
	int type;
	int color;

	ClickCheck& operator=(const ClickCheck& cc)
	{
		pos = cc.pos;
		type = cc.type;
		color = cc.color;
		return *this;
	}
};

class ChessBoard
{
private:
	BitMap* bitmap;
	ChessPiece* board[8][8];
	CLICK_STATE clickState;

	POINT clickFirstPos;
	POINT clickSecondPos;
	int clickFirstType;
	int clickFirstColor;
	int clickSecondType;
	int clickSecondColor;

	bool CheckMove(ChessPiece& piece, POINT curPos, POINT targetPos);
	bool CheckAttack(ChessPiece & curPiece, POINT curPos, ChessPiece & targetPiece, POINT targetPos);
	void DrawPieces(HDC hdc);
	void InitPieces();
	bool CheckIsClickedPiece(int cusrsorX, int cursorY);
	void SendMoveTo(int type, int color, POINT curPos, POINT targetPos);

public:
	ChessBoard();
	~ChessBoard();

	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();
	void MouseInput(int x, int y);
	void MoveTo(POINT curPos, POINT targetPos);
	
};

