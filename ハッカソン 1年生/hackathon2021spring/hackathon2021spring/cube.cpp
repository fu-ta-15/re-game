//===============================================
//
// ボタン処理 (Button.cpp)
// Author : 樋宮匠
//
//===============================================

//========================
// インクルードファイル
//========================
#include "Cube.h"
#include "manager.h"
#include "renderer.h"

//========================
// 静的メンバ変数宣言
//========================
LPD3DXMESH	CCube::m_pMesh[MAX_CUBE] = {};
LPD3DXBUFFER CCube::m_pBuffMat[MAX_CUBE] = {};
DWORD CCube::m_nNumMat[MAX_CUBE] = {};
LPDIRECT3DTEXTURE9 CCube::m_pTexture = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CCube::CCube()
{
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// デストラクタ
// Author : 樋宮匠
//=============================================================================
CCube::~CCube()
{
}

//=============================================================================
// 初期化処理
// Author : 樋宮匠
//=============================================================================
HRESULT CCube::Init(TYPE_CUBE type)
{
	CModelHimiya::Init();
	m_type = type;

	BindMesh(m_pMesh[m_type], m_pBuffMat[m_type], m_nNumMat[m_type]);
	BindTexture(m_pTexture);

	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	return S_OK;
}

//=============================================================================
// 終了処理
// Author : 樋宮匠
//=============================================================================
void CCube::Uninit(void)
{
	CModelHimiya::Uninit();
}

//=============================================================================
// 更新処理
// Author : 樋宮匠
//=============================================================================
void CCube::Update(void)
{
	CModelHimiya::Update();
}

//=============================================================================
// 描画処理
// Author : 樋宮匠
//=============================================================================
void CCube::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	CModelHimiya::Draw();
}

//=============================================================================
// テクスチャ・モデルデータ読み込み処理
// Author : 樋宮匠
//=============================================================================
HRESULT CCube::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXLoadMeshFromX(LPCSTR("./data/model/defaultBox.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[DIRT], NULL, &m_nNumMat[DIRT], &m_pMesh[DIRT]);
	D3DXLoadMeshFromX(LPCSTR("./data/model/stoneBreak.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[STONE_BREAK], NULL, &m_nNumMat[STONE_BREAK], &m_pMesh[STONE_BREAK]);
	D3DXLoadMeshFromX(LPCSTR("./data/model/stoneUnbreak.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[STONE_UNBREAK], NULL, &m_nNumMat[STONE_UNBREAK], &m_pMesh[STONE_UNBREAK]);
	D3DXLoadMeshFromX(LPCSTR("./data/model/tree.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[TREE], NULL, &m_nNumMat[TREE], &m_pMesh[TREE]);

	return S_OK;
}

//=============================================================================
// テクスチャ・モデルデータ破棄処理
// Author : 樋宮匠
//=============================================================================
void CCube::Unload(void)
{
	for (int nCount = 0; nCount < MAX_CUBE; nCount++)
	{
		if (m_pMesh[nCount] != NULL)
		{
			m_pMesh[nCount]->Release();
			m_pMesh[nCount] = NULL;
		}
		if (m_pBuffMat[nCount] != NULL)
		{
			m_pBuffMat[nCount]->Release();
			m_pBuffMat[nCount] = NULL;
		}
	}

	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// インスタンス生成処理
// Author : 樋宮匠
//=============================================================================
CCube * CCube::Create(TYPE_CUBE type, D3DXVECTOR3 pos)
{
	CCube *pCube = NULL;
	pCube = new CCube;
	pCube->Init(type);
	pCube->SetPos(pos);

	switch (type)
	{
	case DIRT:
		pCube->SetObjType(OBJ_TYPE_DIRT);
		break;
	case STONE_BREAK:
		pCube->SetObjType(OBJ_TYPE_STONE_BREAK);
		break;
	case STONE_UNBREAK:
		pCube->SetObjType(OBJ_TYPE_STONE_UNBREAK);
		break;
	case TREE:
		pCube->SetObjType(OBJ_TYPE_TREE);
		break;
	default:
		break;
	}

	return pCube;
}