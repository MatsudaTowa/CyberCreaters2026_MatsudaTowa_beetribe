//=============================================
//
//マウスの軌跡を設置するポイント[mouse_trail_point.cpp]
//Author Matsuda Towa
//
//=============================================
#include "mouse_trail_point.h"
#include "mouse_trail_normal.h"
#include "field.h"
#include "board_holder.h"
namespace
{
	const D3DXVECTOR3 POLY_SYZE = { 5.0f,5.0f,0.0f };				//ポリゴンサイズ
	const int TRAIL_CREATE_NUM = 10;									//一回で何回生成するか
	const D3DXVECTOR3 TRAIL_CREATE_MIN_POS = { -5.0f,0.0f,-5.0f };	//生成する最小位置
	const D3DXVECTOR3 TRAIL_CREATE_MAX_POS = { 5.0f,0.0f,5.0f };	//生成する最大位置
}

//=============================================
//初期化
//============================================
HRESULT My::CMouseTrailPoint::Init()
{
	//親クラスの初期化
	CBillboard::Init();

	SetSize(POLY_SYZE);

	SetColor(COLOR_WHITE);

	//頂点座標
	SetVtx(D3DXVECTOR3(0.0f, 1.0f, 0.0f));

	return S_OK;
}

//=============================================
//終了
//============================================
void My::CMouseTrailPoint::Uninit()
{
	//親クラスの終了
	CBillboard::Uninit();
}

//=============================================
//更新
//============================================
void My::CMouseTrailPoint::Update()
{
	//親クラスの更新
	CBillboard::Update();

	//頂点座標
	SetVtx(D3DXVECTOR3(0.0f, 1.0f, 0.0f));
}

//=============================================
//描画
//============================================
void My::CMouseTrailPoint::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;

	//ライトを有効に戻す
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//親クラスの描画
	CBillboard::Draw();

	//ライトを有効に戻す
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//=============================================
//生成
//============================================
My::CMouseTrailPoint* My::CMouseTrailPoint::Create(D3DXVECTOR3 pos)
{
	CMouseTrailPoint* pTrailPoint = new CMouseTrailPoint;

	if (pTrailPoint == nullptr) { return nullptr; }

	pTrailPoint->SetPos(pos);

	pTrailPoint->SetType(OBJECT_MOUSE_DEBUG);

	pTrailPoint->Init();

	return pTrailPoint;
}

//=============================================
//軌跡の生成
//=============================================
void My::CMouseTrailPoint::CreateTrail()
{
	D3DXVECTOR3 pos = GetPos();

	for (int i = 0; i < TRAIL_CREATE_NUM; ++i)
	{
		float x = 0.0f;
		float z = 0.0f;

		x = Rundom(TRAIL_CREATE_MIN_POS.x, TRAIL_CREATE_MAX_POS.x);
		z = Rundom(TRAIL_CREATE_MIN_POS.z, TRAIL_CREATE_MAX_POS.z);

		CMouseTrail::Create({ pos.x + x,pos.y + 0.5f,pos.z + z },new CMouseTrail_Normal);
	}
}
