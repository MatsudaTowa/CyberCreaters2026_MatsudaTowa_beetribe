//=============================================
//
//マスク処理[mask.cpp]
//Author Matsuda Towa
//
//=============================================
#include "mask.h"
#include "manager.h"

//=============================================
// コンストラクタ
//=============================================
CMask::CMask(int nPriority):CObject2D(nPriority)
{
}

//=============================================
// デストラクタ
//=============================================
CMask::~CMask()
{
}

//=============================================
// 初期化
//=============================================
HRESULT CMask::Init()
{
	CObject2D::Init();

	SetPos({ SCREEN_WIDTH * HALF,SCREEN_HEIGHT * HALF,FLOAT_ZERO });

	//サイズ取得
	D3DXVECTOR2 size = GetSize();

	size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);

	//サイズを代入
	SetSize(size);

	//カラー取得
	D3DXCOLOR col = GetColor();

	col = COLOR_NONE;

	//カラーを代入
	SetColor(col);

	SetVtx(1.0f);
	return S_OK;
}

//=============================================
// 終了
//=============================================
void CMask::Uninit()
{
	CObject2D::Uninit();
}

//=============================================
// 更新
//=============================================
void CMask::Update()
{
	CObject2D::Update();
	SetVtx(1.0f);
}

//=============================================
// 描画
//=============================================
void CMask::Draw()
{
	CObject2D::Draw();
}

//=============================================
// 生成
//=============================================
CMask* CMask::Create(CMask* mask)
{
	CMask* pMask = mask;

	if (pMask == nullptr) { return nullptr; }

	pMask->Init();

	return pMask;
}
