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

	// ��豸�ȿ� �ִ°�?
//	if( m_fRadius == 0.0f ) g_pLog->Log( "Index:[%d], Radius:[%f]",m_nCenter, m_fRadius );
	bInSphere = pFrustum->IsInSphere((D3DXVECTOR3*)(pHeightMap + center), radius);
	if (!bInSphere) return FRUSTUM_OUT;	// ��豸 �ȿ� ������ �������� �������� �׽�Ʈ ����

	// ����Ʈ���� 4���� ��� �������� �׽�Ʈ
	b[0] = pFrustum->IsIn((D3DXVECTOR3*)(pHeightMap + corner[0]));
	b[1] = pFrustum->IsIn((D3DXVECTOR3*)(pHeightMap + corner[1]));
	b[2] = pFrustum->IsIn((D3DXVECTOR3*)(pHeightMap + corner[2]));
	b[3] = pFrustum->IsIn((D3DXVECTOR3*)(pHeightMap + corner[3]));

	// 4����� �������� �ȿ� ����
	if ((b[0] + b[1] + b[2] + b[3]) == 4) return FRUSTUM_COMPLETELY_IN;

	// �Ϻκ��� �������ҿ� �ִ� ���
	return FRUSTUM_PARTIALLY_IN;
}

void QuadTree::FrustumCull(TERRAINVERTEX * pHeightMap, Frustum * pFrustum)
{
	int ret;

	culled = FALSE;
	ret = IsInFrustum(pHeightMap, pFrustum);
	switch (ret)
	{
	case FRUSTUM_COMPLETELY_IN:	// �������ҿ� ��������, ������� �˻� �ʿ����
		AllInFrustum();
		return;
	case FRUSTUM_PARTIALLY_IN:		// �������ҿ� �Ϻ�����, ������� �˻� �ʿ���
		culled = FALSE;
		break;
	case FRUSTUM_OUT:				// �������ҿ��� �������, ������� �˻� �ʿ����
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
		// �̿������ 4�� �ڳʰ��� ��´�.
		n = GetNodeIndex(i, cx, _0, _1, _2, _3);
		// �ڳʰ����� �̿������ �����͸� ���´�.
		if (n >= 0) neighbor[i] = pRoot->FindNode(pHeightMap, _0, _1, _2, _3);
	}

	// �ڽĳ��� ���ȣ��
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
		// ������ܰ�, ���� �ϴ��� �Ÿ��� ���Ѵ�.
		D3DXVECTOR3 v = *((D3DXVECTOR3*)(pHeightMap + corner[CORNER_TL])) -
			*((D3DXVECTOR3*)(pHeightMap + corner[CORNER_BR]));
		// v�� �Ÿ����� �� ��带 ���δ� ��豸�� �����̹Ƿ�, 
		// 2�� ������ �������� ���Ѵ�.
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
	// ��ġ�ϴ� ����� ��尪�� ����
	if ((corner[0] == _0) && (corner[1] == _1) && (corner[2] == _2) && (corner[3] == _3))
		return this;

	// �ڽ� ��尡 �ְ�?
	if (child[0])
	{
		RECT	rc;
		POINT	pt;
		int n = (_0 + _1 + _2 + _3) / 4;

		// ���� �ʻ󿡼��� ��ġ
		pt.x = (int)pHeightMap[n].p.x;
		pt.y = (int)pHeightMap[n].p.z;

		// 4���� �ڳʰ��� �������� �ڽĳ���� �� ���������� ��´�.
		SetRect(&rc, (int)pHeightMap[child[0]->corner[CORNER_TL]].p.x,
			(int)pHeightMap[child[0]->corner[CORNER_TL]].p.z,
			(int)pHeightMap[child[0]->corner[CORNER_BR]].p.x,
			(int)pHeightMap[child[0]->corner[CORNER_BR]].p.z);
		// pt���� ���������ȿ� �ִٸ� �ڽĳ��� ����.
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
	gap = _b - _a;	// ���� ����� �¿�����

	switch (ed)
	{
	case EDGE_UP:	// ���� ���� �̿������ �ε���
		_0 = _a - cx * gap;
		_1 = _b - cx * gap;
		_2 = _a;
		_3 = _b;
		break;
	case EDGE_DN:	// �Ʒ� ���� �̿������ �ε���
		_0 = _c;
		_1 = _d;
		_2 = _c + cx * gap;
		_3 = _d + cx * gap;
		break;
	case EDGE_LT:	// ���� ���� �̿������ �ε���
		_0 = _a - gap;
		_1 = _a;
		_2 = _c - gap;
		_3 = _c;
		break;
	case EDGE_RT:	// ���� ���� �̿������ �ε���
		_0 = _b;
		_1 = _b + gap;
		_2 = _d;
		_3 = _d + gap;
		if ((_0 / cx) != (_a / cx)) return -1;
		if ((_1 / cx) != (_b / cx)) return -1;
		break;
	}

	n = (_0 + _1 + _2 + _3) / 4;	// ��� �ε���
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

	// ��Ʈ����� 4�� �ڳʰ� ����
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
	// ����Ʈ�� ����
	BuildQuadTree(pHeightMap);
	// �̿���� ����
	BuildNeighborNode(this, pHeightMap, corner[CORNER_TR] + 1);
	return TRUE;
}

int QuadTree::GenerateIndex(LPVOID pIndex, TERRAINVERTEX * pHeightMap, Frustum * pFrustum, float fLODRatio)
{
	// ���� �������� �ø��� �ؼ� �ø��� ������ �����Ѵ�.
	FrustumCull(pHeightMap, pFrustum);
	// ����� �������� �ε����� �����ѵ�, �������� ������ �����Ѵ�.
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

	// ��ܺ� ���
	nTopEdgeCenter = (corner[CORNER_TL] + corner[CORNER_TR]) / 2;
	// �ϴܺ� ��� 
	nBottomEdgeCenter = (corner[CORNER_BL] + corner[CORNER_BR]) / 2;
	// ������ ���
	nLeftEdgeCenter = (corner[CORNER_TL] + corner[CORNER_BL]) / 2;
	// ������ ���
	nRightEdgeCenter = (corner[CORNER_TR] + corner[CORNER_BR]) / 2;
	// �Ѱ��
	nCentralPoint = (corner[CORNER_TL] + corner[CORNER_TR] +
		corner[CORNER_BL] + corner[CORNER_BR]) / 4;

	// ���̻� ������ �Ұ����Ѱ�? �׷��ٸ� SubDivide() ����
	if ((corner[CORNER_TR] - corner[CORNER_TL]) <= 1)
	{
		return FALSE;
	}

	// 4���� �ڽĳ�� �߰�
	child[CORNER_TL] = AddChild(corner[CORNER_TL], nTopEdgeCenter, nLeftEdgeCenter, nCentralPoint);
	child[CORNER_TR] = AddChild(nTopEdgeCenter, corner[CORNER_TR], nCentralPoint, nRightEdgeCenter);
	child[CORNER_BL] = AddChild(nLeftEdgeCenter, nCentralPoint, corner[CORNER_BL], nBottomEdgeCenter);
	child[CORNER_BR] = AddChild(nCentralPoint, nRightEdgeCenter, nBottomEdgeCenter, corner[CORNER_BR]);

	return TRUE;
}

int QuadTree::GenTriIndex(int nTris, LPVOID pIndex, TERRAINVERTEX * pHeightMap, Frustum * pFrustum, float fLODRatio)
{
	// �ø��� ����� �׳� ����
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

	// ���� ��尡 ��µǾ�� �ϴ°�?
	if (IsVisible(pHeightMap, pFrustum->GetPos(), fLODRatio))
	{
		// ���� ������ ����� �κк���(subdivide)�� �Ұ����ϹǷ� �׳� ����ϰ� �����Ѵ�.
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
		// ��� �̿����(neightbor node)�� ��°����Ѱ�?
		if (neighbor[EDGE_UP]) b[EDGE_UP] = neighbor[EDGE_UP]->IsVisible(pHeightMap, pFrustum->GetPos(), fLODRatio);
		// �ϴ� �̿����(neightbor node)�� ��°����Ѱ�?
		if (neighbor[EDGE_DN]) b[EDGE_DN] = neighbor[EDGE_DN]->IsVisible(pHeightMap, pFrustum->GetPos(), fLODRatio);
		// ���� �̿����(neightbor node)�� ��°����Ѱ�?
		if (neighbor[EDGE_LT]) b[EDGE_LT] = neighbor[EDGE_LT]->IsVisible(pHeightMap, pFrustum->GetPos(), fLODRatio);
		// ���� �̿����(neightbor node)�� ��°����Ѱ�?
		if (neighbor[EDGE_RT]) b[EDGE_RT] = neighbor[EDGE_RT]->IsVisible(pHeightMap, pFrustum->GetPos(), fLODRatio);

		// �̿������� ��δ� ��°����ϴٸ� ������� �̿������� ���� LOD�̹Ƿ� 
		// �κк����� �ʿ����.
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

		if (!b[EDGE_UP]) // ��� �κк����� �ʿ��Ѱ�?
		{
			n = (corner[CORNER_TL] + corner[CORNER_TR]) / 2;
			*p++ = center; *p++ = corner[CORNER_TL]; *p++ = n; nTris++;
			*p++ = center; *p++ = n; *p++ = corner[CORNER_TR]; nTris++;
		}
		else	// ��� �κк����� �ʿ���� ���
		{
			*p++ = center; *p++ = corner[CORNER_TL]; *p++ = corner[CORNER_TR]; nTris++;
		}

		if (!b[EDGE_DN]) // �ϴ� �κк����� �ʿ��Ѱ�?
		{
			n = (corner[CORNER_BL] + corner[CORNER_BR]) / 2;
			*p++ = center; *p++ = corner[CORNER_BR]; *p++ = n; nTris++;
			*p++ = center; *p++ = n; *p++ = corner[CORNER_BL]; nTris++;
		}
		else	// �ϴ� �κк����� �ʿ���� ���
		{
			*p++ = center; *p++ = corner[CORNER_BR]; *p++ = corner[CORNER_BL]; nTris++;
		}

		if (!b[EDGE_LT]) // ���� �κк����� �ʿ��Ѱ�?
		{
			n = (corner[CORNER_TL] + corner[CORNER_BL]) / 2;
			*p++ = center; *p++ = corner[CORNER_BL]; *p++ = n; nTris++;
			*p++ = center; *p++ = n; *p++ = corner[CORNER_TL]; nTris++;
		}
		else	// ���� �κк����� �ʿ���� ���
		{
			*p++ = center; *p++ = corner[CORNER_BL]; *p++ = corner[CORNER_TL]; nTris++;
		}

		if (!b[EDGE_RT]) // ���� �κк����� �ʿ��Ѱ�?
		{
			n = (corner[CORNER_TR] + corner[CORNER_BR]) / 2;
			*p++ = center; *p++ = corner[CORNER_TR]; *p++ = n; nTris++;
			*p++ = center; *p++ = n; *p++ = corner[CORNER_BR]; nTris++;
		}
		else	// ���� �κк����� �ʿ���� ���
		{
			*p++ = center; *p++ = corner[CORNER_TR]; *p++ = corner[CORNER_BR]; nTris++;
		}

		return nTris;	// �� ��� �Ʒ��� �ڽĳ��� Ž���� �ʿ�����Ƿ� ����!
	}

	// �ڽ� ���� �˻�
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
