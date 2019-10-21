#include <Windows.h>
#include <math.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hlnst;
LPCTSTR lpszClass = TEXT("Matrix Test");

class Vector
{
public:
	Vector() {}

	Vector(float x, float y, float z, float w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	float x;
	float y;
	float z;
	float w;
};

class Matrix
{
public:
	float arr[4][4];

	Matrix() {}

	Matrix(float initArr[][4])
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				arr[i][j] = initArr[i][j];
			}
		}
	}

	Matrix& operator=(const Matrix& matrix)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				arr[i][j] = matrix.arr[i][j];
			}
		}
		return *this;
	}

	Vector operator*(Vector& vec)
	{
		Vector newVec;
		newVec.x = (vec.x * arr[0][0]) + (vec.y * arr[1][0]) + (vec.z * arr[2][0]) + (vec.w * arr[3][0]);
		newVec.y = (vec.x * arr[0][1]) + (vec.y * arr[1][1]) + (vec.z * arr[2][1]) + (vec.w * arr[3][1]);
		newVec.z = (vec.x * arr[0][2]) + (vec.y * arr[1][2]) + (vec.z * arr[2][2]) + (vec.w * arr[3][2]);
		newVec.w = (vec.x * arr[0][3]) + (vec.y * arr[1][3]) + (vec.z * arr[2][3]) + (vec.w * arr[3][3]);

		return newVec;
	}

	Matrix operator*(Matrix& matrix)
	{
		Matrix newMat;
		newMat.arr[0][0] = (this->arr[0][0] * matrix.arr[0][0]) + (this->arr[0][1] * matrix.arr[1][0]) + (this->arr[0][2] * matrix.arr[2][0]) + (this->arr[0][3] * matrix.arr[3][0]);
		newMat.arr[0][1] = (this->arr[0][0] * matrix.arr[0][1]) + (this->arr[0][1] * matrix.arr[1][1]) + (this->arr[0][2] * matrix.arr[2][1]) + (this->arr[0][3] * matrix.arr[3][1]);
		newMat.arr[0][2] = (this->arr[0][0] * matrix.arr[0][2]) + (this->arr[0][1] * matrix.arr[1][2]) + (this->arr[0][2] * matrix.arr[2][2]) + (this->arr[0][3] * matrix.arr[3][2]);
		newMat.arr[0][3] = (this->arr[0][0] * matrix.arr[0][3]) + (this->arr[0][1] * matrix.arr[1][3]) + (this->arr[0][2] * matrix.arr[2][3]) + (this->arr[0][3] * matrix.arr[3][3]);

		newMat.arr[1][0] = (this->arr[1][0] * matrix.arr[0][0]) + (this->arr[1][1] * matrix.arr[1][0]) + (this->arr[1][2] * matrix.arr[2][0]) + (this->arr[1][3] * matrix.arr[3][0]);
		newMat.arr[1][1] = (this->arr[1][0] * matrix.arr[0][1]) + (this->arr[1][1] * matrix.arr[1][1]) + (this->arr[1][2] * matrix.arr[2][1]) + (this->arr[1][3] * matrix.arr[3][1]);
		newMat.arr[1][2] = (this->arr[1][0] * matrix.arr[0][2]) + (this->arr[1][1] * matrix.arr[1][2]) + (this->arr[1][2] * matrix.arr[2][2]) + (this->arr[1][3] * matrix.arr[3][2]);
		newMat.arr[1][3] = (this->arr[1][0] * matrix.arr[0][3]) + (this->arr[1][1] * matrix.arr[1][3]) + (this->arr[1][2] * matrix.arr[2][3]) + (this->arr[1][3] * matrix.arr[3][3]);

		newMat.arr[2][0] = (this->arr[2][0] * matrix.arr[0][0]) + (this->arr[2][1] * matrix.arr[1][0]) + (this->arr[2][2] * matrix.arr[2][0]) + (this->arr[2][3] * matrix.arr[3][0]);
		newMat.arr[2][1] = (this->arr[2][0] * matrix.arr[0][1]) + (this->arr[2][1] * matrix.arr[1][1]) + (this->arr[2][2] * matrix.arr[2][1]) + (this->arr[2][3] * matrix.arr[3][1]);
		newMat.arr[2][2] = (this->arr[2][0] * matrix.arr[0][2]) + (this->arr[2][1] * matrix.arr[1][2]) + (this->arr[2][2] * matrix.arr[2][2]) + (this->arr[2][3] * matrix.arr[3][2]);
		newMat.arr[2][3] = (this->arr[2][0] * matrix.arr[0][3]) + (this->arr[2][1] * matrix.arr[1][3]) + (this->arr[2][2] * matrix.arr[2][3]) + (this->arr[2][3] * matrix.arr[3][3]);

		newMat.arr[3][0] = (this->arr[3][0] * matrix.arr[0][0]) + (this->arr[3][1] * matrix.arr[1][0]) + (this->arr[3][2] * matrix.arr[2][0]) + (this->arr[3][3] * matrix.arr[3][0]);
		newMat.arr[3][1] = (this->arr[3][0] * matrix.arr[0][1]) + (this->arr[3][1] * matrix.arr[1][1]) + (this->arr[3][2] * matrix.arr[2][1]) + (this->arr[3][3] * matrix.arr[3][1]);
		newMat.arr[3][2] = (this->arr[3][0] * matrix.arr[0][2]) + (this->arr[3][1] * matrix.arr[1][2]) + (this->arr[3][2] * matrix.arr[2][2]) + (this->arr[3][3] * matrix.arr[3][2]);
		newMat.arr[3][3] = (this->arr[3][0] * matrix.arr[0][3]) + (this->arr[3][1] * matrix.arr[1][3]) + (this->arr[3][2] * matrix.arr[2][3]) + (this->arr[3][3] * matrix.arr[3][3]);

		return newMat;
	}
};

void MatrixIdentity(Matrix& matrix)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (i == j)
			{
				matrix.arr[i][j] = 1;
			}
			else
			{
				matrix.arr[i][j] = 0;
			}
		}
	}
}

void MatrixTranslation(Vector& vec, Vector move)
{
	Matrix transMat;
	MatrixIdentity(transMat);
	transMat.arr[3][0] = move.x;
	transMat.arr[3][1] = move.y;
	transMat.arr[3][2] = move.z;

	vec = transMat * vec;
}

void MatrixRotationX(Matrix& matrix, float angle)
{
	Matrix rotationMat;
	MatrixIdentity(rotationMat);

	rotationMat.arr[1][1] = cos(angle);
	rotationMat.arr[1][2] = sin(angle);
	rotationMat.arr[2][1] = -sin(angle);
	rotationMat.arr[2][2] = cos(angle);

	matrix = matrix * rotationMat;
}

void MatrixRotationY(Matrix& matrix, float angle)
{
	Matrix rotationMat;
	MatrixIdentity(rotationMat);

	rotationMat.arr[0][0] = cos(angle);
	rotationMat.arr[0][2] = -sin(angle);
	rotationMat.arr[2][0] = sin(angle);
	rotationMat.arr[2][2] = cos(angle);

	matrix = rotationMat * matrix;
}

void MatrixRotationZ(Matrix& matrix, float angle)
{
	Matrix rotationMat;
	MatrixIdentity(rotationMat);

	rotationMat.arr[0][0] = cos(angle);
	rotationMat.arr[0][1] = sin(angle);
	rotationMat.arr[1][0] = -sin(angle);
	rotationMat.arr[1][1] = cos(angle);

	matrix = matrix * rotationMat;
}

void MatrixScale(Matrix& matrix, Vector vec)
{
	Matrix scaleMat;
	MatrixIdentity(scaleMat);

	scaleMat.arr[0][0] = vec.x;
	scaleMat.arr[1][1] = vec.y;
	scaleMat.arr[2][2] = vec.z;

	matrix = matrix * scaleMat;
}

void MatrixProjection(Matrix& matrix, float left, float right, float top, float bottom, float nearVal, float farVal)
{
	Matrix ProjMat;
	MatrixIdentity(ProjMat);
	
	ProjMat.arr[0][0] = 2 * nearVal / (right - left);
	ProjMat.arr[0][2] = (right + left) / (right - left);
	ProjMat.arr[1][1] = 2 * nearVal / top - bottom;
	ProjMat.arr[1][2] = -((farVal + nearVal) / (farVal - nearVal));
	ProjMat.arr[2][2] = 2 * nearVal / right - left;
	ProjMat.arr[2][3] = 2 * nearVal / right - left;
	ProjMat.arr[3][2] = -1;

	matrix = matrix * ProjMat;
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass; // 옵션 구조체
	g_hlnst = hInstance;

	WndClass.cbClsExtra = 0; // 화면 넘어올 때 메모리
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // 배경화면
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW); // 커서
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION); // 아이콘
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc; // 프로시저 함수 포인터
	WndClass.lpszClassName = lpszClass; // 이름
	WndClass.lpszMenuName = NULL; // 메뉴
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass); // 클래스 등록

	// 클래스네임, 타이틀, 윈도우스타일, 창 시작 위치, 넓이, 높이, 계층구조, 메뉴, 인스턴스, 파라미터
	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 10, 10,
		NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow); // 윈도우 출력

	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}

// 핸들, 메세지 타입, 파라미터
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM IParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	SYSTEMTIME st;
	static TCHAR str[256];

	static float timeFlow = 0.0f;
	static Matrix world;
	MatrixIdentity(world);
	MatrixRotationY(world, timeFlow);

	static Vector vEyept = { 0.0f, 0.0f, -10.0f, 0.0f };
	static Vector vLootatPt = { 0.0f, 0.0f, 0.0f, 0.0f };
	static Vector vUpVec = { 0.0f, 1.0f, 0.0f, 0.0f };

	Vector v1 = { 400, 400, 0, 1 };
	Vector v2 = { 600, 400, 0, 1 };
	Vector v3 = { 500, 250, 0, 1 };

	float arr1[][4] = { 1,2,3,4, 2,1,3,1, 4,1,2,1, 5,0,2,1 };
	float arr2[][4] = { 3,2,4,1, 1,2,2,1, 3,3,2,1, 4,1,0,0 };
	static Matrix mat1 = arr1;
	static Matrix mat2 = arr2;
	static Matrix mat3 = (mat1 * mat2);

	switch (iMessage)
	{
	case WM_CREATE:
		SetTimer(hWnd, 1, 1000, NULL);
		return 0;

	case WM_TIMER:
		GetLocalTime(&st);

		timeFlow += 0.1f;
		MatrixRotationY(world, timeFlow);

		InvalidateRect(hWnd, NULL, TRUE);
		return 0;

	case WM_GETMINMAXINFO:
		((MINMAXINFO*)IParam)->ptMaxTrackSize.x = 1280;
		((MINMAXINFO*)IParam)->ptMaxTrackSize.y = 995;
		((MINMAXINFO*)IParam)->ptMinTrackSize.x = 1280;
		((MINMAXINFO*)IParam)->ptMinTrackSize.y = 995;
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		v1 = world * v1;
		v2 = world * v2;
		v3 = world * v3;

		//MatrixTranslation(v2, Vector(200, 0, 0, 0));




		MoveToEx(hdc, v1.x, v1.y, NULL);
		LineTo(hdc, v1.x, v1.y);
		LineTo(hdc, v2.x, v2.y);
		MoveToEx(hdc, v2.x, v2.y, NULL);
		LineTo(hdc, v3.x, v3.y);
		MoveToEx(hdc, v3.x, v3.y, NULL);
		LineTo(hdc, v1.x, v1.y);

		EndPaint(hWnd, &ps);
		return 0;

	case WM_DESTROY:
		KillTimer(hWnd, 1);
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, IParam));
}