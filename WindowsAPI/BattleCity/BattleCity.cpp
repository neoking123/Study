#include "BattleCity.h"
#include "BitMapManager.h"
#include "Tank.h"
#include "PlayerInputComponent.h"
#include "Tile.h"
#include "Enemy.h"
#include "EnemyInputComponent.h"

BattleCity* BattleCity::pInstance = nullptr;

void BattleCity::LoadMap(string fileName)
{
	ifstream inFile(fileName);
	string readString;
	stringstream ss;
	int tileWidth;
	int tileHeight;

	getline(inFile, readString);
	ss.str(readString);
	ss >> tileWidth;
	ss.clear();

	getline(inFile, readString);
	ss.str(readString);
	ss >> tileHeight;

	char* tok = nullptr;

	for (int y = 0; y < tileHeight; y++)
	{
		getline(inFile, readString);
		tok = strtok((char*)readString.c_str(), ","); // ","를 제외하고 읽어들임
		while (tok != nullptr)
		{
			for (int x = 0; x < tileWidth; x++)
			{
				tiles[y][x] = atoi(tok);
				tok = strtok(nullptr, ",");
			}
		}
	}

	CreateTile();
}

void BattleCity::DrawTiles()
{
	for (auto iter = tileVec.begin(); iter != tileVec.end(); iter++)
	{
		if ((*iter)->tag != "tile_tree")
		{
			(*iter)->Render(gameDC);
		}
	}
}

void BattleCity::DrawTreeTiles()
{
	for (auto iter = tileVec.begin(); iter != tileVec.end(); iter++)
	{
		if ((*iter)->tag == "tile_tree")
		{
			(*iter)->Render(gameDC);
		}
	}
}

void BattleCity::DrawBackground()
{
	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::BACK_GREY)->Draw(gameDC, 0, 0);
	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::BACK_BLACK)->Draw(gameDC, MAP_MARGINE_WIDTH, MAP_MARGINE_HEIGHT);
}

void BattleCity::CreateTile()
{
	for (int y = 0; y < TILE_HEIGHT_NUM; y++)
	{
		for (int x = 0; x < TILE_WIDTH_NUM; x++)
		{
			if (tiles[y][x] != BITMAP_RES::BLOCK_15)
			{
				Tile* newTile = new Tile();

				if (tiles[y][x] == BITMAP_RES::BLOCK_0 || tiles[y][x] == BITMAP_RES::BLOCK_1
					|| tiles[y][x] == BITMAP_RES::BLOCK_2 || tiles[y][x] == BITMAP_RES::BLOCK_3 || tiles[y][x] == BITMAP_RES::BLOCK_4)
				{
					newTile->Init(nullptr, x * TILE_SIZE + MAP_MARGINE_WIDTH, y * TILE_SIZE + MAP_MARGINE_HEIGHT, "tile_brick", tiles[y][x]);
				}
				else if (tiles[y][x] == BITMAP_RES::BLOCK_5)
				{
					newTile->Init(nullptr, x * TILE_SIZE + MAP_MARGINE_WIDTH, y * TILE_SIZE + MAP_MARGINE_HEIGHT, "tile_grey", tiles[y][x]);
				}
				else if (tiles[y][x] == BITMAP_RES::BLOCK_6)
				{
					newTile->Init(nullptr, x * TILE_SIZE + MAP_MARGINE_WIDTH, y * TILE_SIZE + MAP_MARGINE_HEIGHT, "tile_tree", tiles[y][x]);
				}
				else if (tiles[y][x] == BITMAP_RES::BLOCK_7)
				{
					newTile->Init(nullptr, x * TILE_SIZE + MAP_MARGINE_WIDTH, y * TILE_SIZE + MAP_MARGINE_HEIGHT, "tile_water", tiles[y][x]);
				}
				else if (tiles[y][x] == BITMAP_RES::BLOCK_8 || tiles[y][x] == BITMAP_RES::BLOCK_9
					|| tiles[y][x] == BITMAP_RES::BLOCK_10 || tiles[y][x] == BITMAP_RES::BLOCK_11 || tiles[y][x] == BITMAP_RES::BLOCK_12)
				{
					newTile->Init(nullptr, x * TILE_SIZE + MAP_MARGINE_WIDTH, y * TILE_SIZE + MAP_MARGINE_HEIGHT, "tile_iron", tiles[y][x]);
				}
				else if (tiles[y][x] == BITMAP_RES::BLOCK_13)
				{
					newTile->Init(nullptr, x * TILE_SIZE + MAP_MARGINE_WIDTH, y * TILE_SIZE + MAP_MARGINE_HEIGHT, "tile_egle", tiles[y][x]);
				}
				else if (tiles[y][x] == BITMAP_RES::BLOCK_14)
				{
					newTile->Init(nullptr, x * TILE_SIZE + MAP_MARGINE_WIDTH, y * TILE_SIZE + MAP_MARGINE_HEIGHT, "tile_flag", tiles[y][x]);
				}

				tileVec.push_back(newTile);
			}
		}
	}

}

void BattleCity::SpawnEnemy(float elapseTime)
{
	if (spawnTime < 1.0f)
	{
		spawnTime += elapseTime;
		return;
	}
	spawnTime = 0.0f;

	if (spawnEnemyNum >= MAX_ENEMY_NUM)
		return;

	if (enemys.size() >= MAX_SPAWN_NUM)
		return;

	if (spawnPointNum >= 12)
	{
		spawnPointNum = 0;
	}
	else
	{
		spawnPointNum += 6;
	}

	RECT spawnBox = { spawnPointNum * TILE_SIZE + MAP_MARGINE_WIDTH, 0 * TILE_SIZE + MAP_MARGINE_HEIGHT, 
		spawnPointNum * TILE_SIZE + MAP_MARGINE_WIDTH + 30, 0 * TILE_SIZE + MAP_MARGINE_HEIGHT + 30 };
	RECT rt;

	for (auto iter = tanks.begin(); iter != tanks.end(); iter++)
	{
		if (IntersectRect(&rt, &spawnBox, &(*iter)->phsics.GetColliderBox()))
		{
			return;
		}
	}
	
	EnemyInputComponent* enemyInput = new EnemyInputComponent();
	enemyInputs.push_back(enemyInput);

	Enemy* enemy = new Enemy();
	enemy->Init(enemyInputs.back(), spawnPointNum * TILE_SIZE + MAP_MARGINE_WIDTH, 0 * TILE_SIZE + MAP_MARGINE_HEIGHT, "enemy");
	enemys.push_back(enemy);
	tanks.push_back(enemy);
	spawnEnemyNum++;
}

void BattleCity::DrawRemainEnemyNum(HDC hdc)
{
	int iconNum = MAX_SPAWN_NUM - enemys.size();
	for (int i = 0; i < iconNum; i++)
	{
		BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::ENERMY_ICON)->Draw(gameDC, (18 * (i % 2)) + 14 * TILE_SIZE + MAP_MARGINE_WIDTH, (18 * (i / 2)) + 1 * TILE_SIZE + MAP_MARGINE_HEIGHT);
	}
}

void BattleCity::CheckWin(float elapseTime)
{
	if (spawnEnemyNum == 0 && enemys.size() == MAX_SPAWN_NUM)
	{
		if (stageChangeTime < 1.0f)
		{
			stageChangeTime += elapseTime;
			return;
		}
		stageChangeTime = 0.0f;
		sceneState = SCENE_STATE::SCORE_SCENE;
	}
}

void BattleCity::CheckGameOver(float elapseTime)
{
	if ((lifeCount == 0 && player->isDead == true) || isDestroyedEgle == true)
	{
		if (stageChangeTime < 1.0f)
		{
			stageChangeTime += elapseTime;
			return;
		}
		stageChangeTime = 0.0f;
		sceneState = SCENE_STATE::GAMEOVER_SCENE;

		isFisrtInit = true;
	}
}

void BattleCity::DrawLifeCount(HDC hdc)
{
	TCHAR info[128];
	TCHAR lifeCountStr[128];
	SetBkColor(hdc, RGB(127, 127, 127));
	HFONT myFont = CreateFont(24, 0, 0, 0, 1000, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "Arial");
	HFONT oldFont = (HFONT)SelectObject(hdc, myFont);
	SetTextColor(hdc, RGB(0, 0, 0));

	wsprintf(info, TEXT("1P"));
	wsprintf(lifeCountStr, TEXT("%d"), lifeCount);
	TextOut(hdc, 14 * TILE_SIZE + MAP_MARGINE_WIDTH, 8 + 7 * TILE_SIZE + MAP_MARGINE_HEIGHT, info, lstrlen(info));
	TextOut(hdc, -8 + 15 * TILE_SIZE + MAP_MARGINE_WIDTH, -4 + 8 * TILE_SIZE + MAP_MARGINE_HEIGHT, lifeCountStr, lstrlen(lifeCountStr));

	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::PLAYER_ICON)->Draw(gameDC, 14 * TILE_SIZE + MAP_MARGINE_WIDTH, 8 * TILE_SIZE + MAP_MARGINE_HEIGHT);

	SetTextColor(hdc, RGB(0, 0, 0));
	SelectObject(hdc, oldFont);
	SetBkColor(hdc, RGB(255, 255, 255));
	DeleteObject(myFont);
}

void BattleCity::DrawStageFlag(HDC hdc)
{
	TCHAR stageNum[128];
	SetBkColor(hdc, RGB(127, 127, 127));
	HFONT myFont = CreateFont(24, 0, 0, 0, 1000, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "Arial");
	HFONT oldFont = (HFONT)SelectObject(hdc, myFont);
	SetTextColor(hdc, RGB(0, 0, 0));

	wsprintf(stageNum, TEXT("%d"), currentStage);
	TextOut(hdc, -8 + 15 * TILE_SIZE + MAP_MARGINE_WIDTH, 8 + 11 * TILE_SIZE + MAP_MARGINE_HEIGHT, stageNum, lstrlen(stageNum));

	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::STAGE_ICON)->Draw(gameDC, 14 * TILE_SIZE + MAP_MARGINE_WIDTH, 16 + 10 * TILE_SIZE + MAP_MARGINE_HEIGHT);

	SetTextColor(hdc, RGB(0, 0, 0));
	SelectObject(hdc, oldFont);
	SetBkColor(hdc, RGB(255, 255, 255));
	DeleteObject(myFont);
}

void BattleCity::UpdateEnemys(float elapseTime)
{
	for (auto iter = enemys.begin(); iter != enemys.end(); iter++)
	{
		(*iter)->Update(elapseTime);
	}
}

void BattleCity::UpdateTileEgle(float elapseTime)
{
	for (auto iter = tileVec.begin(); iter != tileVec.end(); iter++)
	{
		if ((*iter)->tag == "tile_egle")
		{
			(*iter)->Update(elapseTime);
		}
	}
}

void BattleCity::RenderEnemys(HDC hdc)
{
	for (auto iter = enemys.begin(); iter != enemys.end(); iter++)
	{
		(*iter)->Render(gameDC);
	}
}

void BattleCity::DrawScoreScene(HDC hdc)
{
	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::SCORE)->Draw(gameDC, 0, 0);

	TCHAR stageNum[128];
	TCHAR KillCount[128];
	TCHAR scoreCount[128];
	TCHAR playerScore[128];
	SetBkColor(hdc, RGB(0, 0, 0));
	HFONT myFont = CreateFont(24, 0, 0, 0, 1000, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "Arial");
	HFONT oldFont = (HFONT)SelectObject(hdc, myFont);
	SetTextColor(hdc, RGB(255, 255, 255));

	wsprintf(stageNum, TEXT("%d"), currentStage);
	wsprintf(KillCount, TEXT("%d"), scoreKillCount);
	wsprintf(scoreCount, TEXT("%d"), this->scoreCount);
	wsprintf(playerScore, TEXT("%d"), 2000);

	TextOut(hdc, 310, 58, stageNum, lstrlen(stageNum));
	TextOut(hdc, 210, 175, KillCount, lstrlen(KillCount));
	TextOut(hdc, 80, 175, scoreCount, lstrlen(scoreCount));

	SetTextColor(hdc, RGB(255, 160, 0));
	TextOut(hdc, 150, 130, playerScore, lstrlen(playerScore));

	SetTextColor(hdc, RGB(0, 0, 0));
	SelectObject(hdc, oldFont);
	SetBkColor(hdc, RGB(255, 255, 255));
	DeleteObject(myFont);
}

BattleCity::BattleCity()
{
}


BattleCity::~BattleCity()
{
}

void BattleCity::Init(HWND hWnd)
{
	lastTime = std::chrono::system_clock::now();

	this->hWnd = hWnd;
	HDC hdc = GetDC(hWnd);

	gameDC = CreateCompatibleDC(hdc);
	hBitmap = CreateCompatibleBitmap(hdc, SCREEN_WIDE, SCREEN_HEIGHT);
	hOldBitmap = (HBITMAP)SelectObject(gameDC, hBitmap);

	BitMapManager::GetInstance()->Init(gameDC);

	isFisrtInit = true;
	sceneState = SCENE_STATE::MAIN_SCENE;
	currentStage = 1;
	stageChangeTime = 0.0f;

	ReleaseDC(hWnd, hdc);
}

void BattleCity::ReInit()
{
	if(player != nullptr)
		player->Release();
	SAFE_DELETE(player);
	SAFE_DELETE(playerInput);

	for (auto iter = enemys.begin(); iter != enemys.end(); iter++)
	{
		(*iter)->Release();
		SAFE_DELETE(*iter);
	}
	enemys.clear();
	tanks.clear();

	for (auto iter = enemyInputs.begin(); iter != enemyInputs.end(); iter++)
	{
		SAFE_DELETE(*iter);
	}
	enemyInputs.clear();

	for (auto iter = tileVec.begin(); iter != tileVec.end(); iter++)
	{
		SAFE_DELETE(*iter);
	}
	tileVec.clear();


	if (currentStage == 1)
	{
		lifeCount = 2;
		LoadMap(STAGE1);
	}
	else if (currentStage == 2)
	{
		LoadMap(STAGE2);
	}
	
	stageChangeTime = 0.0f;

	playerInput = new PlayerInputComponent();

	player = new Tank();
	player->Init(playerInput, 4 * TILE_SIZE + MAP_MARGINE_WIDTH, 12 * TILE_SIZE + MAP_MARGINE_HEIGHT, "player");
	tanks.push_back(player);

	spawnPointNum = 0;
	spawnTime = 0.0f;
	spawnEnemyNum = 0;
	killCount = 0;
	scoreKillCount = 0;
	scoreCount = 0;
	scoreSceneTime = 0.0f;
	isDestroyedEgle = false;
}

void BattleCity::Update()
{
	std::chrono::duration<float> sec = std::chrono::system_clock::now() - lastTime;
	if (sec.count() < (1 / FPS))
		return;

	elapseTime = sec.count();

	switch (sceneState)
	{
	case SCENE_STATE::MAIN_SCENE:
		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			sceneState = SCENE_STATE::STAGE_SCENE;
		}
		break;

	case SCENE_STATE::STAGE_SCENE:
		if (stageChangeTime < 1.0f)
		{
			stageChangeTime += elapseTime;
			break;
		}

		if (isFisrtInit)
		{
			ReInit();
			isFisrtInit = false;
		}

		stageChangeTime = 0.0f;
		sceneState = SCENE_STATE::INGAME_SCENE;
		break;

	case SCENE_STATE::INGAME_SCENE:
		player->Update(elapseTime);
		SpawnEnemy(elapseTime);
		UpdateEnemys(elapseTime);
		UpdateTileEgle(elapseTime);
		CheckWin(elapseTime);
		CheckGameOver(elapseTime);
		break;

	case SCENE_STATE::GAMEOVER_SCENE:
		UpdateEnemys(elapseTime);

		if (stageChangeTime < 2.0f)
		{
			stageChangeTime += elapseTime;
			break;
		}
		stageChangeTime = 0.0f;
		sceneState = SCENE_STATE::MAIN_SCENE;
		currentStage = 1;
		break;

	case SCENE_STATE::SCORE_SCENE:

		if (scoreSceneTime < 0.05f)
		{
			scoreSceneTime += elapseTime;
			break;
		}
		else if(scoreSceneTime < 1.0f)
		{
			scoreSceneTime = 0.0f;
			scoreKillCount++;
			scoreCount = scoreKillCount * 100;
			if (scoreKillCount == MAX_SPAWN_NUM)
			{
				scoreSceneTime = 2.0f;
			}
		}

		if (stageChangeTime < 2.0f)
		{
			stageChangeTime += elapseTime;
			break;
		}

		stageChangeTime = 0.0f;
		if (currentStage == 1)
		{
			isFisrtInit = true;
			currentStage = 2;
			sceneState = SCENE_STATE::STAGE_SCENE;
		}
		else if (currentStage == 2)
		{
			isFisrtInit = true;
			currentStage = 1;
			sceneState = SCENE_STATE::MAIN_SCENE;
		}

		break;
	}

	Render();

	lastTime = std::chrono::system_clock::now();
}

void BattleCity::Release()
{
	if (player != nullptr)
		player->Release();
	SAFE_DELETE(player);
	SAFE_DELETE(playerInput);

	for (auto iter = enemys.begin(); iter != enemys.end(); iter++)
	{
		(*iter)->Release();
		SAFE_DELETE(*iter);
	}
	enemys.clear();
	tanks.clear();

	for (auto iter = enemyInputs.begin(); iter != enemyInputs.end(); iter++)
	{
		SAFE_DELETE(*iter);
	}
	enemyInputs.clear();

	for (auto iter = tileVec.begin(); iter != tileVec.end(); iter++)
	{
		SAFE_DELETE(*iter);
	}
	tileVec.clear();

	BitMapManager::GetInstance()->Release();
	SelectObject(gameDC, hOldBitmap);
	DeleteObject(hBitmap);
	DeleteDC(gameDC);
}

void BattleCity::Render()
{
	HDC hdc = GetDC(hWnd);

	switch (sceneState)
	{
	case SCENE_STATE::MAIN_SCENE:
		BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::MAIN)->Draw(gameDC, 0, 0);
		break;

	case SCENE_STATE::STAGE_SCENE:
		if (currentStage == 1)
		{
			BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::STAGE_1)->Draw(gameDC, 0, 0);
		}
		else if (currentStage == 2)
		{
			BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::STAGE_2)->Draw(gameDC, 0, 0);
		}
		
		break;

	case SCENE_STATE::INGAME_SCENE:
		DrawBackground();
		DrawTiles();
		DrawRemainEnemyNum(gameDC);
		DrawLifeCount(gameDC);
		DrawStageFlag(gameDC);
		player->Render(gameDC);
		RenderEnemys(gameDC);
		DrawTreeTiles();
		break;

	case SCENE_STATE::GAMEOVER_SCENE:
		DrawBackground();
		DrawTiles();
		DrawRemainEnemyNum(gameDC);
		DrawLifeCount(gameDC);
		DrawStageFlag(gameDC);
		player->Render(gameDC);
		RenderEnemys(gameDC);
		DrawTreeTiles();
		BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::GAMEOVER)->Draw(gameDC, 16 + 5 * TILE_SIZE + MAP_MARGINE_WIDTH, -16 + 7 * TILE_SIZE + MAP_MARGINE_HEIGHT);
		break;

	case SCENE_STATE::SCORE_SCENE:
		DrawScoreScene(gameDC);
		break;
	}

	BitBlt(hdc, 0, 0, SCREEN_WIDE, SCREEN_HEIGHT, gameDC, 0, 0, SRCCOPY);

	ReleaseDC(hWnd, hdc);
}

vector<Tile*> BattleCity::GetTiles()
{
	return tileVec;
}

vector<Tank*> BattleCity::GetTanks()
{
	return tanks;
}

void BattleCity::DecreaseEnemyNum()
{
	spawnEnemyNum--;
	killCount++;
}

void BattleCity::DestroyEgle()
{
	isDestroyedEgle = true;
}

int BattleCity::GetLifeCount()
{
	return lifeCount;
}

void BattleCity::LoseLife()
{
	lifeCount--;
}
