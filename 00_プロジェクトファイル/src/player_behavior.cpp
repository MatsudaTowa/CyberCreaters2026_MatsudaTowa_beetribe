//=============================================
//
//プレイヤーのストラテジーパターン[player_behavior.cpp]
//Author Matsuda Towa
//
//=============================================
#include "player_behavior.h"

//=============================================
//コンストラクタ
//=============================================
CPlayerMove::CPlayerMove()
{
}

//=============================================
//デストラクタ
//=============================================
CPlayerMove::~CPlayerMove()
{
}

//=============================================
//移動処理(プレイヤー)
//=============================================
void CPlayerMove::Move(CCharacter* character)
{
}

//=============================================
//コンストラクタ
//=============================================
CPlayerAttack::CPlayerAttack()
{
}

//=============================================
//デストラクタ
//=============================================
CPlayerAttack::~CPlayerAttack()
{
}

//=============================================
//攻撃処理(プレイヤー)
//=============================================
void CPlayerAttack::GunAttack(CBullet::BULLET_ALLEGIANCE Allegiance, CCharacter* character)
{
	CInputMouse* pMouse = CManager::GetInstance()->GetMouse();

	CCamera* pCamera = CManager::GetInstance()->GetCamera();

	character->SetMove(character->GetMove() * MOVE_SUBTRACTION);

	CPlayer::Motion_Type Motion;
	Motion = CPlayer::Motion_Type::MOTION_ATTACK;
	//モーション代入
	character->SetMotion(Motion);

	CGun* gun = character->GetGun();

	int nRateCnt = gun->GetRateCnt();

	bool isReload = character->GetReload();

	if (pMouse->GetPress(0) && !isReload)
	{//射撃ボタンが押されたら
		if (character->GetGunAttack() != nullptr)
		{
			if (gun->GetAmmo() > INT_ZERO)
			{
				++nRateCnt;

				ShotBullet(character, pCamera, Allegiance, nRateCnt);
			}
			else
			{
				isReload = true;
				character->SetReload(isReload);
			}
		}
	}
	if (pMouse->GetRelease(0))
	{
		nRateCnt = gun->GetFireRate();
	}
	gun->SetRateCnt(nRateCnt);
}

//=============================================
//弾発射
//=============================================
void CPlayerAttack::ShotBullet(CCharacter* character, CCamera* pCamera, const CBullet::BULLET_ALLEGIANCE& Allegiance, int& nRateCnt)
{
	CGun* gun = character->GetGun();
	if (nRateCnt >= gun->GetFireRate())
	{
		nRateCnt = INT_ZERO;

		//銃から発射
		D3DXVECTOR3 ShotPos = D3DXVECTOR3(character->m_apModel[14]->GetMtxWorld()._41 + sinf(character->GetRot().y + D3DX_PI),
			character->m_apModel[14]->GetMtxWorld()._42 + CORRECTION_Y, character->m_apModel[14]->GetMtxWorld()._43 + cosf(character->GetRot().y + D3DX_PI));

		//移動量設定
		D3DXVECTOR3 ShotMove = D3DXVECTOR3(sinf(pCamera->GetRot().y + D3DX_PI) * -gun->GetBulletSpeed(),
			sinf(pCamera->GetRot().x + D3DX_PI) * gun->GetBulletSpeed(),
			cosf(pCamera->GetRot().y + D3DX_PI) * -gun->GetBulletSpeed());
		//弾発射
		gun->m_pShot->Shot(ShotPos, ShotMove, gun->GetSize(), gun->GetDamage(), Allegiance, gun);

		CManager::GetInstance()->GetSound()->PlaySound(CSound::SOUND_LABEL_SE_SHOT);

		D3DXVECTOR3 camera_rot_move = pCamera->GetRotMove();
		//縦反動は一定
		camera_rot_move.x -= RECOIL;

		//横反動はランダム
		std::random_device seed;
		std::mt19937 random(seed());
		std::uniform_real_distribution<float> rot(-RECOIL, RECOIL);
		camera_rot_move.y -= rot(random);

		//反動設定
		pCamera->SetRotMove(camera_rot_move);
	}

	gun->SetRateCnt(nRateCnt);
}

//=============================================
//コンストラクタ
//=============================================
CPlayerAvoidance::CPlayerAvoidance()
{
}

//=============================================
//デストラクタ
//=============================================
CPlayerAvoidance::~CPlayerAvoidance()
{
}

//=============================================
//回避アクション
//=============================================
void CPlayerAvoidance::Avoidance(CCharacter* character)
{
	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetKeyboard();

	//移動の方向の単位ベクトル変数
	D3DXVECTOR3 vecDirection(VEC3_RESET_ZERO);

	if (pKeyboard->GetPress(DIK_W))
	{
		vecDirection.z += FLOAT_ONE;
	}
	else if (pKeyboard->GetPress(DIK_S))
	{
		vecDirection.z -= FLOAT_ONE;
	}
	else if (pKeyboard->GetPress(DIK_A))
	{
		vecDirection.x -= FLOAT_ONE;
	}
	else if (pKeyboard->GetPress(DIK_D))
	{
		vecDirection.x += FLOAT_ONE;
	}
	else
	{
		vecDirection.z -= FLOAT_ONE;
	}

	float rotMoveY = CManager::GetInstance()->GetCamera()->GetRot().y + atan2f(vecDirection.x, vecDirection.z);

	D3DXVECTOR3 move = character->GetMove();

	move.x += sinf(rotMoveY) * character->GetSpeed() * PLAYER_AVOIDANCE_SPEED;
	move.z += cosf(rotMoveY) * character->GetSpeed() * PLAYER_AVOIDANCE_SPEED;
	
	//親クラスからrotを取得
	D3DXVECTOR3 rot = character->GetRot();
	rot.y = rotMoveY + D3DX_PI;
	//rotを代入
	character->SetRot(rot);
	//移動量代入
	character->SetMove(move);
}
