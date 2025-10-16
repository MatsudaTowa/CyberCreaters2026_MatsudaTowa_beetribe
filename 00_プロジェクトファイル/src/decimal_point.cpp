//=============================================
//
//小数点[decimal_point.cpp]
//Author Matsuda Towa
//
//=============================================
#include "decimal_point.h"

//=============================================
// コンストラクタ
//=============================================
CDecimalPoint::CDecimalPoint(int nPriority):CObject2D(nPriority)
{
}

//=============================================
// デストラクタ
//=============================================
CDecimalPoint::~CDecimalPoint()
{
}

//=============================================
// 初期化
//=============================================
HRESULT CDecimalPoint::Init()
{
	CObject2D::Init();
	SetVtx(1.0f);
	return S_OK;
}

//=============================================
// 終了
//=============================================
void CDecimalPoint::Uninit()
{
	CObject2D::Uninit();
}

//=============================================
// 更新
//=============================================
void CDecimalPoint::Update()
{
	CObject2D::Update();
	SetVtx(1.0f);
}

//=============================================
// 描画
//=============================================
void CDecimalPoint::Draw()
{
	CObject2D::Draw();
}

//=============================================
// 生成
//=============================================
CDecimalPoint* CDecimalPoint::Create(D3DXVECTOR3 pos,D3DXVECTOR2 size,D3DXCOLOR col)
{
	CDecimalPoint* point = new CDecimalPoint;

	if (point == nullptr) { return nullptr; }
	point->SetPos(pos);
	point->SetSize(size);
	point->SetColor(col);
	point->Init();
	return point;
}
