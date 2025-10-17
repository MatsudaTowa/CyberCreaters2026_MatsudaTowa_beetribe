//=============================================
//
//水しぶきエフェクト[flash_effect.cpp]
//Author Matsuda Towa
//
//=============================================
#include "splash_effect.h"

namespace
{
	const D3DXVECTOR3 POLY_SIZE = { 20.0f,20.0f,0.0f };

	const int LIFE_FRAME = 30;

	const float MAX_SPEED = 1.0f;
	const float MIN_SPEED = 0.2f;

	std::string TEX_NAME = "data\\TEXTURE\\splash.png"; //ファイルパス
}

//=============================================
// コンストラクタ
//=============================================
My::CSplashEffect::CSplashEffect(int nPriority):CBillboard(nPriority),
m_move(VEC3_RESET_ZERO),
m_pCnt(nullptr)
{
}

//=============================================
// デストラクタ
//=============================================
My::CSplashEffect::~CSplashEffect()
{
}

//=============================================
// 初期化
//=============================================
HRESULT My::CSplashEffect::Init()
{
	if (m_pCnt == nullptr)
	{
		m_pCnt = new CCount;
		m_pCnt->SetFrame(LIFE_FRAME);
	}

	CBillboard::Init();
	//テクスチャ設定
	CTexture* pTexture = GET_TEXTURE;
	BindTexture(pTexture->GetAddress(pTexture->Regist(&TEX_NAME)));

	//放射状にランダム
	float fVertex = CICRLE_RAND;

	float x = FLOAT_ZERO;
	float z = FLOAT_ZERO;
	x = Rundom(MIN_SPEED, MAX_SPEED);
	z = Rundom(MIN_SPEED, MAX_SPEED);

	D3DXVECTOR3 rot = GetRot();
	rot.y = fVertex;
	SetRot(rot);

	//移動量代入
	m_move.x = sinf(fVertex) * x;
	m_move.z = cosf(fVertex) * z;

	SetSize(POLY_SIZE);
	SetColor(COLOR_WHITE);

	SetVtx({ 0.0f,1.0f,0.0f });
	return S_OK;
}

//=============================================
// 終了
//=============================================
void My::CSplashEffect::Uninit()
{
	CBillboard::Uninit();
}

//=============================================
// 更新
//=============================================
void My::CSplashEffect::Update()
{
	CBillboard::Update();

	D3DXVECTOR3 pos = GetPos();

	pos += m_move;

	SetPos(pos);

	float sub_size = POLY_SIZE.x / LIFE_FRAME;

	D3DXVECTOR3 size = GetSize();

	size.x -= sub_size;
	size.y -= sub_size;

	SetSize(size);

	SetVtx({ 0.0f,1.0f,0.0f });

	if (m_pCnt->CountUp())
	{
		Uninit();
	}
}

//=============================================
// 描画
//=============================================
void My::CSplashEffect::Draw()
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
	CBillboard::Draw();

	//通常の合成に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);

	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//zバッファに書き込む
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	//ライトを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//=============================================
// 生成
//=============================================
My::CSplashEffect* My::CSplashEffect::Create(D3DXVECTOR3 pos)
{
	CSplashEffect* pEffect = new CSplashEffect;

	//中身がないなら代入の前にreturn
	if (pEffect == nullptr) { return nullptr; }

	pEffect->SetPos(pos);	//位置設定

	pEffect->Init();		//初期化

	return pEffect;
}
