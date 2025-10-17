//=============================================
//
//動かすプレイヤー[active_player.cpp]
//Author Matsuda Towa
//
//=============================================
#include "active_player.h"
#include "manager.h"
#include "input.h"
#include "block.h"
#include "field.h"
#include "camera.h"
#include "game.h"
#include "smoke_grenade.h"
#include "camera_state.h"
#include "reload_UI.h"
#include "blink_UI.h"
#include "smoke_UI.h"
#include"ammo_UI.h"
#include"life_UI.h"
#include "ult_UI.h"

//スポーン位置
const D3DXVECTOR3 CActivePlayer::PLAYER_SPAWN_POS = { 0.0f, 0.5f, -400.0f };

//スポーン方向
const D3DXVECTOR3 CActivePlayer::PLAYER_SPAWN_ROT = { 0.0f, 3.14f, 0.0f };

//影のサイズ
const D3DXVECTOR3 CActivePlayer::SHADOW_SIZE = { 20.0f, 0.0, 20.0f };

//銃のUIの位置
const D3DXVECTOR3 CActivePlayer::GUN_UI_POS = { 1150.0f, 665.0f, 0.0f };

//銃のUIのサイズ
const D3DXVECTOR2 CActivePlayer::GUN_UI_SIZE = { 70.0f,30.0f };

//=============================================
//コンストラクタ
//=============================================
CActivePlayer::CActivePlayer(int nPriority) :CPlayer(nPriority),
m_Reticle(),					//レティクルのポインタ初期化
m_IgnoreColisionCnt(INT_ZERO),	//当たり判定無効カウントリセット
m_SmokeRecastCnt(INT_ZERO),		//スモーク復活カウントリセット
m_DeathCnt(INT_ZERO),			//死亡カウントリセット
m_Stamina(INT_ZERO),			//スタミナ
m_isSmoke(false),				//スモークを使っていない状態に
m_isEnemyColision(true),		//エネミーと判定をとる状態に
m_pHitCameraEffect(),			//カメラのエフェクトのポインタ初期化
m_pGunIcon(),					//銃のアイコンのポインタ初期化
m_pUlt(),						//ウルトのポインタ初期化 
m_pPlayerState(),				//プレイヤーのステート初期化
m_pAmmoUI(),					//残弾数UIの初期化
m_pLifeUI(),					//体力UIの初期化
m_pUltUI(),						//ウルトのUI初期化
m_pSmokeUI(),					//スモークのUI初期化
m_pBlinkUI(),					//ブリンクのUI初期化
m_pReloadUI()					//リロードのUI初期化
{
}

//=============================================
//デストラクタ
//=============================================
CActivePlayer::~CActivePlayer()
{
}

//=============================================
//初期化
//=============================================
HRESULT CActivePlayer::Init()
{
	CPlayer::Init();

	SetPos(PLAYER_SPAWN_POS); //pos設定
	SetRot(PLAYER_SPAWN_ROT); //rot設定
	SetLife(PLAYER_LIFE); //体力代入

	//ステート変更フレーム代入
	SetStateFrame(DAMAGE_FRAME);

	//スタンフレーム数代入
	SetStanFrame(STAN_FRAME);

	//スタミナ初期化
	m_Stamina = PLAYER_STAMINA;

	if (m_pAvoidance == nullptr)
	{
		m_pAvoidance = new CPlayerAvoidance;
	}
	if (GetMoveStrategy() == nullptr)
	{
		SetMoveStrategy(new CPlayerMove);
	}
	if (GetGunAttack() == nullptr)
	{
		SetGunAttack(new CPlayerAttack);
	}

	if (m_pPlayerState == nullptr)
	{
		m_pPlayerState = new CDefaultState;
	}

	//銃初期化
	if (GetGun() == nullptr)
	{
		SetGun(new CAssultRifle);
		GetGun()->Init();
	}

	if (m_pUlt == nullptr)
	{
		m_pUlt = new CMediumUlt;
		m_pUlt->Init();
	}

	//ブリンクの回数算出
	m_BlinkCnt = PLAYER_STAMINA / AVOIDANCE_COST;

	//UI生成
	CreateUI();

	//移動量初期化
	D3DXVECTOR3 move = VEC3_RESET_ZERO;

	//カメラ情報取得
	CCamera* pCamera = CManager::GetInstance()->GetCamera();
	pCamera->SetRot(VEC3_RESET_ZERO);

	//ムーブ値代入
	SetMove(move);

	//初期モーション設定
	SetMotion(MOTION_NEUTRAL);

	//影のサイズ設定
	SetShadowSize(SHADOW_SIZE);

	return S_OK;
}

//=============================================
//UI生成
//=============================================
void CActivePlayer::CreateUI()
{
	if (m_pGunIcon == nullptr)
	{
		m_pGunIcon = CGunIcon::Create(GUN_UI_POS, GUN_UI_SIZE, COLOR_WHITE, CGunIcon::ICON_TYPE::ICON_TYPE_AR);
	}
	//残弾数初期化
	if (m_pAmmoUI == nullptr)
	{
		m_pAmmoUI = new CAmmo_UI;

		m_pAmmoUI->Init();

		m_pAmmoUI->SetDefaultAmmo_UI(GetGun()->GetAmmo());
	}
	//体力UI初期化
	if (m_pLifeUI == nullptr)
	{
		m_pLifeUI = new CLife_UI;

		m_pLifeUI->Init();
	}
	//ブリンクUI初期化
	if (m_pBlinkUI == nullptr)
	{
		m_pBlinkUI = new CBlink_UI;

		m_pBlinkUI->Init();
	}
	//ウルトUI初期化
	if (m_pUltUI == nullptr)
	{
		m_pUltUI = new CUlt_UI;

		m_pUltUI->Init(this);
	}

	if (m_pSmokeUI == nullptr)
	{
		m_pSmokeUI = new CSmoke_UI;
		m_pSmokeUI->Init(this);
	}

}

//=============================================
//終了
//=============================================
void CActivePlayer::Uninit()
{
	if (m_pAmmoUI != nullptr)
	{
		m_pAmmoUI->Uninit();
		m_pAmmoUI = nullptr;
	}
	if (m_pLifeUI != nullptr)
	{
		m_pLifeUI->Uninit();
		m_pLifeUI = nullptr;
	}
	if (m_pBlinkUI != nullptr)
	{
		m_pBlinkUI->Uninit();
		m_pBlinkUI = nullptr;
	}
	if (m_pUltUI != nullptr)
	{
		m_pUltUI->Uninit();
		m_pUltUI = nullptr;
	}
	if (m_pGunIcon != nullptr)
	{
		m_pGunIcon->Uninit();
		m_pGunIcon = nullptr;
	}
	if (m_pUlt != nullptr)
	{
		m_pUlt->Uninit();
		m_pUlt = nullptr;
	}
	if (m_pSmokeUI != nullptr)
	{
		m_pSmokeUI->Uninit();
		m_pSmokeUI = nullptr;
	}
	if (m_pReloadUI != nullptr)
	{
		m_pReloadUI->Uninit();
		m_pReloadUI = nullptr;
	}
	if (m_pAvoidance != nullptr)
	{
		delete m_pAvoidance;
		m_pAvoidance = nullptr;
	}
	if (m_Reticle != nullptr)
	{
		m_Reticle->Uninit();
		m_Reticle = nullptr;
	}
	if (m_pAvoidance != nullptr)
	{
		delete m_pAvoidance;
		m_pAvoidance = nullptr;
	}
	if (m_pPlayerState != nullptr)
	{
		delete m_pPlayerState;
	}

	//親クラスの終了処理を呼ぶ
	CPlayer::Uninit();
}

//=============================================
//更新
//=============================================
void CActivePlayer::Update()
{
	CPlayer::Update();

	//ダメージステートの切り替え
	ChangeDamageState();

	if (m_pPlayerState != nullptr)
	{
		m_pPlayerState->Default(this);
		m_pPlayerState->Ult(this);
		m_pPlayerState->Blown(this);
	}

	if (m_pHitCameraEffect != nullptr)
	{//使われていたら
		m_pHitCameraEffect->SubAlpha();

		if (m_pHitCameraEffect->GetAlpha() < FLOAT_ZERO)
		{
			m_pHitCameraEffect->Uninit();
			m_pHitCameraEffect = nullptr;
		}
	}

	if (m_isBlown)
	{
		if (GetLaunding())
		{//着地したら
			//スタン状態に
			m_isBlown = false;
		}
	}

	//敵と判定をとる場合だったらとる
	//とらない場合はカウントアップ
	CanDetectEnemyCollision();

	//UI設定
	SetUI();

	//状態を取得
	CCharacter::CHARACTER_STATE state = GetState();

	if (state == CCharacter::CHARACTER_STATE::CHARACTER_DAMAGE)
	{
		//状態のカウント数取得
		int nStateCnt = GetStateCnt();

		//ステート変更カウント進める
		++nStateCnt;

		//ステートカウント代入
		SetStateCnt(nStateCnt);
	}

	if (m_isSmoke)
	{//スモークが使った状態だったら
		++m_SmokeRecastCnt;
		if (m_SmokeRecastCnt > SMOKE_RECAST_FRAME)
		{
			m_SmokeRecastCnt = INT_ZERO;
			m_isSmoke = false;
		}
	}

	if (m_Stamina < PLAYER_STAMINA)
	{//スタミナが減ってたら

		++m_StaminaRecoveryCnt;
		if (m_StaminaRecoveryCnt >= STAMINA_RECOVERY_FRAME)
		{//カウントが到達したら

			//カウントリセット
			m_StaminaRecoveryCnt = INT_ZERO;

			//スタミナ回復
			m_Stamina += STAMINA_RECOVERY;

			int nStaminaPer = m_Stamina % AVOIDANCE_COST;
			if (nStaminaPer == INT_ZERO)
			{
				++m_BlinkCnt;
			}

			if (m_Stamina >= PLAYER_STAMINA)
			{//スタミナがデフォルト値に到達したら
				//スタミナ代入
				m_Stamina = PLAYER_STAMINA;
			}
		}
	}

	//カメラ情報取得
	CCamera* pCamera = CManager::GetInstance()->GetCamera();

	if (m_Reticle != nullptr)
	{
		m_Reticle->SetPos(D3DXVECTOR3(pCamera->GetPosR().x + sinf(GetRot().y + D3DX_PI), pCamera->GetPosR().y - RETICLE_CORRECTION_VALUE, pCamera->GetPosR().z + cosf(GetRot().y + D3DX_PI)));
		m_Reticle->Update();
	}
}

//=============================================
//リロード処理
//=============================================
void CActivePlayer::Reload()
{
	bool isReload = GetReload();
	if (isReload)
	{//リロード中だったら
		isReload = GetGun()->Reload(); //リロードし終わったらfalseが返ってくる
		if (!isReload)
		{
			CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_RELOAD);

			if (m_pReloadUI == nullptr)
			{
				return;
			}
			m_pReloadUI->Uninit();
			m_pReloadUI = nullptr;;
		}
		else if (isReload)
		{
			if (m_pReloadUI == nullptr)
			{
				m_pReloadUI = new CReload_UI;
				m_pReloadUI->Init();
			}
		}
	}
	SetReload(isReload);
}

//=============================================
//UI設定
//=============================================
void CActivePlayer::SetUI()
{
	if (m_pAmmoUI != nullptr)
	{
		m_pAmmoUI->SetCurrentAmmo_UI(GetGun()->GetAmmo());
	}

	if (m_pLifeUI != nullptr)
	{
		m_pLifeUI->SetLife_UI(GetLife());
	}

	if (m_pBlinkUI != nullptr)
	{
		m_pBlinkUI->SetCurrentBlink_UI(this);
	}
	if (m_pSmokeUI != nullptr)
	{
		m_pSmokeUI->SetCurrentSmoke_UI(this);
	}
}

//=============================================
//敵との判定
//=============================================
void CActivePlayer::CanDetectEnemyCollision()
{
	if (m_isEnemyColision)
	{//敵との当たり判定をとる状態だったら
		ColisionEnemy();
		return;
	}
	//敵との当たり判定をとらない状態だったら
	++m_IgnoreColisionCnt;

	if (m_IgnoreColisionCnt > IGNORE_COLLISION_FRAME)
	{//フレームに到達したら
		//当たり判定をとる状態に
		m_IgnoreColisionCnt = INT_ZERO;
		m_isEnemyColision = true;
	}
}

//=============================================
//描画
//=============================================
void CActivePlayer::Draw()
{
	CPlayer::Draw();
}

//=============================================
//ダメージを受けたとき
//=============================================
void CActivePlayer::Damage(int nDamage)
{
	//体力取得
	int nLife = GetLife();

	//状態を取得
	CCharacter::CHARACTER_STATE state = GetState();

	if (nLife > INT_ZERO && state != CCharacter::CHARACTER_STATE::CHARACTER_DAMAGE)
	{//ダメージ状態以外でHPが残ってたら

		if (m_pHitCameraEffect == nullptr)
		{
			if (nLife >= PLAYER_LIFE * 0.6f)
			{
				m_pHitCameraEffect = CHitCameraEffect::Create({ SCREEN_WIDTH * HALF,SCREEN_HEIGHT * HALF,0.0f }, CHitCameraEffect::HIT_EFFECT_STAGE::MILD);
			}
			else if (nLife >= PLAYER_LIFE * 0.3f && nLife < PLAYER_LIFE * 0.6f)
			{
				m_pHitCameraEffect = CHitCameraEffect::Create({ SCREEN_WIDTH * HALF,SCREEN_HEIGHT * HALF,0.0f }, CHitCameraEffect::HIT_EFFECT_STAGE::MODERATE);
			}
			else if (nLife < PLAYER_LIFE * 0.3f)
			{
				m_pHitCameraEffect = CHitCameraEffect::Create({ SCREEN_WIDTH * HALF,SCREEN_HEIGHT * HALF,0.0f }, CHitCameraEffect::HIT_EFFECT_STAGE::SEVERE);
			}
		}

		nLife -= nDamage;

		//ダメージ状態に変更
		state = CCharacter::CHARACTER_STATE::CHARACTER_DAMAGE;

		//状態代入
		SetState(state);

		//体力代入
		SetLife(nLife);
	}
	if (nLife <= INT_ZERO)
	{//HPが0以下だったら
		//リスポーン
		ReSpawn();
	}
}

//=============================================
//リスポーン
//=============================================
void CActivePlayer::ReSpawn()
{
	//自分自身のpos取得
	D3DXVECTOR3 PlayerPos = GetPos();

	//スポーン時の設定にもどす
	SetPos(CActivePlayer::PLAYER_SPAWN_POS);
	SetMove(VEC3_RESET_ZERO);
	SetBlown(false);
	SetRot(CActivePlayer::PLAYER_SPAWN_ROT);
	SetLife(CActivePlayer::PLAYER_LIFE);
	SetStamina(CActivePlayer::PLAYER_STAMINA);
	m_BlinkCnt = PLAYER_STAMINA / AVOIDANCE_COST;
	m_StaminaRecoveryCnt = INT_ZERO;
	m_isSmoke = true;
	m_SmokeRecastCnt = INT_ZERO;

	GetGun()->SetAmmo(CAssultRifle::DEFAULT_AR_MAG_SIZE);
	ChangePlayerState(new CDefaultState);

	++m_DeathCnt;
}

//=============================================
//移動処理
//=============================================
void CActivePlayer::Input()
{
	CInputMouse* pMouse = CManager::GetInstance()->GetMouse();

	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetKeyboard();

	CCamera* pCamera = CManager::GetInstance()->GetCamera();

	//移動の方向の単位ベクトル変数
	D3DXVECTOR3 vecDirection(VEC3_RESET_ZERO);
	if (pKeyboard->GetPress(DIK_W))
	{
		vecDirection.z += FLOAT_ONE;
	}
	if (pKeyboard->GetPress(DIK_S))
	{
		vecDirection.z -= FLOAT_ONE;
	}
	if (pKeyboard->GetPress(DIK_A))
	{
		vecDirection.x -= FLOAT_ONE;
	}
	if (pKeyboard->GetPress(DIK_D))
	{
		vecDirection.x += FLOAT_ONE;
	}

	float rotMoveY = CManager::GetInstance()->GetCamera()->GetRot().y + atan2f(vecDirection.x, vecDirection.z);

	CPlayer::Motion_Type Motion;

	if (vecDirection.x == FLOAT_ZERO && vecDirection.z == FLOAT_ZERO)
	{ // 動いてない。
		Motion = CPlayer::Motion_Type::MOTION_NEUTRAL;
	}
	else
	{
		Motion = CPlayer::Motion_Type::MOTION_MOVE;
	}

	D3DXVECTOR3 move = GetMove();
	if (vecDirection.x == FLOAT_ZERO && vecDirection.z == FLOAT_ZERO)
	{ // 動いてない。
		move.x = 0.0f;
		move.z = 0.0f;
	}
	else
	{
		move.x += sinf(rotMoveY) * GetSpeed();
		move.z += cosf(rotMoveY) * GetSpeed();
	}
	//親クラスからrotを取得
	D3DXVECTOR3 rot = GetRot();
	rot.y = rotMoveY + D3DX_PI;
	//rotを代入
	SetRot(rot);
	//移動量代入
	SetMove(move);

	//モーション代入
	SetMotion(Motion);

	if (pKeyboard->GetTrigger(DIK_LSHIFT))
	{
		if (m_Stamina >= AVOIDANCE_COST)
		{//スタミナがあれば
			//ブリンクSEを鳴らす
			CManager::GetInstance()->GetSound()->PlaySound(CSound::SOUND_LABEL_SE_BLINK);
			m_pAvoidance->Avoidance(this);
			m_Stamina -= AVOIDANCE_COST;

			--m_BlinkCnt;

			if (m_Stamina <= INT_ZERO)
			{//スタミナが0を下回ったら
				m_Stamina = INT_ZERO;
			}
		}
	}

	if (pKeyboard->GetPress(DIK_X))
	{
		if (m_pUlt != nullptr)
		{
			if (m_pUlt->GetCoolTimeCnt() >= m_pUlt->GetCoolTime())
			{
				pCamera->ChangeCameraState(new CUltCameraState);
				ChangePlayerState(new CUltState);
				m_pUltUI->Reset(); //UIのリセット処理

				m_isEnemyColision = false;
			}
		}
	}

	if (pMouse->GetPress(1))
	{//マウスが押されてる間は

		//モーションを変更 TODO:覗きこむモーションに
		SetMotion(MOTION_NEUTRAL);

		ResetRot(); //レティクルのほうを向きたいので

		if (m_Reticle == nullptr)
		{//使われていなかったら
			m_Reticle = new CReticle;

			//値を代入
			m_Reticle->SetPos(D3DXVECTOR3(pCamera->GetPosR().x + sinf(GetRot().y + D3DX_PI), pCamera->GetPosR().y - 20.0f, pCamera->GetPosR().z + cosf(GetRot().y + D3DX_PI)));
			m_Reticle->SetSize({ 5.0f,5.0f,0.0f });

			m_Reticle->Init();
		}
		//射撃状態に変更
		ChangeState(new CShotState);
		m_pCharacterState->Shot(CBullet::BULLET_ALLEGIANCE_PLAYER, this);
	}

	if (pMouse->GetRelease(1))
	{//マウスが離されたら
		if (m_Reticle != nullptr)
		{//使われていたら
			m_Reticle->Uninit();
			m_Reticle = nullptr;
		}
		//移動状態に変更
		ChangeState(new CMoveState);
	}

	if (pKeyboard->GetTrigger(DIK_R) && !pMouse->GetPress(0))
	{
		if (GetGun()->GetAmmo() < CAssultRifle::DEFAULT_AR_MAG_SIZE)
		{
			//リロード
			SetReload(true);
		}
	}

	if (!m_isSmoke)
	{
		if (pKeyboard->GetTrigger(DIK_Q))
		{
			m_isSmoke = true;
			CSmokeGrenade::Create({ GetPos().x,GetPos().y + SMOKE_CORRECTION_VALUE,GetPos().z }, { sinf(pCamera->GetRot().y + D3DX_PI) * -SMOKE_SHOT_SPEED,
					sinf(pCamera->GetRot().x + D3DX_PI) * SMOKE_SHOT_SPEED,
					cosf(pCamera->GetRot().y + D3DX_PI) * -SMOKE_SHOT_SPEED }, VEC3_RESET_ZERO);
		}
	}
}

//=============================================
//プレイヤーのステート変更
//=============================================
void CActivePlayer::ChangePlayerState(CPlayerState* state)
{
	//今のステートを消し引数のステートに切り替える
	if (m_pPlayerState != nullptr)
	{
		delete m_pPlayerState;
		m_pPlayerState = state;
	}
	else if (m_pPlayerState == nullptr)
	{
		delete state;
	}
}

//=============================================
//プレイヤーの方向をカメラのほうへ
//=============================================
void CActivePlayer::ResetRot()
{
	float rotMoveY = CManager::GetInstance()->GetCamera()->GetRot().y;

	//親クラスからrotを取得
	D3DXVECTOR3 rot = GetRot();

	rot.y = rotMoveY + D3DX_PI;

	SetRot(rot);
}

//=============================================
//エネミーとの当たり判定
//=============================================
void CActivePlayer::ColisionEnemy()
{
	for (int nPartsCnt = INT_ZERO; nPartsCnt < GetNumParts(); ++nPartsCnt)
	{
		D3DXVECTOR3 pos = { m_apModel[nPartsCnt]->GetMtxWorld()._41,m_apModel[nPartsCnt]->GetMtxWorld()._42,m_apModel[nPartsCnt]->GetMtxWorld()._43 };
		D3DXVECTOR3 Minpos = m_apModel[nPartsCnt]->GetMin();
		D3DXVECTOR3 Maxpos = m_apModel[nPartsCnt]->GetMax();
		for (int nCnt = INT_ZERO; nCnt < MAX_OBJECT; nCnt++)
		{
			//オブジェクト取得
			CObject* pObj = CObject::Getobject(CEnemy::ENEMY_PRIORITY, nCnt);
			if (pObj != nullptr)
			{//オブジェクトに要素が入っていたら
				//タイプ取得
				CObject::OBJECT_TYPE type = pObj->GetType();

				//ブロックとの当たり判定
				if (type == CObject::OBJECT_TYPE::OBJECT_TYPE_ENEMY)
				{
					//安全にダウンキャスト
					CEnemy* pEnemy = dynamic_cast<CEnemy*>(pObj);

					CheckColisionEnemy(pEnemy, pos, Minpos, Maxpos);
				}
			}
		}
	}
}

//=============================================
//敵との当たり判定
//=============================================
void CActivePlayer::CheckColisionEnemy(CEnemy* pEnemy, const D3DXVECTOR3 pos, const D3DXVECTOR3 Minpos, const D3DXVECTOR3 Maxpos)
{
	for (int nEnemyPartsCnt = INT_ZERO; nEnemyPartsCnt < pEnemy->GetNumParts(); nEnemyPartsCnt++)
	{
		D3DXVECTOR3 Enemypos = { pEnemy->m_apModel[nEnemyPartsCnt]->GetMtxWorld()._41,
			pEnemy->m_apModel[nEnemyPartsCnt]->GetMtxWorld()._42,
			pEnemy->m_apModel[nEnemyPartsCnt]->GetMtxWorld()._43 };

		D3DXVECTOR3 EnemyMinpos = pEnemy->m_apModel[nEnemyPartsCnt]->GetMin();
		D3DXVECTOR3 EnemyMaxpos = pEnemy->m_apModel[nEnemyPartsCnt]->GetMax();
		CColision::COLISION colision = CManager::GetInstance()->GetColision()->CheckColisionSphere(pos, Minpos, Maxpos,
			Enemypos, EnemyMinpos, EnemyMaxpos);

		if (colision == CColision::COLISION::COLISON_X)
		{
			// X軸衝突時の処理
			SetPos({ GetOldPos().x, GetPos().y, GetPos().z });
		}
		if (colision == CColision::COLISION::COLISON_TOP_Y)
		{
			// X軸衝突時の処理
			SetPos({ GetPos().x, GetOldPos().y, GetPos().z });
		}
		if (colision == CColision::COLISION::COLISON_Z)
		{
			// X軸衝突時の処理
			SetPos({ GetPos().x, GetPos().y, GetOldPos().z });
		}
	}
}

//=============================================
//プレイヤーのデバッグ表示
//=============================================
void CActivePlayer::DebugPos()
{
#ifdef _DEBUG
	LPD3DXFONT pFont = CManager::GetInstance()->GetRenderer()->GetFont();
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	sprintf(&aStr[0], "\n\n[player]\npos:%.1f,%.1f,%.1f\nrot:%.1f,%.1f,%.1f\nmove:%.1f,%.1f,%.1f\n弾数:%d\n体力:%d\nスタミナ:%d"
		, GetPos().x, GetPos().y, GetPos().z, GetRot().x, GetRot().y, GetRot().z, GetMove().x, GetMove().y, GetMove().z, GetGun()->GetAmmo(), GetLife(), GetStamina());
	//テキストの描画
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 0, 0, 255));
#endif // _DEBUG
}
