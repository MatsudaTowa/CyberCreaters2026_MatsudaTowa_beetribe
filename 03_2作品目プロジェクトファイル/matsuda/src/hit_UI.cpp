//=============================================
//
//アタックポイント[attack_point.cpp]
//Author Matsuda Towa
//
//=============================================
#include "hit_UI.h"
#include "hit_UI_break.h"
#include "hit_UI_stun.h"

namespace
{
	D3DXVECTOR2 POLY_SIZE = { 30.0f,30.0f };					//ポリゴンサイズ
}

//=============================================
// コンストラクタ
//=============================================
My::CHit_UI::CHit_UI(int nPriority):CObject2D(nPriority)
{
}

//=============================================
// デストラクタ
//=============================================
My::CHit_UI::~CHit_UI()
{
}

//=============================================
// 初期化
//=============================================
HRESULT My::CHit_UI::Init()
{
	//親クラスの初期化を呼ぶ
	CObject2D::Init();

	//サイズ設定
	SetSize(POLY_SIZE);

	//色設定
	SetColor(COLOR_WHITE);

	//頂点設定
	SetVtx();

	return S_OK;
}

//=============================================
// 終了
//=============================================
void My::CHit_UI::Uninit()
{
	//親クラスの終了を呼ぶ
	CObject2D::Uninit();
}

//=============================================
// 更新
//=============================================
void My::CHit_UI::Update()
{
	//親クラスの更新を呼ぶ
	CObject2D::Update();

	//頂点設定
	SetVtx();
}

//=============================================
// 描画
//=============================================
void My::CHit_UI::Draw()
{
	//親クラスの描画を呼ぶ
	CObject2D::Draw();
}

//=============================================
// 生成
//=============================================
My::CHit_UI* My::CHit_UI::Create(D3DXVECTOR3 pos, int type)
{
	CHit_UI* pHitUI = nullptr;

	switch (type)
	{
	case CHit_UI::BREAK:
		pHitUI = new CHit_UI_Break;
		break;
	case CHit_UI::STUN:
		pHitUI = new CHit_UI_Stun;
		break;
	default:
		assert(false && "存在しないタイプです");
		break;
	}
	if (pHitUI == nullptr) { return nullptr; }

	pHitUI->SetPos({pos.x,pos.y,pos.z});

	pHitUI->SetType(OBJECT_TYPE_ATTACK_POINT);

	pHitUI->Init();

	return pHitUI;
}
