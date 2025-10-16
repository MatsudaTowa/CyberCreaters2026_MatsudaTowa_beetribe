//=============================================
//
//ノーマルエネミーのストラテジーパターン[normal_enemy_behavior.cpp]
//Author Matsuda Towa
//
//=============================================
#include "normal_enemy_behavior.h"
#include "smoke_range.h"
#include "player.h"

//=============================================
//コンストラクタ
//=============================================
CNormalMove::CNormalMove():
m_TransitionCnt(INT_ZERO),		
m_nStateChangeCnt(INT_ZERO),
m_nStayCnt(INT_ZERO), 
m_bRandom(), 
m_nLeft(),
m_nRight(),
m_bDamage(false)
{
	m_nLeft = LEFT_PARCENT;
	m_nRight = RIGHT_PARCENT;
}

//=============================================
//デストラクタ
//=============================================
CNormalMove::~CNormalMove()
{
}

//=============================================
//移動
//=============================================
void CNormalMove::Move(CCharacter* character)
{
	if (m_bDamage)
	{
		++m_TransitionCnt;
		if (m_TransitionCnt > TRANSITION_FRAME)
		{
			m_bDamage = false;
			m_TransitionCnt = INT_ZERO;

			//射撃状態に
			character->ChangeState(new CShotState);
			return;
		}
	}
	if (m_nStateChangeCnt < MOVE_FRAME)
	{
		float move_x = FLOAT_ZERO;

		if (m_bRandom)
		{
			move_x = FLOAT_ONE;
		}
		if (!m_bRandom)
		{
			move_x = -FLOAT_ONE;
		}

		//横にしか移動しないのでxに値代入
		SetMoveVec({ move_x,0.0f,0.0f });

		//親クラスの移動を呼ぶ
		CEnemyMove::Move(character);

		++m_nStateChangeCnt;
	}
	if (m_nStateChangeCnt >= MOVE_FRAME)
	{
		Stay(character);
	}

	//自分の方向を取得
	D3DXVECTOR3 vec = { sinf(character->GetRot().y + D3DX_PI), 0.0f, cosf(character->GetRot().y + D3DX_PI) };

	CEnemy* pEnemy = dynamic_cast<CEnemy*>(character);
	CCharacter::RayHitInfo HitPlayerInfo = pEnemy->PerformRaycast_Player(vec, pEnemy);
	CCharacter::RayHitInfo HitBlockInfo = character->PerformRaycast_Block(vec, character);
	CCharacter::RayHitInfo HitSmokeInfo = character->PerformRaycast_Smoke(vec, character);

	if ((HitPlayerInfo.hit
	&&!HitBlockInfo.hit))
	{//ダメージ状態もしくはレイがプレイヤーに当たっていたら
		character->SetMotion(CEnemy::Motion_Type::MOTION_NEUTRAL);

		//射撃状態に
		character->ChangeState(new CShotState);
	}

	if (character->GetState() == CCharacter::CHARACTER_STATE::CHARACTER_DAMAGE)
	{
		m_bDamage = true;
	}
}

//=============================================
//正面を見て止まる
//=============================================
void CNormalMove::Stay(CCharacter* character)
{
	character->SetRot(VEC3_RESET_ZERO);

	if (m_nStayCnt < STAY_FRAME)
	{
		character->SetMotion(CEnemy::Motion_Type::MOTION_NEUTRAL);
		++m_nStayCnt;
	}
	if (m_nStayCnt >= STAY_FRAME)
	{
		m_nStateChangeCnt = INT_ZERO;
		m_nStayCnt = INT_ZERO;
		NextMove_X(character);
	}
}

//=============================================
//動く処理が終わったら次の方向を抽選
//=============================================
void CNormalMove::NextMove_X(CCharacter* character)
{
	std::random_device seed;
	std::mt19937 random(seed());
	std::uniform_int_distribution<int> number(0, 100);

	//どっちに行くかの確率
	if (number(random) <= m_nRight)
	{
		m_bRandom = true;
		if (m_nRight > 0)
		{//右に進む確率を下げる
			m_nRight -= PROBABILITY_SCALE;
		}
	}
	else if (number(random) > m_nRight && number(random) <= m_nLeft)
	{
		m_bRandom = false;
		if (m_nRight < 100)
		{//右に進む確率をあげる
			m_nRight += PROBABILITY_SCALE;
		}
	}
}

//=============================================
//コンストラクタ
//=============================================
CNormalAttack::CNormalAttack():m_nLostCnt(0)
{
}

//=============================================
//デストラクタ
//=============================================
CNormalAttack::~CNormalAttack()
{
}

//=============================================
//攻撃
//=============================================
void CNormalAttack::GunAttack(CBullet::BULLET_ALLEGIANCE Allegiance, CCharacter* character)
{
	LookAtPlayer(character);

	//自分の方向を取得
	D3DXVECTOR3 vec = { sinf(character->GetRot().y + D3DX_PI), 0.0f, cosf(character->GetRot().y + D3DX_PI) };

	//D3DXVec3Normalize(&vec, &vec);

	CEnemy* pEnemy = dynamic_cast<CEnemy*>(character);
	CCharacter::RayHitInfo HitPlayerInfo = pEnemy->PerformRaycast_Player(vec, pEnemy);

	if (HitPlayerInfo.hit)
	{
		if (character->PerformRaycast_Block(vec, character).hit)
		{//ブロックに当たっていたら
			if (character->PerformRaycast_Block(vec, character).distance > HitPlayerInfo.distance)
			{//ブロックより手前にいるときに
				CEnemyGunAttack::GunAttack(Allegiance, character);
			}
			else if (character->PerformRaycast_Block(vec, character).distance < HitPlayerInfo.distance)
			{
				++m_nLostCnt;
			}
		}
		else if (!character->PerformRaycast_Block(vec, character).hit)
		{
			m_nLostCnt = 0;
			CEnemyGunAttack::GunAttack(Allegiance, character);
		}
	}

	if (character->PerformRaycast_Smoke(vec, character).hit || m_nLostCnt > LOST_FRAME)
	{//スモークに当たってたら
		character->ChangeState(new CConfusionState);
		return;;
	}
}