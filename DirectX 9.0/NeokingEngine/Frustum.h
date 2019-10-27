#pragma once
#include "3DBase.h"
#include "Macro.h"

#define FRUSTUM Frustum::GetInstance()

// �������ҿ� ��Ȯ�ϰ� ���Ե��� �ʴ���, �ణ�� ������ �־ �������ҿ� ���Խ�Ű�� ���� ��
#define PLANE_EPSILON	5.0f

/**
 * @brief �������� �ø��� �ϱ����� Ŭ����
 */
class Frustum
{
private:
	static Frustum* instance;

	D3DXVECTOR3	vertex[8];	// ���������� ������ ���� 8��
	D3DXVECTOR3	position;	// ���� ī�޶��� ������ǥ
	D3DXPLANE	plane[6];	// ���������� �����ϴ� 6���� ���

	Frustum();

public:
	~Frustum();

	// ī�޶�(view) * ��������(projection)����� �Է¹޾� 6���� ����� �����.
	BOOL	Make(D3DXMATRIXA16* pmatViewProj);

	// ���� v�� �������Ҿȿ� ������ TRUE�� ��ȯ, �ƴϸ� FALSE�� ��ȯ�Ѵ�.
	BOOL	IsIn(D3DXVECTOR3* pv);

	/**
	 * @details �߽�(v)�� ������(radius)�� ���� ��豸(bounding sphere)�� �������Ҿȿ� ������
	 * @details TRUE�� ��ȯ, �ƴϸ� FALSE�� ��ȯ�Ѵ�.
	 */
	BOOL	IsInSphere(D3DXVECTOR3* pv, float radius);

	// ���������� ȭ�鿡 �׷��ش�.
	BOOL	Draw(LPDIRECT3DDEVICE9 pDev);

	// ���� ī�޶��� ������ǥ�� ����ش�.
	D3DXVECTOR3*	GetPos() { return &position; }

	static Frustum* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new Frustum();
		}

		return instance;
	}

	static void FreeInstance()
	{
		if (instance)
		{
			SAFE_DELETE(instance);
		}
	}
};

