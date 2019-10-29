#include "Terrain.h"
#include "GraphicSystem.h"
#include "Dib.h"

Terrain::Terrain()
{
	cxDIB = 0;
	czDIB = 0;
	cyDIB = 0;
	scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	heightMap = NULL;
	d3dDevice = NULL;
	for (int i = 0; i < MAX_TERRAIN_TEX; i++) 
		texture[i] = NULL;
	vertexBuffer = NULL;
	indexBuffer = NULL;
	trianglesNum = 0;
	quadTree = NULL;
}

Terrain::~Terrain()
{
	Destroy();
}

HRESULT Terrain::Create(LPDIRECT3DDEVICE9 pDev, D3DXVECTOR3 * pvfScale, float fLODRatio, const char * lpBMPFilename, const char * lpTexFilename[MAX_TERRAIN_TEX])
{
	vPos = { 0.0f , 0.0f, 0.0f };
	D3DXMatrixTranslation(&matTrans, vPos.x, vPos.y, vPos.z);

	d3dDevice = pDev;
	scale = *pvfScale;
	LODRatio = fLODRatio;
	if (FAILED(BuildHeightMap(lpBMPFilename)))
	{
		Destroy(); 
		return E_FAIL;
	}
		
	if (FAILED(LoadTextures(lpTexFilename)))
	{
		Destroy();
		return E_FAIL;
	}
		
	if (FAILED(CreateVIB())) 
	{
		Destroy(); 
		return E_FAIL; 
	}

	quadTree = new QuadTree(cxDIB, czDIB);
	if (FAILED(BuildQuadTree())) 
	{
		Destroy(); 
		return E_FAIL; 
	}

	return S_OK;
}

HRESULT Terrain::Destroy()
{
	SAFE_DELETE(quadTree);
	SAFE_DELETE_ARRAY(heightMap);
	SAFE_RELEASE(vertexBuffer);
	SAFE_RELEASE(indexBuffer);
	for (int i = 0; i < 4; i++) 
		SAFE_RELEASE(texture[i]);

	return S_OK;
}

HRESULT Terrain::LoadTextures(const char * lpTexFilename[MAX_TERRAIN_TEX])
{
	for (int i = 0; i < 4; i++)
		D3DXCreateTextureFromFile(d3dDevice, lpTexFilename[i], &texture[i]);

	return S_OK;
}

HRESULT Terrain::BuildHeightMap(const char * lpFilename)
{
	int	 n;
	LPBYTE pDIB = DibLoadHandle(lpFilename);
	if (!pDIB) return E_FAIL;

	cxDIB = DIB_CX(pDIB);
	czDIB = DIB_CY(pDIB);

	// ���Ӱ� �߰��� ��ƾ
	// ���⼭ m_cxDIB�� m_czDIB�� (2^n+1)�� �ƴѰ�� E_FAIL�� ��ȯ�ϵ��� ������ ��
	n = Log2(cxDIB);
	if ((Pow2(n) + 1) != cxDIB) 
		return E_FAIL;
	n = Log2(czDIB);
	if ((Pow2(n) + 1) != czDIB) 
		return E_FAIL;

	heightMap = new TERRAINVERTEX[cxDIB * czDIB];

	TERRAINVERTEX v;
	for (int z = 0; z < czDIB; z++)
	{
		for (int x = 0; x < cxDIB; x++)
		{
			v.p.x = (float)((x - cxDIB / 2) * scale.x);
			v.p.z = -(float)((z - czDIB / 2) * scale.z);
			v.p.y = (float)(*(DIB_DATAXY_INV(pDIB, x, z))) * scale.y;
			D3DXVec3Normalize(&v.n, &v.p);
			v.t.x = (float)x / (float)(cxDIB - 1);
			v.t.y = (float)z / (float)(czDIB - 1);
			heightMap[x + z * czDIB] = v;
		}
	}

	DibDeleteHandle(pDIB);
	return S_OK;
}

HRESULT Terrain::BuildQuadTree()
{
	quadTree->Build(heightMap);
	return S_OK;
}

HRESULT Terrain::CreateVIB()
{
	// VB����
	if (FAILED(d3dDevice->CreateVertexBuffer(cxDIB * czDIB * sizeof(TERRAINVERTEX),
		0, TERRAINVERTEX::FVF, D3DPOOL_DEFAULT, &vertexBuffer, NULL)))
	{
		Destroy();
		return E_FAIL;
	}
	VOID* pVertices;
	if (FAILED(vertexBuffer->Lock(0, cxDIB * czDIB * sizeof(TERRAINVERTEX), (void**)&pVertices, 0)))
	{
		Destroy();
		return E_FAIL;
	}
	memcpy(pVertices, heightMap, cxDIB * czDIB * sizeof(TERRAINVERTEX));
	vertexBuffer->Unlock();

#ifdef USE_INDEX16
	// IB����
	if (FAILED(d3dDevice->CreateIndexBuffer((cxDIB - 1) * (czDIB - 1) * 2 * sizeof(TRIINDEX), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &indexBuffer, NULL)))
	{
		Destroy();
		return E_FAIL;
	}
	//g_pLog->Log( "Using 16bit index buffer..." );
#else
	// IB����
	if (FAILED(d3dDevice->CreateIndexBuffer((cxDIB - 1) * (czDIB - 1) * 2 * sizeof(TRIINDEX), 0, D3DFMT_INDEX32, D3DPOOL_DEFAULT, &indexBuffer, NULL)))
	{
		Destroy();
		return E_FAIL;
	}

	//g_pLog->Log("Using 32bit index buffer...");
#endif
	return S_OK;
}

HRESULT Terrain::Render()
{
	DXDEVICE->SetTransform(D3DTS_WORLD, &matTrans);
	//d3dDevice->SetTexture(0, texture[0]);								// 0�� �ؽ��� ���������� �ؽ��� ����(�����)
	//d3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// 0�� �ؽ�ó ���������� Ȯ�� ����
	//d3dDevice->SetTextureStageState(0, D3DTSS_TEXCOORDINDEX, 0);		// 0�� �ؽ�ó : 0�� �ؽ�ó �ε��� ���

	//d3dDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	//d3dDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	//d3dDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	//d3dDevice->SetStreamSource(0, vertexBuffer, 0, sizeof(TERRAINVERTEX));
	//d3dDevice->SetFVF(TERRAINVERTEX::FVF);
	//d3dDevice->SetIndices(indexBuffer);
	//d3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, cxDIB * czDIB, 0, trianglesNum);

	d3dDevice->SetTexture(0, texture[0]);										// 0�� �ؽ��� ���������� �ؽ��� ����(�����)
	d3dDevice->SetTexture(1, texture[1]);										// 1�� �ؽ��� ���������� �ؽ��� ����(������)
	d3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);			// 0�� �ؽ�ó ���������� Ȯ�� ����
	d3dDevice->SetSamplerState(1, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);			// 0�� �ؽ�ó ���������� Ȯ�� ����
	d3dDevice->SetTextureStageState(0, D3DTSS_TEXCOORDINDEX, 0);				// 0�� �ؽ�ó : 0�� �ؽ�ó �ε��� ���
	d3dDevice->SetTextureStageState(1, D3DTSS_TEXCOORDINDEX, 0);		 		// 1�� �ؽ�ó : 0�� �ؽ�ó �ε��� ���

	d3dDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);		// MODULATE�� ���´�.
	d3dDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);		// �ؽ�ó
	d3dDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);		// ������
	d3dDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_MODULATE2X);		// MODULATE2�� ���´�.
	d3dDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);		// �ؽ�ó
	d3dDevice->SetTextureStageState(1, D3DTSS_COLORARG2, D3DTA_CURRENT);		// �����
	d3dDevice->SetStreamSource(0, vertexBuffer, 0, sizeof(TERRAINVERTEX));
	d3dDevice->SetFVF(TERRAINVERTEX::FVF);
	d3dDevice->SetIndices(indexBuffer);
	d3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, cxDIB * czDIB, 0, trianglesNum);

	return S_OK;
}

HRESULT Terrain::Draw(Frustum * pFrustum)
{
	LPDWORD		pI;

	if (FAILED(indexBuffer->Lock(0, (cxDIB - 1) * (czDIB - 1) * 2 * sizeof(TRIINDEX), (void**)&pI, 0)))
		return E_FAIL;
	trianglesNum = quadTree->GenerateIndex(pI, heightMap, pFrustum, LODRatio);
	indexBuffer->Unlock();
	//	g_pLog->Log( "Triangles=%d", m_nTriangles );
	Render();

	return S_OK;
}
