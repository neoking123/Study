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
				newTile->Init(nullptr, x * TILE_SIZE + MAP_MARGINE_WIDTH, y * TILE_SIZE + MAP_MARGINE_HEIGHT, "tile", tiles[y][x]);
				tileVec.push_back(newTile);
			}
		}
	}

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

	for (int i = 0; i < MAX_ENEMY_NUM; i++)
	{
		EnemyInputComponent* enemyInput = new EnemyInputComponent();
		enemyInputs.push_back(enemyInput);

		Enemy* enemy = new Enemy();
		enemy->Init(enemyInputs[i], (i * 2) * TILE_SIZE + MAP_MARGINE_WIDTH, 0 * TILE_SIZE + MAP_MARGINE_HEIGHT, "enemy");
		enemys.push_back(enemy);
		tanks.push_back(enemy);
	}

	/*enemy_debug = new Enemy();
	enemy_debug->Init(enemyInput, 0 * TILE_SIZE + MAP_MARGINE_WIDTH, 0 * TILE_SIZE + MAP_MARGINE_HEIGHT, "enemy");
	tanks.push_back(enemy_debug);*/
	
	ReleaseDC(hWnd, hdc);
}

void BattleCity::Update()
{
	std::chrono::duration<float> sec = std::chrono::system_clock::now() - lastTime;
	if (sec.count() < (1 / FPS))
		return;

	elapseTime = sec.count();
	
	if (!player->isDead)
		player->Update(elapseTime);

	for (auto iter = enemys.begin(); iter != enemys.end(); iter++)
	{
		if (!(*iter)->isDead)
			(*iter)->Update(elapseTime);
	}
	
	Render();

	lastTime = std::chrono::system_clock::now();
}

void BattleCity::Release()
{
	SAFE_DELETE(player);
	SAFE_DELETE(playerInput);

	for (auto iter = enemys.begin(); iter != enemys.end(); iter++)
	{
		SAFE_DELETE(*iter);
		(*iter)->Release();
	}

	player->Release();


	SelectObject(gameDC, hOldBitmap);
	DeleteObject(hBitmap);
	DeleteDC(gameDC);
}

void BattleCity::Render()
{
	HDC hdc = GetDC(hWnd);

	DrawBackground();
	DrawTiles();

	if (!player->isDead)
		player->Render(gameDC);

	for (auto iter = enemys.begin(); iter != enemys.end(); iter++)
	{
		if (!(*iter)->isDead)
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
