#include "MapEditor.h"
#include "BitMapManager.h"
#include "Macro.h"

enum BUTTON_ID
{
	ID_00,
	ID_01,
	ID_02,
	ID_03,
	ID_04,
	ID_05,
	ID_06,
	ID_07,
	ID_08,
	ID_09,
	ID_10,
	ID_11,
	ID_12,
	ID_13,
	ID_END,
	ID_14,
};

MapEditor* MapEditor::pInstance = nullptr;

MapEditor::MapEditor()
{
}


void MapEditor::CreateRadioButton(HWND hWnd, HINSTANCE g_hInst, int x, int y, int width, int height, int id)
{
	HWND hRadio = CreateWindow("button", "", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP, x, y, width, height, hWnd, (HMENU)id, g_hInst, NULL);
}

void MapEditor::CreateBitmapButton(HWND hWnd, HINSTANCE g_hInst, int x, int y, int width, int height, int id, HBITMAP bitmap)
{
	HWND hButton = CreateWindow("button", "", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP, x, y, width, height, hWnd, (HMENU)id, g_hInst, NULL);
	//HWND hButton = GetDlgItem(hWnd, id);
	SendMessage(hButton, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)bitmap);
}

void MapEditor::DrawTiles()
{
	for (int y = 0; y < EDITOR_HEIGHT; y++)
	{
		for (int x = 0; x < EDITOR_WIDTH; x++)
		{
			BitMapManager::GetInstance()->GetBitMap(tiles[y][x])->Draw(editorDC, x * TILE_SIZE, y * TILE_SIZE);
		}
	}
}

void MapEditor::SetTile(int x, int y, int index)
{
	TileState tileState = { x, y, tiles[y][x] };
	doStack.push(tileState);
	tileState = { x, y, index };
	tiles[y][x] = index;

	doStack.push(tileState);

	if (!reStack.empty())
	{
		if (tileState != reStack.top())
		{
			while (reStack.top() != doStack.top())
			{
				reStack.pop();
				if (reStack.empty())
					break;
			}
			reStack.push(tileState);
		}
	}
}

void MapEditor::CleanAll()
{
	TileState ts = { -1, -1, -1 };
	doStack.push(ts);

	for (int y = 0; y < EDITOR_HEIGHT; y++)
	{
		for (int x = 0; x < EDITOR_WIDTH; x++)
		{
			if (x == 6 && y == 12)
			{
				tiles[y][x] = BITMAP_RES::BLOCK_13;
			}
			else if (tiles[y][x] != BITMAP_RES::BLOCK_15)
			{
				TileState tileState = { x, y, tiles[y][x] };
				doStack.push(tileState);
				tiles[y][x] = BITMAP_RES::BLOCK_15;
			}
		}
	}

	doStack.push(ts);

	while (!reStack.empty())
	{
		reStack.pop();
	}
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
	selectTile = BITMAP_RES::BLOCK_15;
	currentFileName = "";

	HBITMAP bitmap;
	for (int i = 0; i < BUTTON_ID::ID_13; i++)
	{
		string s = "RES\\";
		s += to_string(i);
		s += ".bmp";
		bitmap = (HBITMAP)LoadImage(NULL, s.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
		CreateBitmapButton(hWnd, g_hInst, 520 + (i % 4) * 40, 40 + (i / 4) * 40, TILE_SIZE, TILE_SIZE, BUTTON_ID::ID_00 + i, bitmap);
	}

	string s = "RES\\";
	s += to_string(BITMAP_RES::BLOCK_15);
	s += ".bmp";
	bitmap = (HBITMAP)LoadImage(NULL, s.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	CreateBitmapButton(hWnd, g_hInst, 520 + 1 * 40, 40 + 3 * 40, TILE_SIZE, TILE_SIZE, BUTTON_ID::ID_13, bitmap);

	s = "RES\\";
	s += to_string(BITMAP_RES::SHIELD_1);
	s += ".bmp";
	bitmap = (HBITMAP)LoadImage(NULL, s.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	CreateBitmapButton(hWnd, g_hInst, 520 + 2 * 40, 40 + 3 * 40, TILE_SIZE, TILE_SIZE, BUTTON_ID::ID_14, bitmap);

	for (int y = 0; y < EDITOR_HEIGHT; y++)
	{
		for (int x = 0; x < EDITOR_WIDTH; x++)
		{
			if (x == 6 && y == 12)
			{
				tiles[y][x] = BITMAP_RES::BLOCK_13;
			}
			else
			{
				tiles[y][x] = BITMAP_RES::BLOCK_15;
			}
		}
	}
}

void MapEditor::Draw(HDC hdc)
{
	DrawTiles();
	//BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::BACK_BLACK)->Draw(editorDC, 0, 0);
	BitBlt(hdc, MARGIN, MARGIN, editorSize.cx, editorSize.cy, editorDC, 0, 0, SRCCOPY);
}

void MapEditor::Update()
{
}

void MapEditor::Release()
{
	BitMapManager::GetInstance()->Release();
	SelectObject(editorDC, hOldBitMap);
	DeleteObject(hBitMap);
	DeleteDC(editorDC);

}

void MapEditor::PushButton(WPARAM wParam)
{
	if (LOWORD(wParam) >= BUTTON_ID::ID_00 && LOWORD(wParam) < BUTTON_ID::ID_END)
	{
		if (LOWORD(wParam) == BUTTON_ID::ID_13)
		{
			selectTile = BITMAP_RES::BLOCK_15;
		}
		else
		{
			selectTile = LOWORD(wParam);
		}
	}
	else if (LOWORD(wParam) == BUTTON_ID::ID_14)
	{
		CleanAll();
	}

}

void MapEditor::CheckTilePosition(int x, int y)
{
	if (x > MARGIN && x < TILE_SIZE * EDITOR_WIDTH + MARGIN && y > MARGIN && y < TILE_SIZE * EDITOR_HEIGHT + MARGIN)
	{
		int idX = (x - MARGIN) / 32;
		int idY = (y - MARGIN) / 32;

		if (idX == 6 && idY == 12)
			return;

		BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::BLOCK_15)->Draw(editorDC, idX * TILE_SIZE, idY* TILE_SIZE);
		SetTile(idX, idY, selectTile);
	}
}

void MapEditor::Input(WPARAM wParam)
{
	switch (wParam)
	{
	case 0x5A: //Z
		Undo();
		break;
	case 0x52: //R
		Redo();
		break;
	case 0x53: //S
		
		break;

	default:
		break;
	}
}

void MapEditor::MakeNew()
{
	currentFileName = "";

	for (int y = 0; y < EDITOR_HEIGHT; y++)
	{
		for (int x = 0; x < EDITOR_WIDTH; x++)
		{
			if (x == 6 && y == 12)
			{
				tiles[y][x] = BITMAP_RES::BLOCK_13;
			}
			else
			{
				tiles[y][x] = BITMAP_RES::BLOCK_15;
			}
		}
	}
	
	while (!doStack.empty())
	{
		doStack.pop();
	}
	while (!reStack.empty())
	{
		reStack.pop();
	}

}

void MapEditor::Save()
{
	ofstream outFile(currentFileName);
	outFile << EDITOR_WIDTH << endl;
	outFile << EDITOR_HEIGHT << endl;

	for (int y = 0; y < EDITOR_HEIGHT; y++)
	{
		for (int x = 0; x < EDITOR_WIDTH; x++)
		{
			outFile << tiles[y][x] << ",";
		}
		outFile << endl;
	}
}

void MapEditor::SaveAs(string fileName)
{
	ofstream outFile(fileName);
	outFile << EDITOR_WIDTH << endl;
	outFile << EDITOR_HEIGHT << endl;

	for (int y = 0; y < EDITOR_HEIGHT; y++)
	{
		for (int x = 0; x < EDITOR_WIDTH; x++)
		{
			outFile << tiles[y][x] << ",";
		}
		outFile << endl;
	}
	currentFileName = fileName;
}

void MapEditor::Load(string fileName)
{
	currentFileName = fileName;
	ifstream inFile(fileName);
	if (inFile)
	{
		BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::BACK_BLACK)->Draw(editorDC, 0, 0);

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

		//스택 초기화
		while (!doStack.empty())
		{
			doStack.pop();
		}
		while (!reStack.empty())
		{
			doStack.pop();
		}
	}
}

bool MapEditor::IsFileOpen()
{
	if (currentFileName == "")
		return false;
	else
		return true;
}

void MapEditor::Undo()
{
	if (!doStack.empty())
	{
		TileState ts = { -1, -1, -1 };
		if (doStack.top().id == -1)
		{
			doStack.pop();
			while (doStack.top().id != -1)
			{
				tiles[doStack.top().y][doStack.top().x] = doStack.top().id;
				doStack.pop();
			}
			doStack.pop();
		}
		else
		{
			TileState tileState = { doStack.top().x, doStack.top().y, doStack.top().id };
			reStack.push(tileState);

			doStack.pop();
			BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::BLOCK_15)->Draw(editorDC, doStack.top().x * TILE_SIZE, doStack.top().y * TILE_SIZE);
			tiles[doStack.top().y][doStack.top().x] = doStack.top().id;
			doStack.pop();
		}
	}
}

void MapEditor::Redo()
{
	if (!reStack.empty())
	{
		SetTile(reStack.top().x, reStack.top().y, reStack.top().id);
		tiles[reStack.top().y][reStack.top().x] = reStack.top().id;
		reStack.pop();
	}
}
