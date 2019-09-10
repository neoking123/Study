#pragma once
#include <Windows.h>
#include <vector>
#include <stack>
using namespace std;

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
	int tiles[13][13];
	int selectTile;
	stack<TileState> doStack;
	stack<TileState> reStack;

	void CreateRadioButton(HWND hWnd, HINSTANCE g_hInst, int x, int y, int width, int height, int id);
	void CreateBitmapButton(HWND hWnd, HINSTANCE g_hInst, int x, int y, int width, int height, int id, HBITMAP bitmap);
	void DrawTiles();
	void SetTile(int x, int y, int index);
	
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

