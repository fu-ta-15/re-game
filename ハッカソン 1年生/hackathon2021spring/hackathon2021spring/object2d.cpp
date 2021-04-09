//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	scene2d.cpp
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "object2d.h"

#include "manager.h"
#include "renderer.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//コンストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CObject2D::CObject2D(int nPriority)
  : CObject(nPriority)
{
    m_pTexture = NULL;    // テクスチャへのポインタ
    m_pVtxBuff = NULL;    // 頂点バッファへのポインタ

    m_pos  = D3DXVECTOR3(0, 0, 0);    // ポリゴンの位置
    m_move = D3DXVECTOR3(0, 0, 0);
    m_fRot = 0.0f;
    m_col  = D3DCOLOR_RGBA(255, 255, 255, 255);
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//デストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CObject2D::~CObject2D()
{
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//初期化処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
HRESULT CObject2D::Init(void)
{
    VERTEX_2D* pVtx;
    LPDIRECT3DDEVICE9 pDevice = NULL;
    pDevice                   = CManager::GetRenderer()->GetDevice();

    //頂点バッファの生成
    pDevice->CreateVertexBuffer(
      sizeof(VERTEX_2D) * NUM_VERTEX,    //バッファサイズ
      D3DUSAGE_WRITEONLY,                //固定
      FVF_VERTEX_2D,                     //頂点フォーマット
      D3DPOOL_MANAGED,                   //固定
      &m_pVtxBuff,                       //変数名によって変化
      NULL);

    m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

    //頂点情報を設定
    pVtx[0].pos = m_pos + D3DXVECTOR3((float)-m_size.x / 2, (float)-m_size.y / 2, 0.0f);
    pVtx[1].pos = m_pos + D3DXVECTOR3((float)m_size.x / 2, (float)-m_size.y / 2, 0.0f);
    pVtx[2].pos = m_pos + D3DXVECTOR3((float)-m_size.x / 2, (float)m_size.y / 2, 0.0f);
    pVtx[3].pos = m_pos + D3DXVECTOR3((float)m_size.x / 2, (float)m_size.y / 2, 0.0f);

    //テクスチャ座標の設定
    pVtx[0].tex = D3DXVECTOR2(0, 0);
    pVtx[1].tex = D3DXVECTOR2(1, 0);
    pVtx[2].tex = D3DXVECTOR2(0, 1);
    pVtx[3].tex = D3DXVECTOR2(1, 1);

    //rhwの設定
    pVtx[0].rhw = 1.0f;
    pVtx[1].rhw = 1.0f;
    pVtx[2].rhw = 1.0f;
    pVtx[3].rhw = 1.0f;

    //頂点カラーの設定(0～255)
    pVtx[0].col = m_col;    //aは透明度
    pVtx[1].col = m_col;    //aは透明度
    pVtx[2].col = m_col;    //aは透明度
    pVtx[3].col = m_col;    //aは透明度

    m_pVtxBuff->Unlock();
    return S_OK;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//終了処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CObject2D::Uninit(void)
{
    // 頂点バッファの破棄
    if(m_pVtxBuff != NULL)
    {
        m_pVtxBuff->Release();
        m_pVtxBuff = NULL;
    }
    Release();
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//更新処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CObject2D::Update(void)
{
    D3DXMATRIX posMatrix;       // 頂点行列
    D3DXMATRIX rotateMatrix;    // 回転行列
    VERTEX_2D* pVtx;

    //行列の初期化（単位行列生成）
    D3DXMatrixIdentity(&posMatrix);
    D3DXMatrixIdentity(&rotateMatrix);

    m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

    //頂点座標更新
    pVtx[0].pos = D3DXVECTOR3((float)-m_size.x / 2, (float)-m_size.y / 2, 0.0f);
    pVtx[1].pos = D3DXVECTOR3((float)m_size.x / 2, (float)-m_size.y / 2, 0.0f);
    pVtx[2].pos = D3DXVECTOR3((float)-m_size.x / 2, (float)m_size.y / 2, 0.0f);
    pVtx[3].pos = D3DXVECTOR3((float)m_size.x / 2, (float)m_size.y / 2, 0.0f);

    //頂点カラー更新
    pVtx[0].col = m_col;
    pVtx[1].col = m_col;
    pVtx[2].col = m_col;
    pVtx[3].col = m_col;

    m_pVtxBuff->Unlock();

    //回転行列生成
    D3DXMatrixRotationZ(&rotateMatrix, D3DXToRadian(m_fRot));

    for(int nCount = 0; nCount < NUM_VERTEX; nCount++)
    {
        //頂点座標を行列に変換
        D3DXMatrixTranslation(&posMatrix, pVtx[nCount].pos.x, pVtx[nCount].pos.y, pVtx[nCount].pos.z);
        //回転行列を行列にかける
        posMatrix *= rotateMatrix;
        //回転後の座標を頂点座標に入れる
        pVtx[nCount].pos.x = posMatrix._41;
        pVtx[nCount].pos.y = posMatrix._42;
        pVtx[nCount].pos.z = posMatrix._43;
        //m_pos分移動させる
        pVtx[nCount].pos += m_pos;
    }
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//描画処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CObject2D::Draw(void)
{
    LPDIRECT3DDEVICE9 pDevice = NULL;
    pDevice                   = CManager::GetRenderer()->GetDevice();
    //頂点バッファをデータストリームに設定
    pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

    //頂点フォーマットの設定
    pDevice->SetFVF(FVF_VERTEX_2D);

    //テクスチャの設定
    pDevice->SetTexture(0, m_pTexture);

    //ポリゴンの描画
    pDevice->DrawPrimitive(
      D3DPT_TRIANGLESTRIP,    //プリティブの種類
      0,
      NUM_POLYGON    //プリティブの数
    );
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//セッター関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CObject2D::SetPos(D3DXVECTOR3 pos)
{
    m_pos = pos;
}

void CObject2D::SetMove(D3DXVECTOR3 move)
{
    m_move = move;
}

void CObject2D::SetSize(D3DXVECTOR3 size)
{
    m_size = size;
}

void CObject2D::SetRot(float rot)
{
    m_fRot = rot;
}

void CObject2D::SetTexPos(D3DXVECTOR2* pTexPos)
{
    VERTEX_2D* pVtx;
    m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
    for(int nCount = 0; nCount < NUM_VERTEX; nCount++)
    {
        pVtx[nCount].tex = *(pTexPos + nCount);
    }
    m_pVtxBuff->Unlock();
}

void CObject2D::SetCol(D3DCOLOR col)
{
    m_col = col;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//ゲッター関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
D3DXVECTOR3 CObject2D::GetMove(void)
{
    return m_move;
}

D3DXVECTOR3 CObject2D::GetPos(void)
{
    return m_pos;
}

D3DXVECTOR3 CObject2D::GetSize(void)
{
    return m_size;
}
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//生成処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CObject2D* CObject2D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nPriority)
{
    CObject2D* pScene2d = NULL;
    pScene2d            = new CObject2D(nPriority);
    pScene2d->m_pos     = pos;
    pScene2d->m_size    = size;
    pScene2d->Init();

    return pScene2d;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//テクスチャの割当
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CObject2D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
    m_pTexture = pTexture;
}
