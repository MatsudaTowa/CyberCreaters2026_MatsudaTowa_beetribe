//=============================================
//
//�Q�[���v���C���[�̃X�e�[�g�p�^�[��[game_player_state.cpp]
//Author Matsuda Towa
//
//=============================================
#include "game_player_state.h"
#include "game_player.h"
#include "game_manager.h"
#include "field.h"
#include "flash_effect.h"

//=============================================
// �j���[�g��������
//=============================================
void My::CNeutralState::Neutral(CGamePlayer* player)
{
	//���[�V�����ݒ�
	player->SetMotion(CPlayer::MOTION_NEUTRAL);
}

//=============================================
// ���R�ړ�����
//=============================================
void My::CMovetoFreeState::MovetoFree(CGamePlayer* player)
{
	CMovePoint* point = player->GetMovePoint(0);
	if (point == nullptr)
	{
		return;
	}

	//���[�V�����ݒ�
	player->SetMotion(CPlayer::MOTION_MOVE);

	//�v���C���[�̈ʒu�ւ̕������
	D3DXVECTOR3 PointVector = point->GetPos() - player->GetPos();
	// �ړI�n�Ƃ̋������v�Z
	float point_distance = sqrtf(PointVector.x * PointVector.x + PointVector.z * PointVector.z);

	//�Ώە��Ƃ̊p�x�v�Z
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
//�R���{UI�̈ʒu
const D3DXVECTOR3 My::CAttackState::COMBO_UI_POS = { 1500.0f, 200.0f,0.0f };

//=============================================
// �R���X�g���N�^
//=============================================
My::CAttackState::CAttackState()
{
}

//=============================================
// �U������
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
		//�X�R�A�ݒ�
		CScore* pScore = GET_SCORE;
		int score = pScore->GetCurrentScore();
		++score;
		pScore->SetCurrentScore(score);

		//�R���{�ݒ�
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
	//TODO:�����鉉�o������
	board_holder->KnockDown();
	player->EraseBoardHolder();
	player->ChangeState(new CNeutralState);
}

//=============================================
// �����̕�������
//=============================================
void My::CAttackState::LookAtBoardHolder(My::CBoardHolder* board_holder, My::CGamePlayer* player)
{
	//�v���C���[�Ƃ̋����Z�o
	D3DXVECTOR3 Distance = board_holder->GetPos() - player->GetPos();

	//�v���C���[�Ɍ�����p�x���Z�o
	float fAngle = atan2f(Distance.x, Distance.z);

	//�e�N���X����rot���擾
	D3DXVECTOR3 rot = player->GetRot();

	rot.y = fAngle + D3DX_PI;

	player->SetRot(rot);
}