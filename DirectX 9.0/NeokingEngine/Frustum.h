#pragma once
#include "3DBase.h"
#include "Macro.h"

#define FRUSTUM Frustum::GetInstance()

// 프러스텀에 정확하게 포함되지 않더라도, 약간의 여분을 주어서 프러스텀에 포함시키기 위한 값
#define PLANE_EPSILON	5.0f

/**
 * @brief 프러스텀 컬링을 하기위한 클래스
 */
class Frustum
{
private:
	static Frustum* instance;

	D3DXVECTOR3	vertex[8];	// 프러스텀을 구성할 정점 8개
	D3DXVECTOR3	position;	// 현재 카메라의 월드좌표
	D3DXPLANE	plane[6];	// 프러스텀을 구성하는 6개의 평면

	Frustum();

public:
	~Frustum();

	// 카메라(view) * 프로젝션(projection)행렬을 입력받아 6개의 평면을 만든다.
	BOOL	Make(D3DXMATRIXA16* pmatViewProj);

	// 한점 v가 프러스텀안에 있으면 TRUE를 반환, 아니면 FALSE를 반환한다.
	BOOL	IsIn(D3DXVECTOR3* pv);

	/**
	 * @details 중심(v)와 반지름(radius)를 갖는 경계구(bounding sphere)가 프러스텀안에 있으면
	 * @details TRUE를 반환, 아니면 FALSE를 반환한다.
	 */
	BOOL	IsInSphere(D3DXVECTOR3* pv, float radius);

	// 프러스텀을 화면에 그려준다.
	BOOL	Draw(LPDIRECT3DDEVICE9 pDev);

	// 현재 카메라의 월드좌표를 얻어준다.
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

