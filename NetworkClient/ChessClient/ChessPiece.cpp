#include "ChessPiece.h"
#include "BitMapManager.h"

ChessPiece::ChessPiece()
{
}


ChessPiece::~ChessPiece()
{
}

//void ChessPiece::Init(InputComponent* input, int x, int y, string tag)
//{
//	
//}
//
//void ChessPiece::Init(InputComponent* input, int x, int y, string tag, CHESSPIECE_COLOR pieceColor, CHESS_PIECE_TYPE pieceType)
//{
//	this->input = input;
//	transform.position.x = x;
//	transform.position.y = y;
//	this->tag = tag;
//	this->pieceType = pieceType;
//	this->pieceColor = pieceColor;
//	SetBitMap(this->pieceColor, this->pieceType);
//}
//
//void ChessPiece::Update()
//{
//}
//
//void ChessPiece::Render(HDC hdc)
//{
//	bitmap->Draw(hdc, transform.position.x, transform.position.y);
//}
//
//void ChessPiece::SetPosition(int x, int y)
//{
//}
//
//void ChessPiece::SetBitMap(CHESSPIECE_COLOR pieceColor, CHESS_PIECE_TYPE pieceType)
//{
//	if (pieceColor == CHESSPIECE_COLOR::PIECE_BLACK)
//	{
//		switch (pieceType)
//		{
//		case PIECE_TYPE_KING:
//			bitmap = BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::KING_B);
//			break;
//		case PIECE_TYPE_QUEEN:
//			bitmap = BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::QUEEN_B);
//			break;
//		case PIECE_TYPE_ROOK:
//			bitmap = BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::ROOK_B);
//			break;
//		case PIECE_TYPE_BISHOP:
//			bitmap = BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::BISHOP_B);
//			break;
//		case PIECE_TYPE_KNIGHT:
//			bitmap = BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::KNIGHT_B);
//			break;
//		case PIECE_TYPE_PAWN:
//			bitmap = BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::PAWN_B);
//			break;
//		}
//	}
//	else if (pieceColor == CHESSPIECE_COLOR::PIECE_WHITE)
//	{
//		switch (pieceType)
//		{
//		case PIECE_TYPE_KING:
//			bitmap = BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::KING_W);
//			break;
//		case PIECE_TYPE_QUEEN:
//			bitmap = BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::QUEEN_W);
//			break;
//		case PIECE_TYPE_ROOK:
//			bitmap = BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::ROOK_W);
//			break;
//		case PIECE_TYPE_BISHOP:
//			bitmap = BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::BISHOP_W);
//			break;
//		case PIECE_TYPE_KNIGHT:
//			bitmap = BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::KNIGHT_W);
//			break;
//		case PIECE_TYPE_PAWN:
//			bitmap = BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::PAWN_W);
//			break;
//		}
//	}
//}
