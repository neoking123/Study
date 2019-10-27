#pragma once
#include "3DBase.h"
#include "Frustum.h"

/**
 * @brief QuadTree�� ���̽� Ŭ����
 */
class QuadTree
{
public:
	// ����Ʈ���� �����Ǵ� 4���� �ڳʰ��� ���� �����
	enum CornerType { CORNER_TL, CORNER_TR, CORNER_BL, CORNER_BR };

	// �̿���� ó���� �����
	enum { EDGE_UP, EDGE_DN, EDGE_LT, EDGE_RT };

	// ����Ʈ���� �������Ұ��� ����
	enum QuadLocation {
		FRUSTUM_OUT = 0,				// �������ҿ��� �������
		FRUSTUM_PARTIALLY_IN = 1,		// �������ҿ� �κ�����
		FRUSTUM_COMPLETELY_IN = 2,		// �������ҿ� ��������
		FRUSTUM_UNKNOWN = -1
	};

private:
	QuadTree*	child[4];		// QuadTree�� 4���� �ڽĳ��

	QuadTree*	parent;			// Triangle Crack(Popping)�� �������ؼ� ����Ѵ�.
	QuadTree*	neighbor[4];	// Triangle Crack(Popping)�� �������ؼ� ����Ѵ�.

	int			center;			// QuadTree�� ������ ù��° ��
	int			corner[4];		// QuadTree�� ������ �ι�° ��
								//    TopLeft(TL)      TopRight(TR)
								//              0------1
								//              |      |
								//              |      |
								//              2------3
								// BottomLeft(BL)      BottomRight(BR)
	BOOL		culled;			// �������ҿ��� �ø��� ����ΰ�?
	float		radius;			// ��带 ���δ� ��豸(bounding sphere)�� ������
	
private:
	// �ڽ� ��带 �߰��Ѵ�.
	QuadTree*	AddChild(int nCornerTL, int nCornerTR, int nCornerBL, int nCornerBR);

	// 4���� �ڳʰ��� �����Ѵ�.
	BOOL		SetCorners(int nCornerTL, int nCornerTR, int nCornerBL, int nCornerBR);

	// Quadtree�� 4���� ���� Ʈ���� �κк���(subdivide)�Ѵ�.
	BOOL		SubDivide();		// Quadtree�� subdivide�Ѵ�.

	// ����� �������� �ε����� �����Ѵ�.
	int			GenTriIndex(int nTris, LPVOID pIndex, TERRAINVERTEX* pHeightMap, Frustum* pFrustum, float fLODRatio);

	// �޸𸮿��� ����Ʈ���� �����Ѵ�.
	void		Destroy();

	// ���� ������ �Ÿ��� ���Ѵ�.
	float		GetDistance(D3DXVECTOR3* pv1, D3DXVECTOR3* pv2)
	{
		return D3DXVec3Length(&(*pv2 - *pv1));
	}

	// ī�޶�� ���� ������ �Ÿ����� �������� LOD���� ���Ѵ�.
	int			GetLODLevel(TERRAINVERTEX* pHeightMap, D3DXVECTOR3* pCamera, float fLODRatio)
	{
		float d = GetDistance((D3DXVECTOR3*)(pHeightMap + center), pCamera);
		return max((int)(d * fLODRatio), 1);
	}

	// ��� �ڽĳ���� m_bCulled���� FALSE�� �Ѵ�
	void		AllInFrustum();

	// �����尡 �������ҿ� ���ԵǴ°�?
	int			IsInFrustum(TERRAINVERTEX* pHeightMap, Frustum* pFrustum);

	// _IsInFrustum()�Լ��� ����� ���� �������� �ø� ����
	void		FrustumCull(TERRAINVERTEX* pHeightMap, Frustum* pFrustum);

	// �̿���带 �����.(�ﰢ�� ������ ������)
	void		BuildNeighborNode(QuadTree* pRoot, TERRAINVERTEX* pHeightMap, int cx);

	// ����Ʈ���� �����.(Build()�Լ����� �Ҹ���)
	BOOL		BuildQuadTree(TERRAINVERTEX* pHeightMap);

	// ����Ʈ���� �˻��ؼ� 4�� �ڳʰ��� ��ġ�ϴ� ��带 ã�´�.
	QuadTree*	FindNode(TERRAINVERTEX* pHeightMap, int _0, int _1, int _2, int _3);

	// 4�� ����(���,�ϴ�,����,����)�� �̿���� �ε����� ���Ѵ�.
	int			GetNodeIndex(int ed, int cx, int& _0, int& _1, int& _2, int& _3);

public:

	// ���� ��Ʈ��� ������
	QuadTree(int cx, int cy);

	// ���� �ڽĳ�� ������
	QuadTree(QuadTree* pParent);

	// �Ҹ���
	~QuadTree();

	// ���� ��尡 Culling�Ȱ��ΰ�?
	BOOL		IsCulled() { return culled; }

	// ���� ��尡 LOD������� ����  ����� ������ ����ΰ�?
	BOOL		IsVisible(TERRAINVERTEX* pHeightMap, D3DXVECTOR3* pCamera, float fLODRatio)
	{
		return ((corner[CORNER_TR] - corner[CORNER_TL]) <= GetLODLevel(pHeightMap, pCamera, fLODRatio));
	}

	// QuadTree�� �����Ѵ�.
	BOOL		Build(TERRAINVERTEX* pHeightMap);	// ������ ������ �������� QuadTree�� build�Ѵ�.

	// �ڳ� �ε��� ���� ���´�.
	void		GetCorner(int& _0, int& _1, int& _2, int& _3)
	{
		_0 = corner[0]; _1 = corner[1]; _2 = corner[2]; _3 = corner[3];
	}

	//	�ﰢ���� �ε����� �����, ����� �ﰢ���� ������ ��ȯ�Ѵ�.
	int			GenerateIndex(LPVOID pIndex, TERRAINVERTEX* pHeightMap, Frustum* pFrustum, float fLODRatio);
};

