//=============================================
//
//ステンシルマスク処理[stencil_mask.cpp]
//Author Matsuda Towa
//
//=============================================
#include "stencil_mask.h"
#include "manager.h"

//色
const D3DXCOLOR CStencilMask::COLOR = { 1.0f, 0.0f, 0.0f, 0.75f };

//=============================================
// コンストラクタ
//=============================================
CStencilMask::CStencilMask(int nPriority):CMask(nPriority)
{
}

//=============================================
// デストラクタ
//=============================================
CStencilMask::~CStencilMask()
{
}

//=============================================
// 初期化
//=============================================
HRESULT CStencilMask::Init()
{
	CMask::Init();
	//色設定
	SetColor(COLOR);
	return S_OK;
}

//=============================================
// 終了
//=============================================
void CStencilMask::Uninit()
{
	CMask::Uninit();
}

//=============================================
// 更新
//=============================================
void CStencilMask::Update()
{
	CMask::Update();
}

//=============================================
// 描画
//=============================================
void CStencilMask::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	// デバイスのポインタ
	// ステンシルテストを有効にする
	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);
	// 比較参照値を設定する
	pDevice->SetRenderState(D3DRS_STENCILREF, REFARENCE_VALUE);
	// ステンシルマスクを指定する
	pDevice->SetRenderState(D3DRS_STENCILMASK, 255);
	// ステンシル比較関数を指定する
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_LESSEQUAL);
	// ステンシル結果に対しての反映設定
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);	// Zテスト・ステンシルテスト成功
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);		// Zテスト・ステンシルテスト失敗
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);		// Zテスト失敗・ステンシルテスト成功

	CMask::Draw();

	// ステンシルテストを無効にする
	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
}
