//=============================================
//
//マウスの軌跡_必殺技[mouse_trail_special.cpp]
//Author Matsuda Towa
//
//=============================================
#include "mouse_trail_special.h"

//=============================================
// コンストラクタ
//=============================================
My::CMouseTrail_Special::CMouseTrail_Special(int nPriority):CMouseTrail(nPriority)
{
}

//=============================================
// デストラクタ
//=============================================
My::CMouseTrail_Special::~CMouseTrail_Special()
{
}

//=============================================
// 初期化
//=============================================
HRESULT My::CMouseTrail_Special::Init()
{
	CMouseTrail::Init();
	return S_OK;
}

//=============================================
// 終了
//=============================================
void My::CMouseTrail_Special::Uninit()
{
	CMouseTrail::Uninit();
}

//=============================================
// 更新
//=============================================
void My::CMouseTrail_Special::Update()
{
	CMouseTrail::Update();
}

//=============================================
// 描画
//=============================================
void My::CMouseTrail_Special::Draw()
{
	CMouseTrail::Draw();
}
