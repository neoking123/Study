#include "ChattingManager.h"
#include "BitMapManager.h"
#include "LobbyManager.h"
#include "CatchMind.h"
#include "..\..\Common\NetworkManager.h"

ChattingManager* ChattingManager::instance = nullptr;

ChattingManager::ChattingManager()
{
}

ChattingManager::~ChattingManager()
{
}

void ChattingManager::Init(HWND hWnd, HINSTANCE g_hInst)
{
	this->hWnd = hWnd;
	hChat = CreateWindow("edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL | ES_WANTRETURN, 568, 837, 220, 20, hWnd, (HMENU)ID_EDIT_0, g_hInst, NULL);
	hChatList = CreateWindow("edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOVSCROLL | ES_MULTILINE | WS_VSCROLL, 405, 705, 420, 120, hWnd, (HMENU)ID_EDIT_1, g_hInst, NULL);
	ShowWindow(hChat, SW_HIDE);
	ShowWindow(hChatList, SW_HIDE);
	returnInputTime = 0.0f;
}

void ChattingManager::Input()
{
	if (CatchMind::GetInstance()->GetSceneState() == SCENE_STATE::INGAME_SCENE)
	{
		int roomNum = LobbyManager::GetInstance()->GetRoomNum(CatchMind::GetInstance()->playerIndex);
		if (LobbyManager::GetInstance()->GetCurrentTurn(roomNum) == CatchMind::GetInstance()->playerIndex)
			return;
	}

	if ((GetAsyncKeyState(VK_RETURN) & 0x0001))
	{
		int playerIndex = CatchMind::GetInstance()->playerIndex;
		int roomNum = LobbyManager::GetInstance()->GetRoomNum(playerIndex);

		if (strcmp(chat, ""))
		{
			NetworkManager::GetInstance()->SendChat(playerIndex, roomNum, chat);
		}

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
	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::LOBBY_CHAT)->Draw(hdc, 400, 700);
}

void ChattingManager::PrintChat(int playerIndex, string chat)
{
	if (CatchMind::GetInstance()->GetSceneState() == SCENE_STATE::LOGIN_SCENE)
		return;

	stringstream ss;
	ss << playerIndex;

	string s = LobbyManager::GetInstance()->GetNickName(playerIndex);
	chatList += " " + s + " : " + chat + "\r\n";
	SetWindowText(hChatList, chatList.c_str());
	
	SendMessageA(hChatList, EM_SETSEL, 0, -1);
	SendMessageA(hChatList, EM_SETSEL, -1, -1);
	SendMessageA(hChatList, EM_SCROLLCARET, 0, 0);
}

void ChattingManager::PrintAnswer(int playerIndex, string answer)
{
	string answerPlayer = LobbyManager::GetInstance()->GetNickName(playerIndex);
	chatList += "<정답 : " + answer + ", 맞추신 분 : " + answerPlayer + ">" + "\r\n";

	SetWindowText(hChatList, chatList.c_str());
	SendMessageA(hChatList, EM_SETSEL, 0, -1);
	SendMessageA(hChatList, EM_SETSEL, -1, -1);
	SendMessageA(hChatList, EM_SCROLLCARET, 0, 0);
}
