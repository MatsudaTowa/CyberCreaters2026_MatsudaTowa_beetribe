//=============================================
//
//必殺技時に書く紙[paper.cpp]
//Author Matsuda Towa
//
//=============================================
#include "paper.h"
#include "game_manager.h"

namespace
{
	D3DXVECTOR2 POLY_SIZE = { SCREEN_WIDTH*0.45f,SCREEN_HEIGHT*0.45f };						//サイズ
	const std::string TEX_NAME = "data\\TEXTURE\\paper.png";		//テクスチャ
}
//=============================================
// コンストラクタ
//=============================================
My::CPaper::CPaper(int nPriority):CObject2D(nPriority)
{
}

//=============================================
// デストラクタ
//=============================================
My::CPaper::~CPaper()
{
}

//=============================================
// 初期化
//=============================================
HRESULT My::CPaper::Init()
{
	CGameManager::GetInstance()->SetPaper(this);
	CObject2D::Init();
	CTexture* pTexture = GET_TEXTURE;

	BindTexture(pTexture->GetAddress(pTexture->Regist(&TEX_NAME)));

	SetSize(POLY_SIZE);
	SetColor(COLOR_WHITE);
	SetVtx();
	return S_OK;
}

//=============================================
// 終了
//=============================================
void My::CPaper::Uninit()
{
	CObject2D::Uninit();
}

//=============================================
// 更新
//=============================================
void My::CPaper::Update()
{
	CObject2D::Update();
	SetVtx();
}

//=============================================
// 描画
//=============================================
void My::CPaper::Draw()
{
	CObject2D::Draw();
}

//=============================================
// 描画
//=============================================
My::CPaper* My::CPaper::Create(D3DXVECTOR3 pos)
{
	CPaper* pPaper = new CPaper;
	if (pPaper == nullptr)
	{
		return nullptr;
	}

	pPaper->SetPos(pos);
	pPaper->Init();
	return pPaper;
}
