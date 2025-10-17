//=============================================
//
//移動するポイント[move_point.cpp]
//Author Matsuda Towa
//
//=============================================
#include "move_point.h"

//=============================================
// 初期化
//=============================================
HRESULT My::CMovePoint::Init()
{
	//親クラスの初期化
	CBillboard::Init();

	//頂点座標
	SetVtx({0.0f,1.0f,0.0f});
	return S_OK;
}

//=============================================
// 終了
//=============================================
void My::CMovePoint::Uninit()
{
	//親クラスの終了
	CBillboard::Uninit();
}

//=============================================
// 更新
//=============================================
void My::CMovePoint::Update()
{
	//親クラスの更新
	CBillboard::Update();

	//頂点座標
	SetVtx({ 0.0f,1.0f,0.0f });
}

//=============================================
// 描画
//=============================================
void My::CMovePoint::Draw()
{
	//親クラスの描画
	CBillboard::Draw();
}

//=============================================
// 生成
//=============================================
My::CMovePoint* My::CMovePoint::Create(D3DXVECTOR3 pos, CMovePoint* point)
{
	CMovePoint* move_point = point;

	if (move_point == nullptr) { return nullptr; }

	move_point->SetPos(pos);

	move_point->SetType(OBJECT_TYPE_MOVE_POINT);

	move_point->Init();

	return move_point;
}
