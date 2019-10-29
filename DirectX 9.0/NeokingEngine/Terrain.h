#pragma once
#include "3DBase.h"
#include "QuadTree.h"
#include "Macro.h"

#define MAX_TERRAIN_TEX	4

/**
 * @brief 지형관리 클래스
 */
class Terrain
{
private:
	D3DXVECTOR3				vPos;						// 물체의 현재 위치
	D3DXMATRIXA16			matTrans;					// 물체 위치 행렬

	int						cxDIB;						// DIB의 가로픽셀수
	int						czDIB;						// DIB의 세로픽셀수
	int						cyDIB;						// DIB의 최대높이값(즉 0 ~ 255사이의 값)
	D3DXVECTOR3				scale;						// x scale, y scale, z scale
	TERRAINVERTEX*			heightMap;					// 높이맵의 정점배열
	LPDIRECT3DDEVICE9		d3dDevice;					// 출력용 D3D디바이스
	LPDIRECT3DTEXTURE9		texture[MAX_TERRAIN_TEX];	// 텍스처
	LPDIRECT3DVERTEXBUFFER9	vertexBuffer;				// 지형출력용 정점버퍼
	LPDIRECT3DINDEXBUFFER9	indexBuffer;				// 지형출력용 인덱스버퍼
	int						trianglesNum;				// 출력할 삼각형의 개수
	QuadTree*				quadTree;					// 쿼드트리 객체의 포인터
	float					LODRatio;					// LOD처리시에 사용될 값

public:
	Terrain();
	virtual ~Terrain();

	/**
	 * @brief 지형객체를 초기화한다.
	 * @param pDev : 출력용 D3D디바이스
	 * @param pvfScale : 높이맵의 x,y,z값에 곱할 척도값(scale vector)
	 * @param fLODRatio : LOD처리시에 사용될 값
	 * @param lpBMPFilename : 높이맵용 BMP파일명
	 * @param lpTexFilename : 출력용 D3D디바이스
	 */
	HRESULT		Create(LPDIRECT3DDEVICE9 pDev, D3DXVECTOR3* pvfScale, float fLODRatio, const char* lpBMPFilename, const char* lpTexFilename[MAX_TERRAIN_TEX]);

	// ZTerrain내부에서 사용되는 함수들
private:
	// 지형객체를 메모리에서 소거한다.
	HRESULT		Destroy();

	// 지형객체에서 사용할 텍스처를 읽어들인다.
	HRESULT		LoadTextures(const char* lpTexFilename[MAX_TERRAIN_TEX]);

	// BMP파일을 열어서 높이맵을 생성한다.
	HRESULT		BuildHeightMap(const char* lpFilename);

	// BMP파일의 크기에 맞춰서 쿼드트리를 생성한다.
	HRESULT		BuildQuadTree();

	// 정점, 인덱스 버퍼를 생성한다.
	HRESULT		CreateVIB();

	// 화면에 지형을 출력한다.
	HRESULT		Render();
public:
	// x, z위치의 정점값을 얻어낸다.
	TERRAINVERTEX*	GetVertex(int x, int z) { return (heightMap + x + z * cxDIB); }

	// x, z위치의 높이(y)값만 얻어내다.
	float		GetHeight(int x, int z) { return (GetVertex(x, z))->p.y; }

	//D3DXVECTOR3 GetNormal(int x, int y) { return D3DXVECTOR3(0, 0, GetVertex(x, z))}

	// 높이맵 BMP파일의 가로픽셀수
	int			GetCXDIB() { return cxDIB; }

	// 높이맵 BMP파일의 가로픽셀수
	int			GetCZDIB() { return czDIB; }

	// 높이맵의 실제 x축 폭(column)값
	float		GetCXTerrain() { return cxDIB * scale.x; }

	// 높이맵의 실제 y축 높이(height)값
	float		GetCYTerrain() { return cyDIB * scale.y; }

	// 높이맵의 실제 z축 길이(row)값
	float		GetCZTerrain() { return czDIB * scale.z; }

	// 화면에 지형을 출력한다.
	HRESULT		Draw(Frustum* pFrustum);
};

