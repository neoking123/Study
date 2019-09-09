#include "MapEditor.h"
#include "BitMapManager.h"
#include "Macro.h"

MapEditor* MapEditor::pInstance = nullptr;

MapEditor::MapEditor()
{
}


void MapEditor::CreateRadioButton(HWND hWnd, HINSTANCE g_hInst)
{
	CreateWindow("button", "Tiles", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 500, 10, 200, 400, hWnd, (HMENU)0, g_hInst, NULL);
	HWND hRadio = CreateWindow("button", "Rectangle", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP, 500, 20, 100, 30, hWnd, (HMENU)ID_R1, g_hInst, NULL);
}

MapEditor::~MapEditor()
{
}

void MapEditor::Init(HDC hdc, HWND hWnd, HINSTANCE g_hInst, SIZE editorSize)
{
	this->editorSize = editorSize;
	editorDC = CreateCompatibleDC(hdc);
	hBitMap = CreateCompatibleBitmap(hdc, this->editorSize.cx, this->editorSize.cy);
	hOldBitMap = (HBITMAP)SelectObject(editorDC, hBitMap);
	BitMapManager::GetInstance()->Init(editorDC);

	CreateRadioButton(hWnd, g_hInst);
}

void MapEditor::Draw(HDC hdc)
{
	BitBlt(hdc, 24, 24, editorSize.cx, editorSize.cy, editorDC, 0, 0, SRCCOPY);
}

void MapEditor::Update()
{

}

void MapEditor::Release()
{
	SelectObject(editorDC, hOldBitMap);
	DeleteObject(hBitMap);
	DeleteDC(editorDC);

}
