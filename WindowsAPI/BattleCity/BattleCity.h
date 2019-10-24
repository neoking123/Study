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
* @brief 게임의 초기화, 업데이트, 렌더링을 담당하는 클래스
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
	* @brief 맵을 로딩하는 함수
	* @details 텍스트 파일을 파싱하여 배열에 저장한다
	* @param string fileName 파일명
	*/
	void LoadMap(string fileName);

	/**
	* @brief 생성된 타일을 출력하는 함수
	* @details 생성된 타일을 출력한다
	*/
	void DrawTiles();

	/**
	* @brief 나무 타일 출력 함수
	* @details 나무 타일의 경우 플레이어와 적 탱크보다 나중에 그려져야 하므로 따로 정의한 출력 함수
	* @details 나무 타일을 출력한다
	*/
	void DrawTreeTiles();

	/**
	* @brief 배경화면 출력 함수
	* @details 배경화면을 출력한다
	*/
	void DrawBackground();

	/**
	* @brief 타일 생성 함수
	* @details 텍스트 파싱으로 구한 배열의 인덱스에 맞게 타일을 생성한다
	*/
	void CreateTile();

	/**
	* @brief 적 탱크 스폰 함수
	* @details 일정 딜레이 간격으로 적 탱크를 스폰한다
	* @details 스폰 위치는 3곳이며 스폰 위치에 겹치는 적 탱크가 있을 경우 다음 위치 스폰 위치에 스폰된다
	* @param float elapseTime 경과 시간
	*/
	void SpawnEnemy(float elapseTime);

	/**
	* @brief 남아있는 적 갯수 출력 함수
	* @details 화면 우측 상단에 남아있는 적 탱크의 수를 아이콘으로 출력한다
	* @param HDC hdc DeviceText 핸들
	*/
	void DrawRemainEnemyNum(HDC hdc);
	
	/**
	* @brief 승리 체크 함수
	* @details 스테이지에 남아있는 적 탱크의 수를 체크하여 승리를 확인한다
	* @param float elapseTime 경과 시간
	*/
	void CheckWin(float elapseTime);

	/**
	* @brief 게임오버 체크 함수
	* @details 플레이어의 라이프 수, 상태, 아군 기지 상태를 체크하여 게임오버를 확인한다
	* @param float elapseTime 경과 시간
	*/
	void CheckGameOver(float elapseTime);

	/**
	* @brief 라이프 수 출력 함수
	* @details 현재 플레이어의 라이프 수를 출력한다
	* @param HDC hdc DeviceText 핸들
	*/
	void DrawLifeCount(HDC hdc);

	/**
	* @brief 스테이지 번호 출력 함수
	* @details 현재 스테이지 번호를 출력한다
	* @param HDC hdc DeviceText 핸들
	*/
	void DrawStageFlag(HDC hdc);

	/**
	* @brief 적 탱크 업데이트 함수
	* @details 생성된 모든 적 탱크의 업데이트를 실행한다
	* @param float elapseTime 경과 시간
	*/
	void UpdateEnemys(float elapseTime);

	/**
	* @brief 아군 기지(독수리) 업데이트 함수
	* @details 아군 기지(독수리)의 업데이트를 실행한다
	* @param float elapseTime 경과 시간
	*/
	void UpdateTileEgle(float elapseTime);

	/**
	* @brief 적 탱크 렌더 함수
	* @details 생성된 모든 적 탱크 렌더링
	* @param HDC hdc DeviceText 핸들
	*/
	void RenderEnemys(HDC hdc);

	/**
	* @brief 스코어 씬 출력 함수
	* @details 스테이지 번호, 킬 숫자, 점수 등을 출력한다
	* @param HDC hdc DeviceText 핸들
	*/
	void DrawScoreScene(HDC hdc);

public:
	~BattleCity();
	/**
	* @brief 초기화 함수
	* @details 백버퍼 생성, 비트맵 매니저 초기화, 속성 초기화를 한다
	* @param HWND hWnd window 핸들
	*/
	void Init(HWND hWnd);

	/**
	* @brief 맵 초기화 함수
	* @details 스테이지 변경 시 기존 맵 파일을 초기화하고 재할당한다
	*/
	void ReInit();

	/**
	* @brief 업데이트 함수
	* @details SCENE_STATE에 따른 업데이트를 실행후, 렌더링을 실행한다
	*/
	void Update();

	/**
	* @brief 해제 함수
	* @details 동적 할당된 객체나 데이터를 해제한다
	*/
	void Release();

	/**
	* @brief 렌더링 함수
	* @details SCENE_STATE에 따른 렌더링을 실행후 백버퍼에 있는 정보를 메인버퍼로 옮겨 출력한다(더블 버퍼링)
	*/
	void Render();

	/**
	* @brief 타일 반환 함수
	* @details 생성된 타일 벡터를 반환
	* @return tileVec
	*/
	vector<Tile*> GetTiles();

	/**
	* @brief 탱크 반환 함수
	* @details 생성된 탱크 벡터를 반환
	* @return tanks
	*/
	vector<Tank*> GetTanks();

	/**
	* @brief 적 탱크 수 감소 함수
	* @details 적 탱크 수를 감소 시킨다
	*/
	void DecreaseEnemyNum();

	/**
	* @brief 아군 기지(독수리) 파괴 함수
	* @details 아군 기지(독수리) 파괴 플래그를 준다
	*/
	void DestroyEgle();

	/**
	* @brief 플레이어 라이프 카운트 리턴 함수
	* @details 플레이어 라이프 카운트를 리턴한다
	* @return lifeCount
	*/
	int GetLifeCount();

	/**
	* @brief 플레이어 라이프 감소 함수
	* @details 플레이어 라이프를 감소시킨다
	*/
	void LoseLife();

	/**
	* @brief 싱글톤 Get함수
	* @details 싱글톤 인스턴스를 리턴한다
	* @details null값이라면 새로 메모리를 할당한다
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
	* @brief 싱글톤 해제 함수
	* @details 싱글톤 인스턴스의 메모리를 해제한다
	*/
	static void FreeInstance()
	{
		if (pInstance != nullptr)
		{
			SAFE_DELETE(pInstance);

		}
	}
};

