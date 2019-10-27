#pragma once
#include "3DBase.h"
#include "Frustum.h"

/**
 * @brief QuadTree의 베이스 클래스
 */
class QuadTree
{
public:
	// 쿼드트리에 보관되는 4개의 코너값에 대한 상수값
	enum CornerType { CORNER_TL, CORNER_TR, CORNER_BL, CORNER_BR };

	// 이웃노드 처리용 상수값
	enum { EDGE_UP, EDGE_DN, EDGE_LT, EDGE_RT };

	// 쿼드트리와 프러스텀간의 관계
	enum QuadLocation {
		FRUSTUM_OUT = 0,				// 프러스텀에서 완전벗어남
		FRUSTUM_PARTIALLY_IN = 1,		// 프러스텀에 부분포함
		FRUSTUM_COMPLETELY_IN = 2,		// 프러스텀에 완전포함
		FRUSTUM_UNKNOWN = -1
	};

private:
	QuadTree*	child[4];		// QuadTree의 4개의 자식노드

	QuadTree*	parent;			// Triangle Crack(Popping)을 막기위해서 사용한다.
	QuadTree*	neighbor[4];	// Triangle Crack(Popping)을 막기위해서 사용한다.

	int			center;			// QuadTree에 보관할 첫번째 값
	int			corner[4];		// QuadTree에 보관할 두번째 값
								//    TopLeft(TL)      TopRight(TR)
								//              0------1
								//              |      |
								//              |      |
								//              2------3
								// BottomLeft(BL)      BottomRight(BR)
	BOOL		culled;			// 프러스텀에서 컬링된 노드인가?
	float		radius;			// 노드를 감싸는 경계구(bounding sphere)의 반지름
	
private:
	// 자식 노드를 추가한다.
	QuadTree*	AddChild(int nCornerTL, int nCornerTR, int nCornerBL, int nCornerBR);

	// 4개의 코너값을 셋팅한다.
	BOOL		SetCorners(int nCornerTL, int nCornerTR, int nCornerBL, int nCornerBR);

	// Quadtree를 4개의 하위 트리로 부분분할(subdivide)한다.
	BOOL		SubDivide();		// Quadtree를 subdivide한다.

	// 출력할 폴리곤의 인덱스를 생성한다.
	int			GenTriIndex(int nTris, LPVOID pIndex, TERRAINVERTEX* pHeightMap, Frustum* pFrustum, float fLODRatio);

	// 메모리에서 쿼드트리를 삭제한다.
	void		Destroy();

	// 두점 사이의 거리를 구한다.
	float		GetDistance(D3DXVECTOR3* pv1, D3DXVECTOR3* pv2)
	{
		return D3DXVec3Length(&(*pv2 - *pv1));
	}

	// 카메라와 현재 노드와의 거리값을 기준으로 LOD값을 구한다.
	int			GetLODLevel(TERRAINVERTEX* pHeightMap, D3DXVECTOR3* pCamera, float fLODRatio)
	{
		float d = GetDistance((D3DXVECTOR3*)(pHeightMap + center), pCamera);
		return max((int)(d * fLODRatio), 1);
	}

	// 모든 자식노드의 m_bCulled값을 FALSE로 한다
	void		AllInFrustum();

	// 현재노드가 프러스텀에 포함되는가?
	int			IsInFrustum(TERRAINVERTEX* pHeightMap, Frustum* pFrustum);

	// _IsInFrustum()함수의 결과에 따라 프러스텀 컬링 수행
	void		FrustumCull(TERRAINVERTEX* pHeightMap, Frustum* pFrustum);

	// 이웃노드를 만든다.(삼각형 찢어짐 방지용)
	void		BuildNeighborNode(QuadTree* pRoot, TERRAINVERTEX* pHeightMap, int cx);

	// 쿼드트리를 만든다.(Build()함수에서 불린다)
	BOOL		BuildQuadTree(TERRAINVERTEX* pHeightMap);

	// 쿼드트리를 검색해서 4개 코너값과 일치하는 노드를 찾는다.
	QuadTree*	FindNode(TERRAINVERTEX* pHeightMap, int _0, int _1, int _2, int _3);

	// 4개 방향(상단,하단,좌측,우측)의 이웃노드 인덱스를 구한다.
	int			GetNodeIndex(int ed, int cx, int& _0, int& _1, int& _2, int& _3);

public:

	// 최초 루트노드 생성자
	QuadTree(int cx, int cy);

	// 하위 자식노드 생성자
	QuadTree(QuadTree* pParent);

	// 소멸자
	~QuadTree();

	// 현재 노드가 Culling된것인가?
	BOOL		IsCulled() { return culled; }

	// 현재 노드가 LOD등급으로 볼때  출력이 가능한 노드인가?
	BOOL		IsVisible(TERRAINVERTEX* pHeightMap, D3DXVECTOR3* pCamera, float fLODRatio)
	{
		return ((corner[CORNER_TR] - corner[CORNER_TL]) <= GetLODLevel(pHeightMap, pCamera, fLODRatio));
	}

	// QuadTree를 구축한다.
	BOOL		Build(TERRAINVERTEX* pHeightMap);	// 현재의 정보를 기준으로 QuadTree를 build한다.

	// 코너 인덱스 값을 얻어온다.
	void		GetCorner(int& _0, int& _1, int& _2, int& _3)
	{
		_0 = corner[0]; _1 = corner[1]; _2 = corner[2]; _3 = corner[3];
	}

	//	삼각형의 인덱스를 만들고, 출력할 삼각형의 개수를 반환한다.
	int			GenerateIndex(LPVOID pIndex, TERRAINVERTEX* pHeightMap, Frustum* pFrustum, float fLODRatio);
};

