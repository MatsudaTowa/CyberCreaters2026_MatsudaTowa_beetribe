//=============================================
//
//プレイヤー[result_player.cpp]
//Author Matsuda Towa
//
//=============================================
#include "result_player.h"

namespace
{
	const float BELT_TARGET_POS_Y = 80.0f;
	const float BELT_TARGET_POS_Z = 30.0f;
}

//=============================================
// コンストラクタ
//=============================================
My::CResultPlayer::CResultPlayer(int nPriority):CPlayer(nPriority)
{
}

//=============================================
// デストラクタ
//=============================================
My::CResultPlayer::~CResultPlayer()
{
}

//=============================================
// 初期化
//=============================================
HRESULT My::CResultPlayer::Init()
{
	//親クラスの初期化実行
	CPlayer::Init();
	return S_OK;
}

//=============================================
// 終了
//=============================================
void My::CResultPlayer::Uninit()
{
	//親クラスの終了処理
	CPlayer::Uninit();
}

//=============================================
// 更新
//=============================================
void My::CResultPlayer::Update()
{
	Motion();

	CBelt* pBelt = GetBelt();
	D3DXVECTOR3 pos = pBelt->GetPos();
	if (pos.y < BELT_TARGET_POS_Y)
	{
		pos.y += 1.5f;

		D3DXVECTOR3 scale = pBelt->GetScale();
		scale += {0.1f, 0.1f, 0.1f};
		pBelt->SetScale(scale);
	}
	if (pos.z < BELT_TARGET_POS_Z)
	{
		pos.z += 0.5f;
	}

	pBelt->SetPos(pos);
}

//=============================================
// 描画
//=============================================
void My::CResultPlayer::Draw()
{
	//親クラスの描画
	CPlayer::Draw();
}
