//=============================================
//
//マウスの軌跡[mouse_trail.cpp]
//Author Matsuda Towa
//
//=============================================
#include "mouse_trail.h"
#include "game_manager.h"
namespace 
{
	const std::string TEX_NAME = "data\\TEXTURE\\fude.png";	//ファイルパス
}

const D3DXVECTOR3 My::CMouseTrail::POLY_SIZE = { 12.5f,12.5f,0.0f };		//ポリゴンサイズ
const D3DXCOLOR My::CMouseTrail::COLOR = { 0.0f,0.0f,0.0f,0.5f };		//カラー

//=============================================
//コンストラクタ
//============================================
My::CMouseTrail::CMouseTrail(int nPriority):CBillboard(nPriority)
{
}

//=============================================
//デストラクタ
//============================================
My::CMouseTrail::~CMouseTrail()
{
}

//=============================================
//初期化
//============================================
HRESULT My::CMouseTrail::Init()
{
	//親クラスの初期化
	CBillboard::Init();

	SetSize(POLY_SIZE);

	SetColor(COLOR);

	//頂点座標
	SetVtx(D3DXVECTOR3(0.0f, 1.0f, 0.0f));

	return S_OK;
}

//=============================================
//終了
//============================================
void My::CMouseTrail::Uninit()
{
	//親クラスの終了
	CBillboard::Uninit();
}

//=============================================
//更新
//============================================
void My::CMouseTrail::Update()
{
	//親クラスの更新
	CBillboard::Update();

	//頂点座標
	SetVtx(D3DXVECTOR3(0.0f, 1.0f, 0.0f));
}

//=============================================
//描画
//============================================
void My::CMouseTrail::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;

	//zの比較方法変更
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	//zバッファに書き込まない
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//ライトを有効に戻す
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//親クラスの描画
	CBillboard::Draw();

	//zの比較方法変更
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	//zバッファに書き込まない
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//ライトを有効に戻す
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//=============================================
//生成
//============================================
My::CMouseTrail* My::CMouseTrail::Create(D3DXVECTOR3 pos, CMouseTrail* trail)
{
	CTexture* pTexture = GET_TEXTURE;

	CMouseTrail* pTrail = trail;
	
	if (pTrail == nullptr) { return nullptr; }

	pTrail->SetPos(pos);

	pTrail->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEX_NAME)));

	pTrail->Init();

	return pTrail;
}
