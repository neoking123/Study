#include "ChattingManager.h"
#include "BitMapManager.h"
#include "ChessGame.h"
#include "..\..\Common\ChessPacket.h"

ChattingManager* ChattingManager::instance = nullptr;

ChattingManager::ChattingManager()
{
}

void ChattingManager::SendChat()
{
	PACKET_CHAT packet;
	packet.header.type = PACKET_TYPE::PACKET_TYPE_CHAT;
	packet.header.len = sizeof(packet);
	packet.playerIndex = ChessGame::GetInstance()->playerIndex;
	packet.sendPos = -1;
	strcpy(packet.chat, chat);
	send(ChessGame::GetInstance()->GetSock(), (const char*)&packet, packet.header.len, 0);
}

ChattingManager::~ChattingManager()
{
}

void ChattingManager::Init(HWND hWnd, HINSTANCE g_hInst)
{
	hChat = CreateWindow("edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 218, 837, 220, 20, hWnd, (HMENU)ID_EDIT_0, g_hInst, NULL);
	hChatList = CreateWindow("edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOVSCROLL | ES_MULTILINE, 55, 705, 420, 120, hWnd, (HMENU)ID_EDIT_1, g_hInst, NULL);
}

void ChattingManager::Input()
{
	if ((GetAsyncKeyState(VK_RETURN) & 0x8000))
	{
		SendChat();

		SetWindowText(hChat, "");
		GetWindowText(hChat, chat, 128);
	}
	else
	{
		GetWindowText(hChat, chat, 128);
	}
}

void ChattingManager::DrawChat(HDC hdc)
{
	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::LOBBY_CHAT)->Draw(hdc, 50, 700);
}
