#include "CatchMind.h"
#include "BitMapManager.h"
#include "LobbyManager.h"
#include "ChattingManager.h"
#include "..\..\Common\NetworkManager.h"
#include "SketchBook.h"

CatchMind* CatchMind::instance = nullptr;

CatchMind::CatchMind()
{
}

void CatchMind::DrawLogin(HDC hdc)
{
	DrawBackground(hdc);
	DrawLoginInfo(hdc);
	DrawKungyasToSelect(hdc);
}

void CatchMind::DrawInRoom(HDC hdc)
{
	DrawBackground(hdc);
	DrawInGameFrame(hdc);
	DrawPalette(hdc);
	DrawEraseAllButton(hdc);
	DrawTimer(hdc);
	DrawDockBar(hdc);
	DrawBackButton(hdc);
	DrawExitButton(hdc);
	DrawPlayersInfo(hdc);
	DrawStartButton(hdc);
	DrawRoomState(hdc);
	ChattingManager::GetInstance()->DrawChat(hdc);
}

void CatchMind::DrawInGame(HDC hdc)
{
	DrawBackground(hdc);
	DrawInGameFrame(hdc);
	DrawPalette(hdc);
	DrawEraseAllButton(hdc);
	DrawTimer(hdc);
	DrawDockBar(hdc);
	DrawBackButton(hdc);
	DrawExitButton(hdc);
	DrawPlayersInfo(hdc);
	DrawAnswer(hdc);
	ChattingManager::GetInstance()->DrawChat(hdc);
}

void CatchMind::DrawInGameFrame(HDC hdc)
{
	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::IN_GAME_FRAME)->Draw(hdc, 342, 130);
}

void CatchMind::DrawBackground(HDC hdc)
{
	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::LOBY_BACK)->Draw(hdc, 0, 0, 2, 2);
}

void CatchMind::DrawPalette(HDC hdc)
{
	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::COLOR_BUTTON_BALCK)->Draw(hdc, 400, 500);
	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::COLOR_BUTTON_RED)->Draw(hdc, 435, 500);
	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::COLOR_BUTTON_BLUE)->Draw(hdc, 470, 500);
	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::COLOR_BUTTON_GREEN)->Draw(hdc, 505, 500);
	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::COLOR_BUTTON_YELLOW)->Draw(hdc, 540, 500);
	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::COLOR_BUTTON_WHITE)->Draw(hdc, 575, 500);

	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::ERASE_BUTTON)->Draw(hdc, 620, 500);
}

void CatchMind::DrawEraseAllButton(HDC hdc)
{
	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::ERASE_ALL_BUTTON)->Draw(hdc, 720, 500);
}

void CatchMind::DrawTimer(HDC hdc)
{
	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::TIMER_FRAME)->Draw(hdc, 380, 580);
}

void CatchMind::DrawPlayersInfo(HDC hdc)
{
	DrawPlayersInfoFrame(hdc);
	DrawAllPlayers(hdc);
}

void CatchMind::DrawPlayersInfoFrame(HDC hdc)
{
	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::PLAYER_INFO_FRAME)->Draw(hdc, 130, 150);
	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::PLAYER_INFO_FRAME)->Draw(hdc, 130, 270);
	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::PLAYER_INFO_FRAME)->Draw(hdc, 130, 390);
	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::PLAYER_INFO_FRAME)->Draw(hdc, 130, 510);

	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::PLAYER_INFO_FRAME)->Draw(hdc, 950, 150);
	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::PLAYER_INFO_FRAME)->Draw(hdc, 950, 270);
	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::PLAYER_INFO_FRAME)->Draw(hdc, 950, 390);
	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::PLAYER_INFO_FRAME)->Draw(hdc, 950, 510);
}

void CatchMind::DrawAllPlayers(HDC hdc)
{
	TCHAR nickName[128];
	TCHAR roomMaster[128];
	HFONT myFont = CreateFont(18, 0, 0, 0, 1000, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "Arial");
	HFONT oldFont = (HFONT)SelectObject(hdc, myFont);
	SetTextColor(hdc, RGB(8, 99, 165));
	//SetBkColor(hdc, RGB(206, 206, 206));

	int roomNum = LobbyManager::GetInstance()->GetRoomNum(playerIndex);

	for (int i = 0; i < MAX_ROOM_IN_NUM; i++)
	{
		if (LobbyManager::GetInstanceLock()->GetNickName(roomNum, i) != nullptr)
		{
			if (LobbyManager::GetInstanceLock()->GetKungyaNum(roomNum, i) != -1)
			{
				BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::KUNGYA_0 + LobbyManager::GetInstanceLock()->GetKungyaNum(roomNum, i))->Draw(hdc, 135 + (i % 2) * 820, 160 + (i / 2) * 120);
			}
			SetTextColor(hdc, RGB(8, 99, 165));
			SetBkColor(hdc, RGB(206, 206, 206));
			wsprintf(nickName, TEXT("%s"), LobbyManager::GetInstanceLock()->GetNickName(roomNum, i));
			TextOut(hdc, 230 + (i % 2) * 820, 172 + (i / 2) * 120, nickName, lstrlen(nickName));

			if (LobbyManager::GetInstance()->CheckIsRoomMaster(LobbyManager::GetInstance()->GetPlayerIndex(roomNum, i)))
			{
				SetTextColor(hdc, RGB(255, 0, 0));
				SetBkColor(hdc, RGB(123, 115, 140));
				wsprintf(roomMaster, TEXT("☆방장☆"));
				TextOut(hdc, 230 + (i % 2) * 820, 197 + (i / 2) * 120, roomMaster, lstrlen(roomMaster));
			}
		}
	}

	SetTextColor(hdc, RGB(0, 0, 0));
	SetBkColor(hdc, RGB(255, 255, 255));
	SelectObject(hdc, oldFont);
	DeleteObject(myFont);
}

void CatchMind::DrawKungyasToSelect(HDC hdc)
{
	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::KUNGYA_0)->Draw(hdc, 300, 300);
	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::KUNGYA_1)->Draw(hdc, 400, 300);
	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::KUNGYA_2)->Draw(hdc, 500, 300);
	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::KUNGYA_3)->Draw(hdc, 600, 300);
	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::KUNGYA_4)->Draw(hdc, 700, 300);
	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::KUNGYA_5)->Draw(hdc, 800, 300);

	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::KUNGYA_6)->Draw(hdc, 300, 400);
	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::KUNGYA_7)->Draw(hdc, 400, 400);
	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::KUNGYA_8)->Draw(hdc, 500, 400);
	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::KUNGYA_9)->Draw(hdc, 600, 400);
	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::KUNGYA_10)->Draw(hdc, 700, 400);
	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::KUNGYA_11)->Draw(hdc, 800, 400);
}

void CatchMind::DrawSelectedKungya(HDC hdc)
{
	if (!isSelectKungya)
		return;

	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::KUNGYA_SELECT_FRAME)->Draw(hdc, 300 + (kungyaNum % 6) * 100, 300 + (kungyaNum / 6) * 100);
}

void CatchMind::DrawLoginInfo(HDC hdc)
{
	TCHAR info[128];
	HFONT myFont = CreateFont(30, 0, 0, 0, 1000, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "Arial");
	HFONT oldFont = (HFONT)SelectObject(hdc, myFont);
	SetTextColor(hdc, RGB(255, 255, 255));
	SetBkColor(hdc, RGB(0, 91, 184));

	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::LOGIN_INFO_FRAME)->Draw(hdc, 375, 500, 3, 3);
	wsprintf(info, TEXT("쿵야를 선택하고 닉네임을 입력하세요!"));
	TextOut(hdc, 425, 525, info, lstrlen(info));

	SetTextColor(hdc, RGB(0, 0, 0));
	SetBkColor(hdc, RGB(255, 255, 255));
	SelectObject(hdc, oldFont);
	DeleteObject(myFont);
}

void CatchMind::DrawStartButton(HDC hdc)
{
	if (LobbyManager::GetInstance()->CheckIsRoomMaster(playerIndex))
	{
		BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::BUTTON_START)->Draw(hdc, START_BUTTON_POSITION_X, START_BUTTON_POSITION_Y);
	}
	else
	{
		BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::BUTTON_READY)->Draw(hdc, START_BUTTON_POSITION_X, START_BUTTON_POSITION_Y);
	}
}

void CatchMind::DrawRoomState(HDC hdc)
{
	TCHAR ready[128];
	HFONT myFont = CreateFont(18, 0, 0, 0, 1000, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "Arial");
	HFONT oldFont = (HFONT)SelectObject(hdc, myFont);
	SetTextColor(hdc, RGB(255, 0, 0));
	SetBkColor(hdc, RGB(123, 115, 140));

	int roomNum = LobbyManager::GetInstance()->GetRoomNum(playerIndex);
	for (int i = 0; i < MAX_ROOM_IN_NUM; i++)
	{
		if (LobbyManager::GetInstance()->CheckIsReady(roomNum, i))
		{
			wsprintf(ready, TEXT("Reday"));
			TextOut(hdc, 230 + (i % 2) * 820, 197 + (i / 2) * 120, ready, lstrlen(ready));
		}
	}

	SetTextColor(hdc, RGB(0, 0, 0));
	SetBkColor(hdc, RGB(255, 255, 255));
	SelectObject(hdc, oldFont);
	DeleteObject(myFont);
}

void CatchMind::DrawAnswer(HDC hdc)
{
	int roomNum = LobbyManager::GetInstance()->GetRoomNum(CatchMind::GetInstance()->playerIndex);

	TCHAR turnName[128];
	HFONT myFont = CreateFont(24, 0, 0, 0, 1000, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "Arial");
	HFONT oldFont = (HFONT)SelectObject(hdc, myFont);
	SetTextColor(hdc, RGB(255, 255, 255));
	SetBkColor(hdc, RGB(8, 123, 181));

	char turn[32];
	strcpy(turn, LobbyManager::GetInstance()->GetNickName(LobbyManager::GetInstance()->GetCurrentTurn(roomNum)));
	wsprintf(turnName, TEXT("%s님이 그리는 중"), turn);
	TextOut(hdc, 700, 580, turnName, lstrlen(turnName));

	SetTextColor(hdc, RGB(0, 0, 0));
	SetBkColor(hdc, RGB(255, 255, 255));
	SelectObject(hdc, oldFont);
	DeleteObject(myFont);

	if (LobbyManager::GetInstance()->GetCurrentTurn(roomNum) != CatchMind::GetInstance()->playerIndex)
		return;

	TCHAR answer[128];
	HFONT newMyFont = CreateFont(28, 0, 0, 0, 1000, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "Arial");
	HFONT newOldFont = (HFONT)SelectObject(hdc, newMyFont);
	SetTextColor(hdc, RGB(255, 255, 255));
	SetBkColor(hdc, RGB(8, 123, 181));

	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::ANSWER_WORD_FRAME)->Draw(hdc, 560, 60);

	char answerWord[32];
	strcpy(answerWord, LobbyManager::GetInstance()->GetAnswerWord(roomNum));
	wsprintf(answer, TEXT("%s"), answerWord);
	TextOut(hdc, 588, 65, answer, lstrlen(answer));

	SetTextColor(hdc, RGB(0, 0, 0));
	SetBkColor(hdc, RGB(255, 255, 255));
	SelectObject(hdc, newOldFont);
	DeleteObject(newMyFont);
}

bool CatchMind::CheckIsClickedStateButton(int x, int y)
{
	if (x > START_BUTTON_POSITION_X && x < START_BUTTON_POSITION_X + BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::BUTTON_START)->GetSize().cx
		&& y > START_BUTTON_POSITION_Y && y < START_BUTTON_POSITION_Y + BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::BUTTON_START)->GetSize().cy)
	{
		int roomNum = LobbyManager::GetInstance()->GetRoomNum(playerIndex);
		if (LobbyManager::GetInstance()->CheckIsRoomMaster(playerIndex))
		{
			if (LobbyManager::GetInstance()->CheckCanStart(roomNum, playerIndex))
			{
				bool isStart = true;
				//LobbyManager::GetInstanceLock()->SetIsStart(roomNum, isStart);
				NetworkManager::GetInstance()->SendRoomState(roomNum, playerIndex, true, isStart);
			}
		}
		else
		{
			if (!isReady)
			{
				isReady = true;
				NetworkManager::GetInstance()->SendRoomState(roomNum, playerIndex, isReady);
			}
			/*else
			{
				isReady = true;
				NetworkManager::GetInstance()->SendRoomState(roomNum, playerIndex, isReady);
			}*/
		}
		return true;
	}
	return false;
}

void CatchMind::CheckIsClickedBackButton(int x, int y)
{
	if (x > BACK_BUTTON_POSITION_X && x < BACK_BUTTON_POSITION_X + BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::BUTTON_BACK)->GetSize().cx
		&& y > BACK_BUTTON_POSITION_Y && y < BACK_BUTTON_POSITION_Y + BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::BUTTON_BACK)->GetSize().cy)
	{
		sceneState = SCENE_STATE::LOBY_SCENE;
		LobbyManager::GetInstance()->ActivateCreateRoom();
		isReady = false;
		int roomNum = LobbyManager::GetInstance()->GetRoomNum(playerIndex);
		NetworkManager::GetInstance()->SendBackToLobby(roomNum, playerIndex);
		SketchBook::GetInstance()->CleanSketchBook();
	}
}

void CatchMind::CheckIsClickedKungya(int x, int y)
{
	if (x > 300 && x < 300 + KUNGYA_SIZE && y > 300 && y < 300 + KUNGYA_SIZE)
	{
		isSelectKungya = true;
		kungyaNum = 0;
		
	}
	else if (x > 400 && x < 400 + KUNGYA_SIZE && y > 300 && y < 300 + KUNGYA_SIZE)
	{
		isSelectKungya = true;
		kungyaNum = 1;
	}
	else if (x > 500 && x < 500 + KUNGYA_SIZE && y > 300 && y < 300 + KUNGYA_SIZE)
	{
		isSelectKungya = true;
		kungyaNum = 2;
	}
	else if (x > 600 && x < 600 + KUNGYA_SIZE && y > 300 && y < 300 + KUNGYA_SIZE)
	{
		isSelectKungya = true;
		kungyaNum = 3;
	}
	else if (x > 700 && x < 700 + KUNGYA_SIZE && y > 300 && y < 300 + KUNGYA_SIZE)
	{
		isSelectKungya = true;
		kungyaNum = 4;
	}
	else if (x > 800 && x < 800 + KUNGYA_SIZE && y > 300 && y < 300 + KUNGYA_SIZE)
	{
		isSelectKungya = true;
		kungyaNum = 5;
	}
	else if (x > 300 && x < 300 + KUNGYA_SIZE && y > 400 && y < 400 + KUNGYA_SIZE)
	{
		isSelectKungya = true;
		kungyaNum = 6;
	}
	else if (x > 400 && x < 400 + KUNGYA_SIZE && y > 400 && y < 400 + KUNGYA_SIZE)
	{
		isSelectKungya = true;
		kungyaNum = 7;
	}
	else if (x > 500 && x < 500 + KUNGYA_SIZE && y > 400 && y < 400 + KUNGYA_SIZE)
	{
		isSelectKungya = true;
		kungyaNum = 8;
	}
	else if (x > 600 && x < 600 + KUNGYA_SIZE && y > 400 && y < 400 + KUNGYA_SIZE)
	{
		isSelectKungya = true;
		kungyaNum = 9;
	}
	else if (x > 700 && x < 700 + KUNGYA_SIZE && y > 400 && y < 400 + KUNGYA_SIZE)
	{
		isSelectKungya = true;
		kungyaNum = 10;
	}
	else if (x > 800 && x < 800 + KUNGYA_SIZE && y > 400 && y < 400 + KUNGYA_SIZE)
	{
		isSelectKungya = true;
		kungyaNum = 11;
	}
}

void CatchMind::CheckIsClickedPalette(int x, int y, int mouseState)
{
	if (CatchMind::GetInstance()->GetSceneState() == SCENE_STATE::INGAME_SCENE)
	{
		int roomNum = LobbyManager::GetInstance()->GetRoomNum(CatchMind::GetInstance()->playerIndex);
		if (LobbyManager::GetInstance()->GetCurrentTurn(roomNum) != CatchMind::GetInstance()->playerIndex)
			return;
	}

	if (mouseState != MOUSE_STATE::LCLICK_DOWN)
		return;

	if (x > 400 && x < 400 + PALETTE_SIZE && y > 500 && y < 500 + PALETTE_SIZE)
	{
		SketchBook::GetInstance()->SetColor({ 0, 0, 0 });
	}
	else if (x > 435 && x < 435 + PALETTE_SIZE && y > 500 && y < 500 + PALETTE_SIZE)
	{
		SketchBook::GetInstance()->SetColor({ 255, 24, 66 });
	}
	else if (x > 470 && x < 470 + PALETTE_SIZE && y > 500 && y < 500 + PALETTE_SIZE)
	{
		SketchBook::GetInstance()->SetColor({ 66, 148, 231 });
	}
	else if (x > 505 && x < 505 + PALETTE_SIZE && y > 500 && y < 500 + PALETTE_SIZE)
	{
		SketchBook::GetInstance()->SetColor({ 132, 165, 33 });
	}
	else if (x > 540 && x < 540 + PALETTE_SIZE && y > 500 && y < 500 + PALETTE_SIZE)
	{
		SketchBook::GetInstance()->SetColor({ 255, 206, 33 });
	}
	else if (x > 575 && x < 575 + PALETTE_SIZE && y > 500 && y < 500 + PALETTE_SIZE)
	{
		SketchBook::GetInstance()->SetColor({ 255, 255, 255 });
	}
	else if (x > 620 && x < 620 + 39 && y > 500 && y < 500 + 23)
	{
		SketchBook::GetInstance()->SetColor({ 255, 255, 255 });
	}
}

void CatchMind::CheckIsCliekedEraseAll(int x, int y, int mouseState)
{
	if (CatchMind::GetInstance()->GetSceneState() == SCENE_STATE::INGAME_SCENE)
	{
		int roomNum = LobbyManager::GetInstance()->GetRoomNum(CatchMind::GetInstance()->playerIndex);
		if (LobbyManager::GetInstance()->GetCurrentTurn(roomNum) != CatchMind::GetInstance()->playerIndex)
			return;
	}

	if (mouseState != MOUSE_STATE::LCLICK_DOWN)
		return;

	if (x > 720 && x < 720 + 84 && y > 500 && y < 500 + 29)
	{
		NetworkManager::GetInstance()->SendEraseAllToServer(LobbyManager::GetInstance()->GetRoomNum(playerIndex));
	}
}

void CatchMind::CheckStart()
{
	int roomNum = LobbyManager::GetInstance()->GetRoomNum(playerIndex);
	if (LobbyManager::GetInstance()->GetIsStart(roomNum))
	{
		if (LobbyManager::GetInstance()->CheckIsRoomMaster(playerIndex))
		{
			//curTurn = -1;
		}
		else
		{
			//curTurn = playerIndex;
		}
		sceneState = SCENE_STATE::INGAME_SCENE;
	}
}

void CatchMind::LoginInput()
{
	if ((GetAsyncKeyState(VK_RETURN) & 0x0001) && isSelectKungya)
	{
		int playerIndex = CatchMind::GetInstance()->playerIndex;
		int roomNum = LobbyManager::GetInstance()->GetRoomNum(playerIndex);
		NetworkManager::GetInstance()->SendLoginToServer(playerIndex, nickName, kungyaNum);
		SetSeceneState(SCENE_STATE::LOBY_SCENE);
		ShowWindow(hLoginEidt, SW_HIDE);
		ShowWindow(ChattingManager::GetInstance()->hChat, SW_SHOW);
		ShowWindow(ChattingManager::GetInstance()->hChatList, SW_SHOW);
		SetFocus(ChattingManager::GetInstance()->hChat);
		SetWindowText(hLoginEidt, "");
	}
	else
	{
		GetWindowText(hLoginEidt, nickName, 32);
	}
}

void CatchMind::InitLogin()
{
	if (hLoginEidt != nullptr)
		return;
	
	hLoginEidt = CreateWindow("edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL | ES_WANTRETURN, 480, 600, 220, 20, hWnd, (HMENU)ID_EDIT_0, hInstance, NULL);
	SetFocus(hLoginEidt);
}

CatchMind::~CatchMind()
{
}

void CatchMind::Init(HWND hWnd, HINSTANCE g_hInst)
{
	lastTime = std::chrono::system_clock::now();
	playerIndex = 0;
	this->hWnd = hWnd;
	hInstance = g_hInst;
	hLoginEidt = nullptr;
	HDC hdc = GetDC(hWnd);
	reStartTime = 0.0f;
	isSelectKungya = false;
	isReady = false;
	kungyaNum = -1;

	gameDC = CreateCompatibleDC(hdc);
	hBitmap = CreateCompatibleBitmap(hdc, INGAME_WIDTH, INGAME_HEIGHT);
	hOldBitmap = (HBITMAP)SelectObject(gameDC, hBitmap);

	BitMapManager::GetInstance()->Init(gameDC);
	LobbyManager::GetInstance()->Init(hWnd, g_hInst);
	SketchBook::GetInstance()->Init();

	sceneState = SCENE_STATE::LOGIN_SCENE;

	ReleaseDC(hWnd, hdc);
}

void CatchMind::Update()
{
	std::chrono::duration<float> sec = std::chrono::system_clock::now() - lastTime;
	if (sec.count() < (1 / FPS))
		return;

	elapseTime = sec.count();

	switch (sceneState)
	{
	case SCENE_STATE::LOGIN_SCENE:
		InitLogin();
		LoginInput();
		break;

	case SCENE_STATE::LOBY_SCENE:
		ChattingManager::GetInstance()->Input();
		LobbyManager::GetInstance()->Update();
		break;

	case SCENE_STATE::READY_SCENE:
		ChattingManager::GetInstance()->Input();
		CheckStart();
		break;

	case SCENE_STATE::START_SCENE:
		//ChattingManager::GetInstance()->Input();
		break;

	case SCENE_STATE::INGAME_SCENE:
		ChattingManager::GetInstance()->Input();
		break;

	case SCENE_STATE::RESULT_SCENE:
		//ChattingManager::GetInstance()->Input();
		break;
	}

	Render();

	lastTime = std::chrono::system_clock::now();
}

void CatchMind::Render()
{
	HDC hdc = GetDC(hWnd);

	switch (sceneState)
	{
	case SCENE_STATE::LOGIN_SCENE:
		DrawLogin(gameDC);
		DrawSelectedKungya(gameDC);
		break;

	case SCENE_STATE::LOBY_SCENE:
		LobbyManager::GetInstanceLock()->Render(gameDC);
		break;

	case SCENE_STATE::READY_SCENE:
		DrawInRoom(gameDC);
		SketchBook::GetInstanceLock()->Render(gameDC);
		break;

	case SCENE_STATE::START_SCENE:
		break;

	case SCENE_STATE::INGAME_SCENE:
		DrawInGame(gameDC);
		SketchBook::GetInstanceLock()->Render(gameDC);
		break;

	case SCENE_STATE::RESULT_SCENE:
		break;
	}

	BitBlt(hdc, 0, 0, INGAME_WIDTH, INGAME_HEIGHT, gameDC, 0, 0, SRCCOPY);

	ReleaseDC(hWnd, hdc);
}

void CatchMind::Release()
{
	BitMapManager::GetInstance()->Release();
	BitMapManager::FreeInstance();
	LobbyManager::GetInstance()->Release();
	LobbyManager::FreeInstance();
	ChattingManager::FreeInstance();
	SketchBook::GetInstance()->Release();
	SketchBook::FreeInstance();
}

void CatchMind::MouseInput(int x, int y, int mouseState)
{
	cursor = { x, y };

	switch (sceneState)
	{
	case SCENE_STATE::LOGIN_SCENE:
		CheckIsClickedKungya(cursor.x, cursor.y);
		break;

	case SCENE_STATE::LOBY_SCENE:
		LobbyManager::GetInstance()->CheckIsClickedRoomCB(cursor.x, cursor.y);
		LobbyManager::GetInstance()->CheckIsClickedRoom(cursor.x, cursor.y);
		break;

	case SCENE_STATE::READY_SCENE:
		CheckIsClickedStateButton(cursor.x, cursor.y);
		CheckIsClickedBackButton(cursor.x, cursor.y);
		CheckIsClickedPalette(cursor.x, cursor.y, mouseState);
		CheckIsCliekedEraseAll(cursor.x, cursor.y, mouseState);
		SketchBook::GetInstance()->MouseInput(cursor.x, cursor.y, mouseState);
		break;

	case SCENE_STATE::START_SCENE:
		break;

	case SCENE_STATE::INGAME_SCENE:
		CheckIsClickedBackButton(cursor.x, cursor.y);
		CheckIsClickedPalette(cursor.x, cursor.y, mouseState);
		CheckIsCliekedEraseAll(cursor.x, cursor.y, mouseState);
		SketchBook::GetInstance()->MouseInput(cursor.x, cursor.y, mouseState);
		break;

	case SCENE_STATE::RESULT_SCENE:
		break;
	}
}

void CatchMind::SetSeceneState(SCENE_STATE newState)
{
	sceneState = newState;
}

void CatchMind::DrawBackButton(HDC hdc)
{
	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::BUTTON_BACK)->Draw(hdc, BACK_BUTTON_POSITION_X, BACK_BUTTON_POSITION_Y);
}

void CatchMind::DrawExitButton(HDC hdc)
{
	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::EXIT_ICON)->Draw(hdc, BACK_BUTTON_POSITION_X + 50, BACK_BUTTON_POSITION_Y);
}

void CatchMind::DrawDockBar(HDC hdc)
{
	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::DOCK_BAR)->Draw(hdc, 0, DOCK_BAR_POSITION, 2, 1);
}