//=============================================
//
//ヒットUI(割れ)[hit_UI_break.cpp]
//Author Matsuda Towa
//
//=============================================
#include "hit_UI_break.h"

namespace
{
	std::string TEX_NAME = "data\\TEXTURE\\break.png";	//ファイルパス
}

//=============================================
//コンストラクタ
//=============================================
My::CHit_UI_Break::CHit_UI_Break(int nPriority) :CHit_UI(nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
My::CHit_UI_Break::~CHit_UI_Break()
{
}

//=============================================
//初期化
//=============================================
HRESULT My::CHit_UI_Break::Init()
{
	//親クラスの初期化
	CHit_UI::Init();

	CTexture* pTexture = GET_TEXTURE;

	BindTexture(pTexture->GetAddress(pTexture->Regist(&TEX_NAME)));

	return S_OK;
}

//=============================================
//終了
//=============================================
void My::CHit_UI_Break::Uninit()
{
	//親クラスの終了
	CHit_UI::Uninit();
}

//=============================================
//更新
//=============================================
void My::CHit_UI_Break::Update()
{
	//親クラスの更新
	CHit_UI::Update();
}

//=============================================
//描画
//=============================================
void My::CHit_UI_Break::Draw()
{
	//親クラスの描画
	CHit_UI::Draw();
}