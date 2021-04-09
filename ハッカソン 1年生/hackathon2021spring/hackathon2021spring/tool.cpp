//===============================================
//
// ボタン処理 (Button.cpp)
// Author : 樋宮匠
//
//===============================================

//========================
// インクルードファイル
//========================
#include "tool.h"
#include "manager.h"
#include "renderer.h"

//========================
// 静的メンバ変数宣言
//========================
LPD3DXMESH	CTool::m_pMesh[MAX_TOOL] = {};
LPD3DXBUFFER CTool::m_pBuffMat[MAX_TOOL] = {};
DWORD CTool::m_nNumMat[MAX_TOOL] = {};
LPDIRECT3DTEXTURE9 CTool::m_pTexture = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CTool::CTool()
{
}

//=============================================================================
// デストラクタ
// Author : 樋宮匠
//=============================================================================
CTool::~CTool()
{
}

//=============================================================================
// 初期化処理
// Author : 樋宮匠
//=============================================================================
HRESULT CTool::Init(TYPE_TOOL type)
{
	CModelHimiya::Init();
	m_type = type;

	BindMesh(m_pMesh[m_type], m_pBuffMat[m_type], m_nNumMat[m_type]);
	BindTexture(m_pTexture);

	SetRot(D3DXVECTOR3(0.0f, D3DXToRadian(90), 0.0f));

	return S_OK;
}

//=============================================================================
// 終了処理
// Author : 樋宮匠
//=============================================================================
void CTool::Uninit(void)
{
	CModelHimiya::Uninit();
}

//=============================================================================
// 更新処理
// Author : 樋宮匠
//=============================================================================
void CTool::Update(void)
{
	CModelHimiya::Update();
}

//=============================================================================
// 描画処理
// Author : 樋宮匠
//=============================================================================
void CTool::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	CModelHimiya::Draw();
}

//=============================================================================
// テクスチャ・モデルデータ読み込み処理
// Author : 樋宮匠
//=============================================================================
HRESULT CTool::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXLoadMeshFromX(LPCSTR("./data/model/pickaxe.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[PICKAXE], NULL, &m_nNumMat[PICKAXE], &m_pMesh[PICKAXE]);
	D3DXLoadMeshFromX(LPCSTR("./data/model/axe.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[AXE], NULL, &m_nNumMat[AXE], &m_pMesh[AXE]);

	return S_OK;
}

//=============================================================================
// テクスチャ・モデルデータ破棄処理
// Author : 樋宮匠
//=============================================================================
void CTool::Unload(void)
{
	for (int nCount = 0; nCount < MAX_TOOL; nCount++)
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
CTool * CTool::Create(TYPE_TOOL type, D3DXVECTOR3 pos)
{
	CTool *pTool = NULL;
	pTool = new CTool;
	pTool->Init(type);
	pTool->SetPos(pos);
	pTool->SetObjType(OBJ_TYPE_TOOL);

	return pTool;
}