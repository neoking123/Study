#include "ChattingManager.h"
#include "BitMapManager.h"
#include "LobbyManager.h"
#include "CatchMind.h"
#include "..\..\Common\NetworkManager.h"

ChattingManager* ChattingManager::instance = nullptr;

ChattingManager::ChattingManager()
{
}

void ChattingManager::SendChat()
{
	PACKET_CHAT packet;
	packet.header.type = PACKET_TYPE::PACKET_TYPE_CHAT;
	packet.header.len = sizeof(packet);
	//packetBuf.playerIndex = ChessGame::GetInstance()->playerIndex;
	//packetBuf.roomNum = LobbyManager::GetInstance()->GetRoomNum(ChessGame::GetInstance()->playerIndex);
	strcpy(packet.chat, chat);
	//send(ChessGame::GetInstance()->GetSock(), (const char*)&packetBuf, packetBuf.header.len, 0);
}

ChattingManager::~ChattingManager()
{
}

void ChattingManager::Init(HWND hWnd, HINSTANCE g_hInst)
{
	this->hWnd = hWnd;
	hChat = CreateWindow("edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL | ES_WANTRETURN, 218, 837, 220, 20, hWnd, (HMENU)ID_EDIT_0, g_hInst, NULL);
	hChatList = CreateWindow("edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOVSCROLL | ES_MULTILINE | WS_VSCROLL, 55, 705, 420, 120, hWnd, (HMENU)ID_EDIT_1, g_hInst, NULL);
	returnInputTime = 0.0f;
}

void ChattingManager::Input()
{
	if ((GetAsyncKeyState(VK_RETURN) & 0x0001))
	{
		//SendChat();
		int playerIndex = CatchMind::GetInstance()->playerIndex;
		int roomNum = LobbyManager::GetInstance()->GetRoomNum(playerIndex);
		NetworkManager::GetInstance()->SendChat(playerIndex, roomNum, chat);

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

void ChattingManager::PrintChat(int playerIndex, string chat)
{
	stringstream ss;
	ss << playerIndex;
	chatList += " player" + ss.str() + " : " + chat + "\r\n";
	SetWindowText(hChatList, chatList.c_str());
	
	SendMessageA(hChatList, EM_SETSEL, 0, -1);
	SendMessageA(hChatList, EM_SETSEL, -1, -1);
	SendMessageA(hChatList, EM_SCROLLCARET, 0, 0);
}
