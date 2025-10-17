//=============================================
//
//光るエフェクト[flash_effect.cpp]
//Author Matsuda Towa
//
//=============================================
#include "flash_effect.h"

namespace
{
	const D3DXVECTOR3 POLY_SIZE = { 10.0f,10.0f,0.0f };
	const int ANIM_FRAME = 3;
	const int SPLIT_X = 8;
	const int SPLIT_Y = 1;
	std::string TEX_NAME = "data\\TEXTURE\\flash_anim.png";	//ファイルパス
}

//=============================================
// コンストラクタ
//=============================================
My::CFlashEffect::CFlashEffect(int nPriority):CBillboard_Anim(nPriority)
{
}

//=============================================
// デストラクタ
//=============================================
My::CFlashEffect::~CFlashEffect()
{
}

//=============================================
// 初期化
//=============================================
HRESULT My::CFlashEffect::Init()
{
	CBillboard_Anim::Init();

	//テクスチャ設定
	CTexture* pTexture = GET_TEXTURE;
	BindTexture(pTexture->GetAddress(pTexture->Regist(&TEX_NAME)));

	SetSize(POLY_SIZE);
	SetColor(COLOR_WHITE);

	//テクスチャ移動量取得
	D3DXVECTOR2 tex_move = GetTexMove();
	tex_move.x = 1.0f / (float)SPLIT_X;
	tex_move.y = 1.0f / (float)SPLIT_Y;
	//テクスチャ移動量代入
	SetTexMove(tex_move);

	//テクスチャ座標取得
	D3DXVECTOR2 tex_pos = GetTexPos();
	tex_pos.x = 0.0f;
	tex_pos.y = 0.0f;
	//テクスチャ座標代入
	SetTexPos(tex_pos);
	SetAnimFrame(ANIM_FRAME);

	SetVtx({ 0.0f,1.0f,0.0f });
	AnimationTex(tex_pos, tex_move);
	return S_OK;
}

//=============================================
// 終了
//=============================================
void My::CFlashEffect::Uninit()
{
	CBillboard_Anim::Uninit();
}

//=============================================
// 更新
//=============================================
void My::CFlashEffect::Update()
{
	CBillboard_Anim::Update();
	//テクスチャ情報取得
	D3DXVECTOR2 tex_pos = GetTexPos();
	D3DXVECTOR2 tex_move = GetTexMove();
	//アニメーション後のテクスチャ座標取得
	tex_pos = GetTexPos();
	//アニメーションを繰り返す
	if (tex_pos.x >= FLOAT_ONE)
	{
		Uninit();
		return;
	}

	SetVtx({ 0.0f,1.0f,0.0f });

	//頂点座標
	AnimationTex(tex_pos, tex_move);
}

//=============================================
// 描画
//=============================================
void My::CFlashEffect::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;
	//ライトを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	//zバッファに書き込まない
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//減算合成処理
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);

	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	CBillboard_Anim::Draw();

	//通常の合成に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);

	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//zバッファに書き込まない
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	//ライトを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//=============================================
// 生成
//=============================================
My::CFlashEffect* My::CFlashEffect::Create(D3DXVECTOR3 pos)
{
	CFlashEffect* pEffect = new CFlashEffect;

	//中身がないなら代入の前にreturn
	if (pEffect == nullptr) { return nullptr; }

	pEffect->SetPos(pos);	//位置設定

	pEffect->Init();		//初期化

	return pEffect;
}
