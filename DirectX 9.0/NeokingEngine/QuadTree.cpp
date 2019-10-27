#include "QuadTree.h"

void QuadTree::AllInFrustum()
{
	culled = FALSE;
	if (!child[0]) return;
	child[0]->AllInFrustum();
	child[1]->AllInFrustum();
	child[2]->AllInFrustum();
	child[3]->AllInFrustum();
}

int QuadTree::IsInFrustum(TERRAINVERTEX * pHeightMap, Frustum * pFrustum)
{
	BOOL	b[4];
	BOOL	bInSphere;

	// 경계구안에 있는가?
//	if( m_fRadius == 0.0f ) g_pLog->Log( "Index:[%d], Radius:[%f]",m_nCenter, m_fRadius );
	bInSphere = pFrustum->IsInSphere((D3DXVECTOR3*)(pHeightMap + center), radius);
	if (!bInSphere) return FRUSTUM_OUT;	// 경계구 안에 없으면 점단위의 프러스텀 테스트 생략

	// 쿼드트리의 4군데 경계 프러스텀 테스트
	b[0] = pFrustum->IsIn((D3DXVECTOR3*)(pHeightMap + corner[0]));
	b[1] = pFrustum->IsIn((D3DXVECTOR3*)(pHeightMap + corner[1]));
	b[2] = pFrustum->IsIn((D3DXVECTOR3*)(pHeightMap + corner[2]));
	b[3] = pFrustum->IsIn((D3DXVECTOR3*)(pHeightMap + corner[3]));

	// 4개모두 프러스텀 안에 있음
	if ((b[0] + b[1] + b[2] + b[3]) == 4) return FRUSTUM_COMPLETELY_IN;

	// 일부분이 프러스텀에 있는 경우
	return FRUSTUM_PARTIALLY_IN;
}

void QuadTree::FrustumCull(TERRAINVERTEX * pHeightMap, Frustum * pFrustum)
{
	int ret;

	culled = FALSE;
	ret = IsInFrustum(pHeightMap, pFrustum);
	switch (ret)
	{
	case FRUSTUM_COMPLETELY_IN:	// 프러스텀에 완전포함, 하위노드 검색 필요없음
		AllInFrustum();
		return;
	case FRUSTUM_PARTIALLY_IN:		// 프러스텀에 일부포함, 하위노드 검색 필요함
		culled = FALSE;
		break;
	case FRUSTUM_OUT:				// 프러스텀에서 완전벗어남, 하위노드 검색 필요없음
		culled = TRUE;
		return;
	}
	if (child[0]) child[0]->FrustumCull(pHeightMap, pFrustum);
	if (child[1]) child[1]->FrustumCull(pHeightMap, pFrustum);
	if (child[2]) child[2]->FrustumCull(pHeightMap, pFrustum);
	if (child[3]) child[3]->FrustumCull(pHeightMap, pFrustum);
}

void QuadTree::BuildNeighborNode(QuadTree * pRoot, TERRAINVERTEX * pHeightMap, int cx)
{
	int				n;
	int				_0, _1, _2, _3;

	for (int i = 0; i < 4; i++)
	{
		_0 = corner[0];
		_1 = corner[1];
		_2 = corner[2];
		_3 = corner[3];
		// 이웃노드의 4개 코너값을 얻는다.
		n = GetNodeIndex(i, cx, _0, _1, _2, _3);
		// 코너값으로 이웃노드의 포인터를 얻어온다.
		if (n >= 0) neighbor[i] = pRoot->FindNode(pHeightMap, _0, _1, _2, _3);
	}

	// 자식노드로 재귀호출
	if (child[0])
	{
		child[0]->BuildNeighborNode(pRoot, pHeightMap, cx);
		child[1]->BuildNeighborNode(pRoot, pHeightMap, cx);
		child[2]->BuildNeighborNode(pRoot, pHeightMap, cx);
		child[3]->BuildNeighborNode(pRoot, pHeightMap, cx);
	}
}

BOOL QuadTree::BuildQuadTree(TERRAINVERTEX * pHeightMap)
{
	if (SubDivide())
	{
		// 좌측상단과, 우측 하단의 거리를 구한다.
		D3DXVECTOR3 v = *((D3DXVECTOR3*)(pHeightMap + corner[CORNER_TL])) -
			*((D3DXVECTOR3*)(pHeightMap + corner[CORNER_BR]));
		// v의 거리값이 이 노드를 감싸는 경계구의 지름이므로, 
		// 2로 나누어 반지름을 구한다.
		radius = D3DXVec3Length(&v) / 2.0f;
		child[CORNER_TL]->BuildQuadTree(pHeightMap);
		child[CORNER_TR]->BuildQuadTree(pHeightMap);
		child[CORNER_BL]->BuildQuadTree(pHeightMap);
		child[CORNER_BR]->BuildQuadTree(pHeightMap);
	}
	return TRUE;
}

QuadTree * QuadTree::FindNode(TERRAINVERTEX * pHeightMap, int _0, int _1, int _2, int _3)
{
	QuadTree*	p = NULL;
	// 일치하는 노드라면 노드값을 리턴
	if ((corner[0] == _0) && (corner[1] == _1) && (corner[2] == _2) && (corner[3] == _3))
		return this;

	// 자식 노드가 있가?
	if (child[0])
	{
		RECT	rc;
		POINT	pt;
		int n = (_0 + _1 + _2 + _3) / 4;

		// 현재 맵상에서의 위치
		pt.x = (int)pHeightMap[n].p.x;
		pt.y = (int)pHeightMap[n].p.z;

		// 4개의 코너값을 기준으로 자식노드의 맵 점유범위를 얻는다.
		SetRect(&rc, (int)pHeightMap[child[0]->corner[CORNER_TL]].p.x,
			(int)pHeightMap[child[0]->corner[CORNER_TL]].p.z,
			(int)pHeightMap[child[0]->corner[CORNER_BR]].p.x,
			(int)pHeightMap[child[0]->corner[CORNER_BR]].p.z);
		// pt값이 점유범위안에 있다면 자식노드로 들어간다.
		if (IsInRect(&rc, pt))
			return child[0]->FindNode(pHeightMap, _0, _1, _2, _3);

		SetRect(&rc, (int)pHeightMap[child[1]->corner[CORNER_TL]].p.x,
			(int)pHeightMap[child[1]->corner[CORNER_TL]].p.z,
			(int)pHeightMap[child[1]->corner[CORNER_BR]].p.x,
			(int)pHeightMap[child[1]->corner[CORNER_BR]].p.z);
		if (IsInRect(&rc, pt))
			return child[1]->FindNode(pHeightMap, _0, _1, _2, _3);

		SetRect(&rc, (int)pHeightMap[child[2]->corner[CORNER_TL]].p.x,
			(int)pHeightMap[child[2]->corner[CORNER_TL]].p.z,
			(int)pHeightMap[child[2]->corner[CORNER_BR]].p.x,
			(int)pHeightMap[child[2]->corner[CORNER_BR]].p.z);
		if (IsInRect(&rc, pt))
			return child[2]->FindNode(pHeightMap, _0, _1, _2, _3);

		SetRect(&rc, (int)pHeightMap[child[3]->corner[CORNER_TL]].p.x,
			(int)pHeightMap[child[3]->corner[CORNER_TL]].p.z,
			(int)pHeightMap[child[3]->corner[CORNER_BR]].p.x,
			(int)pHeightMap[child[3]->corner[CORNER_BR]].p.z);
		if (IsInRect(&rc, pt))
			return child[3]->FindNode(pHeightMap, _0, _1, _2, _3);
	}

	return NULL;
}

int QuadTree::GetNodeIndex(int ed, int cx, int & _0, int & _1, int & _2, int & _3)
{
	int		n, _a, _b, _c, _d, gap;
	_a = _0;
	_b = _1;
	_c = _2;
	_d = _3;
	gap = _b - _a;	// 현재 노드의 좌우폭값

	switch (ed)
	{
	case EDGE_UP:	// 위쪽 방향 이웃노드의 인덱스
		_0 = _a - cx * gap;
		_1 = _b - cx * gap;
		_2 = _a;
		_3 = _b;
		break;
	case EDGE_DN:	// 아래 방향 이웃노드의 인덱스
		_0 = _c;
		_1 = _d;
		_2 = _c + cx * gap;
		_3 = _d + cx * gap;
		break;
	case EDGE_LT:	// 좌측 방향 이웃노드의 인덱스
		_0 = _a - gap;
		_1 = _a;
		_2 = _c - gap;
		_3 = _c;
		break;
	case EDGE_RT:	// 우측 방향 이웃노드의 인덱스
		_0 = _b;
		_1 = _b + gap;
		_2 = _d;
		_3 = _d + gap;
		if ((_0 / cx) != (_a / cx)) return -1;
		if ((_1 / cx) != (_b / cx)) return -1;
		break;
	}

	n = (_0 + _1 + _2 + _3) / 4;	// 가운데 인덱스
	if (!IS_IN_RANGE(n, 0, cx * cx - 1)) return -1;

	return n;
}

QuadTree::QuadTree(int cx, int cy)
{
	int		i;
	parent = NULL;
	for (i = 0; i < 4; i++)
	{
		child[i] = NULL;
		neighbor[i] = NULL;
	}

	// 루트노드의 4개 코너값 설정
	corner[CORNER_TL] = 0;
	corner[CORNER_TR] = cx - 1;
	corner[CORNER_BL] = cx * (cy - 1);
	corner[CORNER_BR] = cx * cy - 1;
	center = (corner[CORNER_TL] + corner[CORNER_TR] +
		corner[CORNER_BL] + corner[CORNER_BR]) / 4;

	culled = FALSE;
	radius = 0.0f;
}

QuadTree::QuadTree(QuadTree * pParent)
{
	int		i;
	parent = pParent;
	center = 0;
	for (i = 0; i < 4; i++)
	{
		child[i] = NULL;
		neighbor[i] = NULL;
		corner[i] = 0;
	}

	culled = FALSE;
	radius = 0.0f;
}

QuadTree::~QuadTree()
{
	Destroy();
}

BOOL QuadTree::Build(TERRAINVERTEX * pHeightMap)
{
	// 쿼드트리 구축
	BuildQuadTree(pHeightMap);
	// 이웃노드 구축
	BuildNeighborNode(this, pHeightMap, corner[CORNER_TR] + 1);
	return TRUE;
}

int QuadTree::GenerateIndex(LPVOID pIndex, TERRAINVERTEX * pHeightMap, Frustum * pFrustum, float fLODRatio)
{
	// 먼저 프러스텀 컬링을 해서 컬링될 노드들을 배제한다.
	FrustumCull(pHeightMap, pFrustum);
	// 출력할 폴리곤의 인덱스를 생성한뒤, 폴리곤의 개수를 리턴한다.
	return GenTriIndex(0, pIndex, pHeightMap, pFrustum, fLODRatio);
}

QuadTree * QuadTree::AddChild(int nCornerTL, int nCornerTR, int nCornerBL, int nCornerBR)
{
	QuadTree*	pChild;

	pChild = new QuadTree(this);
	pChild->SetCorners(nCornerTL, nCornerTR, nCornerBL, nCornerBR);

	return pChild;
}

BOOL QuadTree::SetCorners(int nCornerTL, int nCornerTR, int nCornerBL, int nCornerBR)
{
	corner[CORNER_TL] = nCornerTL;
	corner[CORNER_TR] = nCornerTR;
	corner[CORNER_BL] = nCornerBL;
	corner[CORNER_BR] = nCornerBR;
	center = (corner[CORNER_TL] + corner[CORNER_TR] +
		corner[CORNER_BL] + corner[CORNER_BR]) / 4;
	return TRUE;
}

BOOL QuadTree::SubDivide()
{
	int		nTopEdgeCenter;
	int		nBottomEdgeCenter;
	int		nLeftEdgeCenter;
	int		nRightEdgeCenter;
	int		nCentralPoint;

	// 상단변 가운데
	nTopEdgeCenter = (corner[CORNER_TL] + corner[CORNER_TR]) / 2;
	// 하단변 가운데 
	nBottomEdgeCenter = (corner[CORNER_BL] + corner[CORNER_BR]) / 2;
	// 좌측변 가운데
	nLeftEdgeCenter = (corner[CORNER_TL] + corner[CORNER_BL]) / 2;
	// 우측변 가운데
	nRightEdgeCenter = (corner[CORNER_TR] + corner[CORNER_BR]) / 2;
	// 한가운데
	nCentralPoint = (corner[CORNER_TL] + corner[CORNER_TR] +
		corner[CORNER_BL] + corner[CORNER_BR]) / 4;

	// 더이상 분할이 불가능한가? 그렇다면 SubDivide() 종료
	if ((corner[CORNER_TR] - corner[CORNER_TL]) <= 1)
	{
		return FALSE;
	}

	// 4개의 자식노드 추가
	child[CORNER_TL] = AddChild(corner[CORNER_TL], nTopEdgeCenter, nLeftEdgeCenter, nCentralPoint);
	child[CORNER_TR] = AddChild(nTopEdgeCenter, corner[CORNER_TR], nCentralPoint, nRightEdgeCenter);
	child[CORNER_BL] = AddChild(nLeftEdgeCenter, nCentralPoint, corner[CORNER_BL], nBottomEdgeCenter);
	child[CORNER_BR] = AddChild(nCentralPoint, nRightEdgeCenter, nBottomEdgeCenter, corner[CORNER_BR]);

	return TRUE;
}

int QuadTree::GenTriIndex(int nTris, LPVOID pIndex, TERRAINVERTEX * pHeightMap, Frustum * pFrustum, float fLODRatio)
{
	// 컬링된 노드라면 그냥 리턴
	if (culled)
	{
		culled = FALSE;
		return nTris;
	}

#ifdef USE_INDEX16
	LPWORD p = ((LPWORD)pIndex) + nTris * 3;
#else
	LPDWORD p = ((LPDWORD)pIndex) + nTris * 3;
#endif

	// 현재 노드가 출력되어야 하는가?
	if (IsVisible(pHeightMap, pFrustum->GetPos(), fLODRatio))
	{
		// 만약 최하위 노드라면 부분분할(subdivide)이 불가능하므로 그냥 출력하고 리턴한다.
		if (corner[CORNER_TR] - corner[CORNER_TL] <= 1)
		{
			*p++ = corner[0];
			*p++ = corner[1];
			*p++ = corner[2];
			nTris++;
			*p++ = corner[2];
			*p++ = corner[1];
			*p++ = corner[3];
			nTris++;
			return nTris;
		}

		BOOL	b[4] = { 0,0,0,0 };
		// 상단 이웃노드(neightbor node)가 출력가능한가?
		if (neighbor[EDGE_UP]) b[EDGE_UP] = neighbor[EDGE_UP]->IsVisible(pHeightMap, pFrustum->GetPos(), fLODRatio);
		// 하단 이웃노드(neightbor node)가 출력가능한가?
		if (neighbor[EDGE_DN]) b[EDGE_DN] = neighbor[EDGE_DN]->IsVisible(pHeightMap, pFrustum->GetPos(), fLODRatio);
		// 좌측 이웃노드(neightbor node)가 출력가능한가?
		if (neighbor[EDGE_LT]) b[EDGE_LT] = neighbor[EDGE_LT]->IsVisible(pHeightMap, pFrustum->GetPos(), fLODRatio);
		// 우측 이웃노드(neightbor node)가 출력가능한가?
		if (neighbor[EDGE_RT]) b[EDGE_RT] = neighbor[EDGE_RT]->IsVisible(pHeightMap, pFrustum->GetPos(), fLODRatio);

		// 이웃노드들이 모두다 출력가능하다면 현재노드와 이웃노드들이 같은 LOD이므로 
		// 부분분할이 필요없다.
		if (b[EDGE_UP] && b[EDGE_DN] && b[EDGE_LT] && b[EDGE_RT])
		{
			*p++ = corner[0];
			*p++ = corner[1];
			*p++ = corner[2];
			nTris++;
			*p++ = corner[2];
			*p++ = corner[1];
			*p++ = corner[3];
			nTris++;
			return nTris;
		}

		int		n;

		if (!b[EDGE_UP]) // 상단 부분분할이 필요한가?
		{
			n = (corner[CORNER_TL] + corner[CORNER_TR]) / 2;
			*p++ = center; *p++ = corner[CORNER_TL]; *p++ = n; nTris++;
			*p++ = center; *p++ = n; *p++ = corner[CORNER_TR]; nTris++;
		}
		else	// 상단 부분분할이 필요없을 경우
		{
			*p++ = center; *p++ = corner[CORNER_TL]; *p++ = corner[CORNER_TR]; nTris++;
		}

		if (!b[EDGE_DN]) // 하단 부분분할이 필요한가?
		{
			n = (corner[CORNER_BL] + corner[CORNER_BR]) / 2;
			*p++ = center; *p++ = corner[CORNER_BR]; *p++ = n; nTris++;
			*p++ = center; *p++ = n; *p++ = corner[CORNER_BL]; nTris++;
		}
		else	// 하단 부분분할이 필요없을 경우
		{
			*p++ = center; *p++ = corner[CORNER_BR]; *p++ = corner[CORNER_BL]; nTris++;
		}

		if (!b[EDGE_LT]) // 좌측 부분분할이 필요한가?
		{
			n = (corner[CORNER_TL] + corner[CORNER_BL]) / 2;
			*p++ = center; *p++ = corner[CORNER_BL]; *p++ = n; nTris++;
			*p++ = center; *p++ = n; *p++ = corner[CORNER_TL]; nTris++;
		}
		else	// 좌측 부분분할이 필요없을 경우
		{
			*p++ = center; *p++ = corner[CORNER_BL]; *p++ = corner[CORNER_TL]; nTris++;
		}

		if (!b[EDGE_RT]) // 우측 부분분할이 필요한가?
		{
			n = (corner[CORNER_TR] + corner[CORNER_BR]) / 2;
			*p++ = center; *p++ = corner[CORNER_TR]; *p++ = n; nTris++;
			*p++ = center; *p++ = n; *p++ = corner[CORNER_BR]; nTris++;
		}
		else	// 우측 부분분할이 필요없을 경우
		{
			*p++ = center; *p++ = corner[CORNER_TR]; *p++ = corner[CORNER_BR]; nTris++;
		}

		return nTris;	// 이 노드 아래의 자식노드는 탐색할 필요없으므로 리턴!
	}

	// 자식 노드들 검색
	if (child[CORNER_TL]) nTris = child[CORNER_TL]->GenTriIndex(nTris, pIndex, pHeightMap, pFrustum, fLODRatio);
	if (child[CORNER_TR]) nTris = child[CORNER_TR]->GenTriIndex(nTris, pIndex, pHeightMap, pFrustum, fLODRatio);
	if (child[CORNER_BL]) nTris = child[CORNER_BL]->GenTriIndex(nTris, pIndex, pHeightMap, pFrustum, fLODRatio);
	if (child[CORNER_BR]) nTris = child[CORNER_BR]->GenTriIndex(nTris, pIndex, pHeightMap, pFrustum, fLODRatio);

	return nTris;
}

void QuadTree::Destroy()
{
	for (int i = 0; i < 4; i++) 
		SAFE_DELETE(child[i]);
}
