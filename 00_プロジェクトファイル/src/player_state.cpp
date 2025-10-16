//=============================================
//
//プレイヤーのステートパターン[player_state.cpp]
//Author Matsuda Towa
//
//=============================================
#include "player_state.h"
#include "manager.h"
#include "camera_state.h"
#include "active_player.h"

//=============================================
//デフォルト状態の処理
//=============================================
void CDefaultState::Default(CActivePlayer* player)
{
	if (player->GetUlt() != nullptr)
	{
		player->GetUlt()->Update();
	}

	player->Input();
}

//=============================================
//ウルト状態の処理
//=============================================
void CUltState::Ult(CActivePlayer* player)
{
	bool isFinish = false;
	if (player->GetUlt() != nullptr)
	{
		isFinish = player->GetUlt()->Action(player);
	}

	if (isFinish)
	{
		CCamera* pCamera = CManager::GetInstance()->GetCamera();
		pCamera->ChangeCameraState(new CThirdView);
		player->ChangePlayerState(new CDefaultState);
	}
}

//=============================================
//キャラクターの回避状態
//=============================================
void CAvoidanceState::Avoidance(CActivePlayer* player)
{

}

//=============================================
//コンストラクタ
//=============================================
CBlownState::CBlownState():m_nStanCnt(INT_ZERO)
{
}

//=============================================
//キャラクターの吹っ飛ばされ状態
//=============================================
void CBlownState::Blown(CActivePlayer* player)
{
	if (player->GetLaunding())
	{//着地したら
		++m_nStanCnt;
		player->SetMotion(CPlayer::MOTION_STAN);
		//スタックしないように当たり判定無効
		player->SetEnemyColision(true);
		if (m_nStanCnt > player->GetStanFrame())
		{//スタンが終わったら
			//当たり判定復活
			player->SetEnemyColision(false);
			m_nStanCnt = INT_ZERO;
			player->ChangePlayerState(new CDefaultState);
		}
	}
}
