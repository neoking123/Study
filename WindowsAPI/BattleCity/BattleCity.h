#pragma once
#include <Windows.h>
#include <chrono>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include "Macro.h"
using namespace std;

#define FPS	100.0f
#define MAP_WIDTH 32
#define MAP_HEIGHT 32
#define SCREEN_WIDE 550
#define SCREEN_HEIGHT 460
#define MAP_MARGINE_WIDTH 24
#define MAP_MARGINE_HEIGHT 24
#define TILE_WIDTH_NUM 13
#define TILE_HEIGHT_NUM 13
#define TILE_SIZE 32
#define MAX_ENEMY_NUM 4
#define MAX_SPAWN_NUM 20
#define STAGE1 "Maps\\Stage1.txt"
#define STAGE2 "Maps\\Stage2.txt"

enum SCENE_STATE
{
	MAIN_SCENE,
	STAGE_SCENE,
	INGAME_SCENE,
	SCORE_SCENE,
	GAMEOVER_SCENE,
};

class Tank;
class PlayerInputComponent;
class Tile;
class Enemy;
class EnemyInputComponent;

/**
* @brief ������ �ʱ�ȭ, ������Ʈ, �������� ����ϴ� Ŭ����
* @author Dayeol Hyeon
*/


class BattleCity
{
private:
	static BattleCity* pInstance;

	HDC gameDC;
	HBITMAP hBitmap;
	HBITMAP hOldBitmap;
	HWND hWnd;

	float elapseTime;
	chrono::system_clock::time_point lastTime;

	bool isFisrtInit;
	SCENE_STATE sceneState;
	int currentStage;
	float stageChangeTime;
	int scoreKillCount;
	int scoreCount;
	float scoreSceneTime;
	int lifeCount;

	int tiles[MAP_HEIGHT][MAP_WIDTH];
	vector<Tile*> tileVec;

	Tank* player = nullptr;
	PlayerInputComponent* playerInput = nullptr;
	vector<EnemyInputComponent*> enemyInputs;
	list<Enemy*> enemys;
	vector<Tank*> tanks;

	int spawnPointNum;
	float spawnTime;
	int spawnEnemyNum;
	int killCount;
	bool isDestroyedEgle;

	BattleCity();

	/**
	* @brief ���� �ε��ϴ� �Լ�
	* @details �ؽ�Ʈ ������ �Ľ��Ͽ� �迭�� �����Ѵ�
	* @param string fileName ���ϸ�
	*/
	void LoadMap(string fileName);

	/**
	* @brief ������ Ÿ���� ����ϴ� �Լ�
	* @details ������ Ÿ���� ����Ѵ�
	*/
	void DrawTiles();

	/**
	* @brief ���� Ÿ�� ��� �Լ�
	* @details ���� Ÿ���� ��� �÷��̾�� �� ��ũ���� ���߿� �׷����� �ϹǷ� ���� ������ ��� �Լ�
	* @details ���� Ÿ���� ����Ѵ�
	*/
	void DrawTreeTiles();

	/**
	* @brief ���ȭ�� ��� �Լ�
	* @details ���ȭ���� ����Ѵ�
	*/
	void DrawBackground();

	/**
	* @brief Ÿ�� ���� �Լ�
	* @details �ؽ�Ʈ �Ľ����� ���� �迭�� �ε����� �°� Ÿ���� �����Ѵ�
	*/
	void CreateTile();

	/**
	* @brief �� ��ũ ���� �Լ�
	* @details ���� ������ �������� �� ��ũ�� �����Ѵ�
	* @details ���� ��ġ�� 3���̸� ���� ��ġ�� ��ġ�� �� ��ũ�� ���� ��� ���� ��ġ ���� ��ġ�� �����ȴ�
	* @param float elapseTime ��� �ð�
	*/
	void SpawnEnemy(float elapseTime);

	/**
	* @brief �����ִ� �� ���� ��� �Լ�
	* @details ȭ�� ���� ��ܿ� �����ִ� �� ��ũ�� ���� ���������� ����Ѵ�
	* @param HDC hdc DeviceText �ڵ�
	*/
	void DrawRemainEnemyNum(HDC hdc);
	
	/**
	* @brief �¸� üũ �Լ�
	* @details ���������� �����ִ� �� ��ũ�� ���� üũ�Ͽ� �¸��� Ȯ���Ѵ�
	* @param float elapseTime ��� �ð�
	*/
	void CheckWin(float elapseTime);

	/**
	* @brief ���ӿ��� üũ �Լ�
	* @details �÷��̾��� ������ ��, ����, �Ʊ� ���� ���¸� üũ�Ͽ� ���ӿ����� Ȯ���Ѵ�
	* @param float elapseTime ��� �ð�
	*/
	void CheckGameOver(float elapseTime);

	/**
	* @brief ������ �� ��� �Լ�
	* @details ���� �÷��̾��� ������ ���� ����Ѵ�
	* @param HDC hdc DeviceText �ڵ�
	*/
	void DrawLifeCount(HDC hdc);

	/**
	* @brief �������� ��ȣ ��� �Լ�
	* @details ���� �������� ��ȣ�� ����Ѵ�
	* @param HDC hdc DeviceText �ڵ�
	*/
	void DrawStageFlag(HDC hdc);

	/**
	* @brief �� ��ũ ������Ʈ �Լ�
	* @details ������ ��� �� ��ũ�� ������Ʈ�� �����Ѵ�
	* @param float elapseTime ��� �ð�
	*/
	void UpdateEnemys(float elapseTime);

	/**
	* @brief �Ʊ� ����(������) ������Ʈ �Լ�
	* @details �Ʊ� ����(������)�� ������Ʈ�� �����Ѵ�
	* @param float elapseTime ��� �ð�
	*/
	void UpdateTileEgle(float elapseTime);

	/**
	* @brief �� ��ũ ���� �Լ�
	* @details ������ ��� �� ��ũ ������
	* @param HDC hdc DeviceText �ڵ�
	*/
	void RenderEnemys(HDC hdc);

	/**
	* @brief ���ھ� �� ��� �Լ�
	* @details �������� ��ȣ, ų ����, ���� ���� ����Ѵ�
	* @param HDC hdc DeviceText �ڵ�
	*/
	void DrawScoreScene(HDC hdc);

public:
	~BattleCity();
	/**
	* @brief �ʱ�ȭ �Լ�
	* @details ����� ����, ��Ʈ�� �Ŵ��� �ʱ�ȭ, �Ӽ� �ʱ�ȭ�� �Ѵ�
	* @param HWND hWnd window �ڵ�
	*/
	void Init(HWND hWnd);

	/**
	* @brief �� �ʱ�ȭ �Լ�
	* @details �������� ���� �� ���� �� ������ �ʱ�ȭ�ϰ� ���Ҵ��Ѵ�
	*/
	void ReInit();

	/**
	* @brief ������Ʈ �Լ�
	* @details SCENE_STATE�� ���� ������Ʈ�� ������, �������� �����Ѵ�
	*/
	void Update();

	/**
	* @brief ���� �Լ�
	* @details ���� �Ҵ�� ��ü�� �����͸� �����Ѵ�
	*/
	void Release();

	/**
	* @brief ������ �Լ�
	* @details SCENE_STATE�� ���� �������� ������ ����ۿ� �ִ� ������ ���ι��۷� �Ű� ����Ѵ�(���� ���۸�)
	*/
	void Render();

	/**
	* @brief Ÿ�� ��ȯ �Լ�
	* @details ������ Ÿ�� ���͸� ��ȯ
	* @return tileVec
	*/
	vector<Tile*> GetTiles();

	/**
	* @brief ��ũ ��ȯ �Լ�
	* @details ������ ��ũ ���͸� ��ȯ
	* @return tanks
	*/
	vector<Tank*> GetTanks();

	/**
	* @brief �� ��ũ �� ���� �Լ�
	* @details �� ��ũ ���� ���� ��Ų��
	*/
	void DecreaseEnemyNum();

	/**
	* @brief �Ʊ� ����(������) �ı� �Լ�
	* @details �Ʊ� ����(������) �ı� �÷��׸� �ش�
	*/
	void DestroyEgle();

	/**
	* @brief �÷��̾� ������ ī��Ʈ ���� �Լ�
	* @details �÷��̾� ������ ī��Ʈ�� �����Ѵ�
	* @return lifeCount
	*/
	int GetLifeCount();

	/**
	* @brief �÷��̾� ������ ���� �Լ�
	* @details �÷��̾� �������� ���ҽ�Ų��
	*/
	void LoseLife();

	/**
	* @brief �̱��� Get�Լ�
	* @details �̱��� �ν��Ͻ��� �����Ѵ�
	* @details null���̶�� ���� �޸𸮸� �Ҵ��Ѵ�
	* @return pInstance
	*/
	static BattleCity* GetInstance()
	{
		if (pInstance == nullptr)
		{
			pInstance = new BattleCity();
		}
		return pInstance;
	}

	/**
	* @brief �̱��� ���� �Լ�
	* @details �̱��� �ν��Ͻ��� �޸𸮸� �����Ѵ�
	*/
	static void FreeInstance()
	{
		if (pInstance != nullptr)
		{
			SAFE_DELETE(pInstance);

		}
	}
};

