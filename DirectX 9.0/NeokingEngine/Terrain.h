#pragma once
#include "3DBase.h"
#include "QuadTree.h"
#include "Macro.h"

#define MAX_TERRAIN_TEX	4

/**
 * @brief �������� Ŭ����
 */
class Terrain
{
private:
	D3DXVECTOR3				vPos;						// ��ü�� ���� ��ġ
	D3DXMATRIXA16			matTrans;					// ��ü ��ġ ���

	int						cxDIB;						// DIB�� �����ȼ���
	int						czDIB;						// DIB�� �����ȼ���
	int						cyDIB;						// DIB�� �ִ���̰�(�� 0 ~ 255������ ��)
	D3DXVECTOR3				scale;						// x scale, y scale, z scale
	TERRAINVERTEX*			heightMap;					// ���̸��� �����迭
	LPDIRECT3DDEVICE9		d3dDevice;					// ��¿� D3D����̽�
	LPDIRECT3DTEXTURE9		texture[MAX_TERRAIN_TEX];	// �ؽ�ó
	LPDIRECT3DVERTEXBUFFER9	vertexBuffer;				// ������¿� ��������
	LPDIRECT3DINDEXBUFFER9	indexBuffer;				// ������¿� �ε�������
	int						trianglesNum;				// ����� �ﰢ���� ����
	QuadTree*				quadTree;					// ����Ʈ�� ��ü�� ������
	float					LODRatio;					// LODó���ÿ� ���� ��

public:
	Terrain();
	virtual ~Terrain();

	/**
	 * @brief ������ü�� �ʱ�ȭ�Ѵ�.
	 * @param pDev : ��¿� D3D����̽�
	 * @param pvfScale : ���̸��� x,y,z���� ���� ô����(scale vector)
	 * @param fLODRatio : LODó���ÿ� ���� ��
	 * @param lpBMPFilename : ���̸ʿ� BMP���ϸ�
	 * @param lpTexFilename : ��¿� D3D����̽�
	 */
	HRESULT		Create(LPDIRECT3DDEVICE9 pDev, D3DXVECTOR3* pvfScale, float fLODRatio, const char* lpBMPFilename, const char* lpTexFilename[MAX_TERRAIN_TEX]);

	// ZTerrain���ο��� ���Ǵ� �Լ���
private:
	// ������ü�� �޸𸮿��� �Ұ��Ѵ�.
	HRESULT		Destroy();

	// ������ü���� ����� �ؽ�ó�� �о���δ�.
	HRESULT		LoadTextures(const char* lpTexFilename[MAX_TERRAIN_TEX]);

	// BMP������ ��� ���̸��� �����Ѵ�.
	HRESULT		BuildHeightMap(const char* lpFilename);

	// BMP������ ũ�⿡ ���缭 ����Ʈ���� �����Ѵ�.
	HRESULT		BuildQuadTree();

	// ����, �ε��� ���۸� �����Ѵ�.
	HRESULT		CreateVIB();

	// ȭ�鿡 ������ ����Ѵ�.
	HRESULT		Render();
public:
	// x, z��ġ�� �������� ����.
	TERRAINVERTEX*	GetVertex(int x, int z) { return (heightMap + x + z * cxDIB); }

	// x, z��ġ�� ����(y)���� ����.
	float		GetHeight(int x, int z) { return (GetVertex(x, z))->p.y; }

	//D3DXVECTOR3 GetNormal(int x, int y) { return D3DXVECTOR3(0, 0, GetVertex(x, z))}

	// ���̸� BMP������ �����ȼ���
	int			GetCXDIB() { return cxDIB; }

	// ���̸� BMP������ �����ȼ���
	int			GetCZDIB() { return czDIB; }

	// ���̸��� ���� x�� ��(column)��
	float		GetCXTerrain() { return cxDIB * scale.x; }

	// ���̸��� ���� y�� ����(height)��
	float		GetCYTerrain() { return cyDIB * scale.y; }

	// ���̸��� ���� z�� ����(row)��
	float		GetCZTerrain() { return czDIB * scale.z; }

	// ȭ�鿡 ������ ����Ѵ�.
	HRESULT		Draw(Frustum* pFrustum);
};

