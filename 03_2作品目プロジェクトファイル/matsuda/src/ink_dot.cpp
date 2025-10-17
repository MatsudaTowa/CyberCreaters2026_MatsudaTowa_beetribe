//=============================================
//
//墨の点[ink_dot.cpp]
//Author Matsuda Towa
//
//=============================================
#include "ink_dot.h"

namespace
{
	const float MAX_SIZE = 1.0f;
	const float MIN_SIZE = 3.0f;
	const std::string TEX_NAME =
	{
		"data\\TEXTURE\\ink_dot.png",
	};
}
//=============================================
// コンストラクタ
//=============================================
My::CInkDot::CInkDot(int nPriority):CObject3D(nPriority)
{
}

//=============================================
// デストラクタ
//=============================================
My::CInkDot::~CInkDot()
{
}

//=============================================
// 初期化
//=============================================
HRESULT My::CInkDot::Init()
{
	SetColor(COLOR_WHITE);
	CObject3D::Init();

	//テクスチャ設定
	CTexture* pTexture = GET_TEXTURE;
	BindTexture(pTexture->GetAddress(pTexture->Regist(&TEX_NAME)));

	float size = FLOAT_ZERO;

	size = Rundom(MIN_SIZE, MAX_SIZE);

	SetSize({ size,0.0f,size });

	//頂点設定
	SetVtx(D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	return S_OK;
}

//=============================================
// 終了
//=============================================
void My::CInkDot::Uninit()
{
	CObject3D::Uninit();
}

//=============================================
// 更新
//=============================================
void My::CInkDot::Update()
{
	CObject3D::Update();

	//頂点設定
	SetVtx(D3DXVECTOR3(0.0f, 1.0f, 0.0f));
}

//=============================================
// 描画
//=============================================
void My::CInkDot::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;
	//zバッファに書き込まない
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	CObject3D::Draw();
	//zバッファに書き込む
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

//=============================================
// 生成
//=============================================
My::CInkDot* My::CInkDot::Create(D3DXVECTOR3 pos)
{
	CInkDot* pInkDot = new CInkDot;
	if (pInkDot == nullptr)
	{
		return nullptr;
	}
	pInkDot->SetPos(pos);
	pInkDot->Init();

	return pInkDot;
}
