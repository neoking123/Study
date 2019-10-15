#pragma once
#include <Windows.h>
#include <vector>
#include <stack>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

#define TILE_SIZE 32
#define EDITOR_WIDTH 13
#define EDITOR_HEIGHT 13
#define MARGIN 24

struct TileState
{
	int x = 0;
	int y = 0;
	int id = 0;

	bool operator==(TileState& tileStae)
	{
		if (this->x == tileStae.x && this->y == tileStae.y && this->id == tileStae.id)
			return true;
		else
			false;
	}

	bool operator!=(TileState& tileStae)
	{
		if (this->x == tileStae.x && this->y == tileStae.y && this->id == tileStae.id)
			return false;
		else
			true;
	}
};

class MapEditor
{
private:
	MapEditor();

	static MapEditor* pInstance;

	HWND hWnd;
	HDC editorDC;
	HBITMAP hBitMap;
	HBITMAP hOldBitMap;
	SIZE editorSize;
	int tiles[EDITOR_HEIGHT][EDITOR_WIDTH];
	int selectTile;
	stack<TileState> doStack;
	stack<TileState> reStack;
	string currentFileName;

	void CreateRadioButton(HWND hWnd, HINSTANCE g_hInst, int x, int y, int width, int height, int id);
	void CreateBitmapButton(HWND hWnd, HINSTANCE g_hInst, int x, int y, int width, int height, int id, HBITMAP bitmap);
	void DrawTiles();
	void SetTile(int x, int y, int index);
	void CleanAll();
	void Undo();
	void Redo();

public:
	~MapEditor();

	void Init(HDC hdc, HWND hWnd, HINSTANCE g_hInst, SIZE editorSize);
	void Draw(HDC hdc);
	void Update();
	void Release();
	void PushButton(WPARAM wParam);
	void CheckTilePosition(int x, int y);
	void Input(WPARAM wParam);
	void MakeNew();
	void Save();
	void SaveAs(string fileName);
	void Load(string fileName);
	bool IsFileOpen();

	static MapEditor* GetInstance()
	{
		if (pInstance == nullptr)
		{
			pInstance = new MapEditor();
		}
		return pInstance;
	}

	static void FreeInstance()
	{
		if (pInstance != nullptr)
		{
			delete pInstance;
			pInstance = nullptr;
		}
	}
};

