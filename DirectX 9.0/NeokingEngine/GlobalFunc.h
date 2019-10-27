#ifndef _GLOBALFUNC_H_
#define _GLOBALFUNC_H_

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#define IS_IN_RANGE(value,r0,r1) (( ((r0) <= (value)) && ((value) <= (r1)) ) ? 1 : 0)

// 2�� ������ �ϴ� ���� n�� �αװ��� ���Ѵ�.
int	Log2(int n);

// 2^n���� ���Ѵ�
int	Pow2(int n);

// pt�� rc�ȿ� ���ԵǴ��� �˻��Ѵ�.(PtInRect()��� API�Լ��� ����(-)�� ó���� ���ߴ�.)
BOOL IsInRect(RECT* rc, POINT pt);

#endif // _GLOBALFUNC_H_