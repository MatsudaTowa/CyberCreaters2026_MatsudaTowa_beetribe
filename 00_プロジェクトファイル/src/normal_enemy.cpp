//=============================================
//
//通常の敵の処理[normal_enemy.cpp]
//Author Matsuda Towa
//
//=============================================
#include "normal_enemy.h"
#include "normal_enemy_behavior.h"

//影のサイズ
const D3DXVECTOR3 CNormalEnemy::SHADOW_SIZE = { 20.0f, 0.0, 20.0f };

//=============================================
//コンストラクタ
//=============================================
CNormalEnemy::CNormalEnemy(int nPriority):CEnemy(nPriority)
{
	if (GetMoveStrategy() == nullptr)
	{
		SetMoveStrategy(new CNormalMove);
	}
	if (GetGunAttack() == nullptr)
	{
		SetGunAttack(new CNormalAttack);
	}
	if (GetStan() == nullptr)
	{
		SetStan(new CEnemyStan);
	}
	if (GetConfusion() == nullptr)
	{
		SetConfusion(new CEnemyConfusion);
	}
}

//=============================================
//デストラクタ
//=============================================
CNormalEnemy::~CNormalEnemy()
{
}

//=============================================
//初期化
//=============================================
HRESULT CNormalEnemy::Init()
{
	//銃初期化
	if (GetGun() == nullptr)
	{
		SetGun(new CAssultRifle);
		GetGun()->Init();
	}

	SetLife(DEFAULT_LIFE);

	//影のサイズ設定
	SetShadowSize(SHADOW_SIZE);

	//親クラスの初期化を呼ぶ
	CEnemy::Init();
	return S_OK;
}

//=============================================
//終了
//=============================================
void CNormalEnemy::Uninit()
{
	//親クラスの終了処理を呼ぶ
	CEnemy::Uninit();
}

//=============================================
//更新
//=============================================
void CNormalEnemy::Update()
{
	CEnemy::Update();
	Motion(); //モーション処理
}

//=============================================
//描画
//=============================================
void CNormalEnemy::Draw()
{
	CEnemy::Draw();
}

//=============================================
//ウルトヒット処理
//=============================================
void CNormalEnemy::MediumUltHit(D3DXVECTOR3 UltPos, int nDamage)
{
	ChangeState(new CStanState);

	//親クラスのヒット処理
	CEnemy::MediumUltHit(UltPos,nDamage);
}
