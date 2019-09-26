#pragma once
#include <Windows.h>

#define CHESS_PIECE_SIZE 77

enum CHESS_PIECE_TYPE
{
	PIECE_TYPE_KING,
	PIECE_TYPE_QUEEN,
	PIECE_TYPE_ROOK,
	PIECE_TYPE_BISHOP,
	PIECE_TYPE_KNIGHT,
	PIECE_TYPE_PAWN,
	PIECE_TYPE_NONE
};

enum CHESS_PIECE_COLOR
{
	PIECE_BLACK,
	PIECE_WHITE,
	PIECE_NONE
};

class BitMap;

class ChessPiece
{
protected:
	CHESS_PIECE_COLOR pieceColor = CHESS_PIECE_COLOR::PIECE_NONE;
	CHESS_PIECE_TYPE pieceType = CHESS_PIECE_TYPE::PIECE_TYPE_NONE;
	
public:
	BitMap* bitmap;

	ChessPiece();
	~ChessPiece();

	virtual bool CheckMove(POINT curPos, POINT targetPos) = 0;
	virtual bool CheckAttack(POINT curPos, ChessPiece& targetPiece, POINT targetPos) = 0;
	virtual void DrawMovablePos(HDC hdc, POINT curPos) = 0;

	inline virtual CHESS_PIECE_COLOR GetColor() const
	{
		return pieceColor;
	}

	inline virtual CHESS_PIECE_TYPE GetType() const
	{
		return pieceType;
	}

	/*virtual void Init(InputComponent* input, int x = 0, int y = 0, string tag = "") override;
	void Init(InputComponent* input, int x = 0, int y = 0, string tag = "", CHESSPIECE_COLOR pieceColor = CHESSPIECE_COLOR::PIECE_NONE, CHESS_PIECE_TYPE pieceType = CHESS_PIECE_TYPE::PIECE_TYPE_NONE);
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void SetPosition(int x, int y) override;
	void SetBitMap(CHESSPIECE_COLOR pieceColor, CHESS_PIECE_TYPE pieceType);*/
};

