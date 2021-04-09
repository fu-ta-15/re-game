//##################################################################################################################################################################//
//
// ポリゴン処理 [polygon.cpp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//

//=====================================================================================================================================================================//
//　インクルードファイル
//=====================================================================================================================================================================//
#include "polygon.h"
#include "manager.h"
#include "renderer.h"

//=====================================================================================================================================================================//
//　static初期化
//=====================================================================================================================================================================//
vector<CPolygon*> CPolygon::m_pPolygon = {};

//=====================================================================================================================================================================//
//　コンストラクタ
//=====================================================================================================================================================================//
CPolygon::CPolygon()
{
	//各メンバ変数のクリア
	m_pVtxBuff = nullptr;
	m_pos = ZeroVector3;
	m_size = ZeroVector3;

	CPolygon *pPolygon = nullptr;

	//for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	//{
	//	if (m_pPolygon[nCnt] == nullptr)
	//	{
	//		m_pPolygon[nCnt] = this;
	//		break;
	//	}
	//}

	pPolygon = this;

	m_pPolygon.push_back(pPolygon);
}

CPolygon::~CPolygon()
{
}

CPolygon * CPolygon::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	// polygonのクラスのポインタ
	CPolygon *pPolygon = nullptr;

	// メモリの確保
	pPolygon = new CPolygon;

	// nullチェック
	if (pPolygon != nullptr)
	{
		// 初期化開始
		pPolygon->m_pos = pos;
		pPolygon->m_size = size;
		pPolygon->Init();
	}
	else return nullptr;

	return pPolygon;
}

HRESULT CPolygon::Init(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, nullptr)))
	{
		return E_FAIL;
	}

	//頂点バッファのロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//各頂点座標
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y + m_size.y + m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y - m_size.y + m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y + m_size.y + m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y - m_size.y + m_size.y, 0.0f);

	//rhwの設定		=	1.0f固定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定・赤・緑・青
	pVtx[0].col = D3DCOLOR_RGBA(225, 225, 225, 225);
	pVtx[1].col = D3DCOLOR_RGBA(225, 225, 225, 225);
	pVtx[2].col = D3DCOLOR_RGBA(225, 225, 225, 225);
	pVtx[3].col = D3DCOLOR_RGBA(225, 225, 225, 225);

	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0);
	pVtx[2].tex = D3DXVECTOR2(0.1f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f, 0);

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}

void CPolygon::Uninit(void)
{
	//頂点バッファの開放
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
}

void CPolygon::Update(void)
{
}

void CPolygon::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, nullptr);

	//ポリゴン描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

void CPolygon::DrawAllList(void)
{
	for (size_t nCnt = 0; nCnt < m_pPolygon.size(); nCnt++)
	{
		if (m_pPolygon.at(nCnt) != nullptr)
		{
			m_pPolygon.at(nCnt)->Draw();
		}
	}
	//for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	//{
	//	if (m_pPolygon[nCnt] != nullptr)
	//	{
	//		m_pPolygon[nCnt]->Draw();
	//	}
	//}
}

void CPolygon::ReleceAllList(void)
{
	for (size_t nCnt = 0; nCnt < m_pPolygon.size(); nCnt++)
	{
		if (m_pPolygon.at(nCnt) != nullptr)
		{
			delete m_pPolygon.at(nCnt);
			m_pPolygon.at(nCnt) = nullptr;

		}
	}
	//for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	//{
	//	if (m_pPolygon[nCnt] != nullptr)
	//	{
	//		delete m_pPolygon[nCnt];
	//		m_pPolygon[nCnt] = nullptr;
	//	}
	//}
}

void CPolygon::SetPos(const D3DXVECTOR3 pos)
{
	m_pos = pos;
}

void CPolygon::SetSize(const D3DXVECTOR3 size)
{
	m_size = size;
}

void CPolygon::SetColor(const D3DXCOLOR color)
{
	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点データをロックし、頂点バッファへのポインタ取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//カラーの設定
	pVtx[0].col = color;
	pVtx[1].col = color;
	pVtx[2].col = color;
	pVtx[3].col = color;

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();
}
