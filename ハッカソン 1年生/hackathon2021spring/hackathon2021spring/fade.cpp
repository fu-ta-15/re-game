//=============================================================================
//
// フェード処理 [fade.cpp]
// Author : 吉田悠人
//
//=============================================================================
#include "fade.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CFade::CFade()
{
	m_pVtxBuff = NULL;
	m_mode = CManager::MODE_TITLE;
	m_color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	m_fade = FADE_NONE;
}

//=============================================================================
// デストラクタ
//=============================================================================
CFade::~CFade()
{
}


//=============================================================================
// 作成処理
//=============================================================================
CFade * CFade::Create(void)
{
	CFade *pFade;
	//インスタンス生成
	pFade = new CFade;
	//初期化処理
	if (pFade != NULL)
	{
		pFade->Init();
	}

	return pFade;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CFade::Init(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();
	//頂点バッファ生成
	pD3DDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX,
		D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	//頂点情報へのポインタ
	VERTEX_2D*pVtx;

	m_color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);//黒い画面（不透明）

												//頂点データの範囲をロックし、頂点バッファのポインタを習得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);//この書式は変えない

											 //頂点座標設定（右回りで設定する）
	pVtx[0].pos = D3DXVECTOR3(00.0f, 00.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 00.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(00.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//rhwの設定（値は1.0で固定）
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定（0～255の数値で設定）
	pVtx[0].col = m_color;
	pVtx[1].col = m_color;
	pVtx[2].col = m_color;
	pVtx[3].col = m_color;

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	//頂点データをアンロック
	m_pVtxBuff->Unlock();

	//初期化
	m_fade = FADE_OUT;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CFade::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void CFade::Update(void)
{
	//頂点情報へのポインター
	VERTEX_2D *pVtx;

	//フェード処理中
	if (m_fade != FADE_NONE)
	{
		//フェードイン処理
		if (m_fade == FADE_IN)
		{
			m_color.a -= FADE_RATE;//α値を減算して後ろの画面を浮き上がらせる

			if (m_color.a <= 0.0f)
			{
				m_color.a = 0.0f;
				//フェード処理終了
				m_fade = FADE_NONE;
			}
		}
		//フェードアウト処理
		else if (m_fade == FADE_OUT)
		{
			m_color.a += FADE_RATE;//α値を加算して後ろの画面を消していく

			if (m_color.a >= 1.0f)
			{
				m_color.a = 1.0f;
				//フェードイン処理に切り替え
				m_fade = FADE_IN;

				//モードを設定
				CManager::SetMode(m_mode);
			}
		}
	}
	//頂点データの範囲をロックし、頂点バッファのポインタを習得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].col = m_color;
	pVtx[1].col = m_color;
	pVtx[2].col = m_color;
	pVtx[3].col = m_color;

	//頂点データをアンロック
	m_pVtxBuff->Unlock();
}

//=============================================================================
// 描画処理
//=============================================================================
void CFade::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();

	//頂点バッファをデバイスのデータストリームにバインド
	pD3DDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pD3DDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pD3DDevice->SetTexture(0, NULL);

	//ポリゴン描画
	pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

//=============================================================================
// フェードの設定
//=============================================================================
void CFade::SetFade(CManager::MODE mode)
{
	m_fade = FADE_OUT;
	m_mode = mode;
}


