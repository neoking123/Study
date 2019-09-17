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
		(*iter)->Render(gameDC);
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
	if (spawnTime < 1.5f)
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

void BattleCity::CheckWin()
{
	if (spawnEnemyNum == 0 && enemys.size() == MAX_SPAWN_NUM)
	{
		int a = 0;
		int b = 0;
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
	wsprintf(lifeCountStr, TEXT("%d"), player->lifeCount);
	TextOut(hdc, 14 * TILE_SIZE + MAP_MARGINE_WIDTH, 8 + 7 * TILE_SIZE + MAP_MARGINE_HEIGHT, info, lstrlen(info));
	TextOut(hdc, -8 + 15 * TILE_SIZE + MAP_MARGINE_WIDTH, -4 + 8 * TILE_SIZE + MAP_MARGINE_HEIGHT, lifeCountStr, lstrlen(lifeCountStr));

	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::PLAYER_ICON)->Draw(gameDC, 14 * TILE_SIZE + MAP_MARGINE_WIDTH, 8 * TILE_SIZE + MAP_MARGINE_HEIGHT);

	SetTextColor(hdc, RGB(0, 0, 0));
	SelectObject(hdc, oldFont);
	SetBkColor(hdc, RGB(255, 255, 255));
	DeleteObject(myFont);
}

void BattleCity::DrawFlag(HDC hdc)
{
	if (!isDestroyedEgle)
		return;
	BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::BLOCK_14)->Draw(gameDC, 6 * TILE_SIZE + MAP_MARGINE_WIDTH, 12 * TILE_SIZE + MAP_MARGINE_HEIGHT);
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
	LoadMap("Maps\\Stage1.txt");

	playerInput = new PlayerInputComponent();

	player = new Tank();
	player->Init(playerInput, 4 * TILE_SIZE + MAP_MARGINE_WIDTH, 12 * TILE_SIZE + MAP_MARGINE_HEIGHT, "player");
	tanks.push_back(player);

	spawnPointNum = 0;
	spawnTime = 0.0f;
	spawnEnemyNum = 0;
	killCount = 0;
	isDestroyedEgle = false;

	ReleaseDC(hWnd, hdc);
}

void BattleCity::Update()
{
	std::chrono::duration<float> sec = std::chrono::system_clock::now() - lastTime;
	if (sec.count() < (1 / FPS))
		return;

	elapseTime = sec.count();
	

	player->Update(elapseTime);

	SpawnEnemy(elapseTime);

	for (auto iter = enemys.begin(); iter != enemys.end(); iter++)
	{
		(*iter)->Update(elapseTime);
	}
	
	for (auto iter = tileVec.begin(); iter != tileVec.end(); iter++)
	{
		if ((*iter)->tag == "tile_egle")
		{
			(*iter)->Update(elapseTime);
		}
	}

	Render();
	CheckWin();

	lastTime = std::chrono::system_clock::now();
}

void BattleCity::Release()
{
	player->Release();
	SAFE_DELETE(player);
	SAFE_DELETE(playerInput);

	for (auto iter = enemys.begin(); iter != enemys.end(); iter++)
	{
		(*iter)->Release();
		SAFE_DELETE(*iter);
	}

	for (auto iter = enemyInputs.begin(); iter != enemyInputs.end(); iter)
	{
		SAFE_DELETE(*iter);
	}

	for (auto iter = tanks.begin(); iter != tanks.end(); iter++)
	{
		SAFE_DELETE(*iter);
	}

	for (auto iter = tileVec.begin(); iter != tileVec.end(); iter++)
	{
		SAFE_DELETE(*iter);
	}

	SelectObject(gameDC, hOldBitmap);
	DeleteObject(hBitmap);
	DeleteDC(gameDC);
}

void BattleCity::Render()
{
	HDC hdc = GetDC(hWnd);

	DrawBackground();
	//DrawFlag(gameDC);
	DrawTiles();
	DrawRemainEnemyNum(gameDC);
	DrawLifeCount(gameDC);

	player->Render(gameDC);

	for (auto iter = enemys.begin(); iter != enemys.end(); iter++)
	{
		(*iter)->Render(gameDC);
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
