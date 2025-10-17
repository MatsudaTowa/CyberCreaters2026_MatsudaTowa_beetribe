//=============================================
//
//ゲームプレイヤーのステートパターン[game_player_state.cpp]
//Author Matsuda Towa
//
//=============================================
#include "game_player_state.h"
#include "game_player.h"
#include "game_manager.h"
#include "field.h"
#include "flash_effect.h"

//=============================================
// ニュートラル処理
//=============================================
void My::CNeutralState::Neutral(CGamePlayer* player)
{
	//モーション設定
	player->SetMotion(CPlayer::MOTION_NEUTRAL);
}

//=============================================
// 自由移動処理
//=============================================
void My::CMovetoFreeState::MovetoFree(CGamePlayer* player)
{
	CMovePoint* point = player->GetMovePoint(0);
	if (point == nullptr)
	{
		return;
	}

	//モーション設定
	player->SetMotion(CPlayer::MOTION_MOVE);

	//プレイヤーの位置への方向情報
	D3DXVECTOR3 PointVector = point->GetPos() - player->GetPos();
	// 目的地との距離を計算
	float point_distance = sqrtf(PointVector.x * PointVector.x + PointVector.z * PointVector.z);

	//対象物との角度計算
	float angle = atan2f(PointVector.x, PointVector.z);

	D3DXVECTOR3 move = player->GetMove();

	bool isReached = isTargetReached(THRESHOLD, player->GetSpeed(), angle, point_distance, move);

	player->SetMove(move);
	D3DXVECTOR3 rot = player->GetRot();
	rot.y = angle + D3DX_PI;
	player->SetRot(rot);

	if (isReached)
	{
		player->EraseMovePoint(0);
		if (player->GetMovePoint(0) != nullptr)
		{
			return;
		}

		player->ChangeState(new CNeutralState);
	}
}
//コンボUIの位置
const D3DXVECTOR3 My::CAttackState::COMBO_UI_POS = { 1500.0f, 200.0f,0.0f };

//=============================================
// コンストラクタ
//=============================================
My::CAttackState::CAttackState()
{
}

//=============================================
// 攻撃処理
//=============================================
void My::CAttackState::Attack(CGamePlayer* player)
{
	CBoardHolder* board_holder = player->GetBoardHolder(0);

	LookAtBoardHolder(board_holder, player);

	if (typeid(*board_holder) != typeid(CTrapHolderInfo))
	{
		board_holder->BreakBoard();
	}

	CCombo* pCombo = player->GetComboUI();
	if (typeid(*board_holder) == typeid(CTrapHolderInfo))
	{
		if (pCombo != nullptr)
		{
			pCombo->SetNumCombo(INT_ZERO);
			pCombo->Uninit();
			pCombo = nullptr;
		}
		player->SetComboUI(pCombo);

		int time = CGameManager::GetInstance()->GetTimer()->GetCurrentTimer();
		time -= PENALTY;
		if (time <= CNormal::SPECIAL_TIME)
		{
			time =CGameManager::GetInstance()->GetTimer()->GetCurrentTimer();
		}
		CGameManager::GetInstance()->GetTimer()->SetCurrentTimer(time);
	}
	else
	{
		//スコア設定
		CScore* pScore = GET_SCORE;
		int score = pScore->GetCurrentScore();
		++score;
		pScore->SetCurrentScore(score);

		//コンボ設定
		if (pCombo == nullptr)
		{
			pCombo = CCombo::Create(COMBO_UI_POS);
		}
		int num_combo = pCombo->GetNumCombo();
		++num_combo;
		pCombo->SetNumCombo(num_combo);
		player->SetComboUI(pCombo);
	}
	D3DXVECTOR3 board_holder_pos = board_holder->GetPos();
	CFlashEffect::Create({board_holder_pos.x,1.0f,board_holder_pos.z});
	//TODO:消える演出を入れる
	board_holder->KnockDown();
	player->EraseBoardHolder();
	player->ChangeState(new CNeutralState);
}

//=============================================
// 板持ちの方を見る
//=============================================
void My::CAttackState::LookAtBoardHolder(My::CBoardHolder* board_holder, My::CGamePlayer* player)
{
	//プレイヤーとの距離算出
	D3DXVECTOR3 Distance = board_holder->GetPos() - player->GetPos();

	//プレイヤーに向ける角度を算出
	float fAngle = atan2f(Distance.x, Distance.z);

	//親クラスからrotを取得
	D3DXVECTOR3 rot = player->GetRot();

	rot.y = fAngle + D3DX_PI;

	player->SetRot(rot);
}