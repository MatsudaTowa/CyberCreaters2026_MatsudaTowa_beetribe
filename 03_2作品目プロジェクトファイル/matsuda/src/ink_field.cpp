//=============================================
//
//墨の飛び散り[ink_field.cpp]
//Author Matsuda Towa
//
//=============================================
#include "ink_field.h"
#include "ink_dot.h"

namespace
{
	const int NUM_TEX = 3;
	const int NUM_DOT = 20;
	const float DOT_COLECTION = 1.25f;
	const float MAX_SIZE = 30.0f;
	const float MIN_SIZE = 15.0f;
	const std::string TEX_NAME[NUM_TEX] =
	{
		"data\\TEXTURE\\ink_field_000.png",
		"data\\TEXTURE\\ink_field_001.png",
		"data\\TEXTURE\\ink_field_002.png"
	};
}

//=============================================
// コンストラクタ
//=============================================
My::CInkField::CInkField(int nPriority):CObject3D(nPriority)
{
}

//=============================================
// デストラクタ
//=============================================
My::CInkField::~CInkField()
{
}

//=============================================
// 初期化
//=============================================
HRESULT My::CInkField::Init()
{
	SetColor({COLOR_WHITE.r,COLOR_WHITE.g,COLOR_WHITE.b,0.0f });
	CObject3D::Init();

	int tex_type = Rundom(0, NUM_TEX);
	//テクスチャ設定
	CTexture* pTexture = GET_TEXTURE;
	BindTexture(pTexture->GetAddress(pTexture->Regist(&TEX_NAME[tex_type])));

	float size = FLOAT_ZERO;

	size = Rundom(MIN_SIZE, MAX_SIZE);

	SetSize({ size,0.0f,size });

	//サイズより少しでかめに調整
	float dot_correction = size * DOT_COLECTION;

	for (int i = INT_ZERO; i < NUM_DOT; ++i)
	{
		//放射状にランダム
		float fVertex = CICRLE_RAND;
		D3DXVECTOR3 create_pos = { GetPos().x + dot_correction * sinf(fVertex),1.0f,GetPos().z + dot_correction * cosf(fVertex) };

		CInkDot::Create(create_pos);
	}

	//頂点設定
	SetVtx(D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	return S_OK;
}

//=============================================
// 終了
//=============================================
void My::CInkField::Uninit()
{
	CObject3D::Uninit();
}

//=============================================
// 更新
//=============================================
void My::CInkField::Update()
{
	CObject3D::Update();

	D3DXCOLOR col = GetColor();
	if (col.a < 1.0f)
	{
		col.a += 0.1f;
	}
	SetColor(col);

	//頂点設定
	SetVtx(D3DXVECTOR3(0.0f, 1.0f, 0.0f));
}

//=============================================
// 描画
//=============================================
void My::CInkField::Draw()
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
My::CInkField* My::CInkField::Create(D3DXVECTOR3 pos)
{
	CInkField* pInkField = new CInkField;
	if (pInkField == nullptr)
	{
		return nullptr;
	}
	pInkField->SetPos(pos);
	pInkField->Init();

	return pInkField;
}
