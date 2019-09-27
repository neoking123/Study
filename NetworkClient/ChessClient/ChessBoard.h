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
	static ChessBoard* instance;

	BitMap* bitmap;
	ChessPiece* board[8][8];
	CLICK_STATE clickState;

	int playerColor;
	POINT clickFirstPos;
	POINT clickSecondPos;
	int clickFirstType;
	int clickFirstColor;
	int clickSecondType;
	int clickSecondColor;
	

	ChessBoard();

	bool CheckMove(ChessPiece& piece, POINT curPos, POINT targetPos);
	bool CheckAttack(ChessPiece & curPiece, POINT curPos, ChessPiece & targetPiece, POINT targetPos);
	void DrawPieces(HDC hdc);
	void DrawPieceMovablePos(HDC hdc);
	void InitPieces();
	bool CheckIsClickedPiece(int cusrsorX, int cursorY);
	void SendMoveTo(int type, int color, POINT curPos, POINT targetPos);
	ChessPiece* FindMyKing(POINT& kingPos);
	ChessPiece* FindEnemyKing(POINT& kingPos);
	bool CanBeAttackedMyKing(ChessPiece* king, POINT& kingPos);
	bool CanBeAttackedEnemyKing(ChessPiece* king, POINT& kingPos);
	bool IsEnemyCheck();
	bool AmICheck();
	ChessPiece* MoveToTemp(POINT curPos, POINT targetPos);

public:
	int checkState;

	~ChessBoard();

	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();
	void MouseInput(int x, int y);
	void MoveTo(POINT curPos, POINT targetPos);
	bool IsExist(POINT pos);

	inline ChessPiece* GetPiece(POINT pos)
	{
		return board[pos.y][pos.x];
	}

	inline int GetPlayerColor()
	{
		return playerColor;
	}

	inline void SetPlayerColor(int playerColor)
	{
		this->playerColor = playerColor;
	}

	inline static ChessBoard* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new ChessBoard();
		}
		return instance;
	}

	inline static void FreeInstance()
	{
		if (instance != nullptr)
		{
			delete instance;
			instance = nullptr;
		}
	}
	
};

