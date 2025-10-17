//=============================================
//
//プレイヤーが移動するポイント[player_move_point.cpp]
//Author Matsuda Towa
//
//=============================================
#include "player_move_point.h"

namespace
{
	const D3DXVECTOR3 POLY_SYZE = { 5.0f,5.0f,0.0f };				//ポリゴンサイズ
}

//=============================================
// 初期化
//=============================================
HRESULT My::CPlayerMovePoint::Init()
{

	SetSize(POLY_SYZE);

	SetColor(COLOR_BLUE);

	//親クラスの初期化
	CMovePoint::Init();

	return S_OK;
}

//=============================================
// 終了
//=============================================
void My::CPlayerMovePoint::Uninit()
{	
	//親クラスの終了
	CMovePoint::Uninit();
}

//=============================================
// 更新
//=============================================
void My::CPlayerMovePoint::Update()
{
	//親クラスの更新
	CMovePoint::Update();
}

//=============================================
// 描画
//=============================================
void My::CPlayerMovePoint::Draw()
{
	//親クラスの描画
	CMovePoint::Draw();
}