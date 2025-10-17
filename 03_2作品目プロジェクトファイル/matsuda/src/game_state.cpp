//=============================================
//
//�Q�[���̃X�e�[�g�p�^�[��[game_state.cpp]
//Author Matsuda Towa
//
//=============================================
#include "game_state.h"
#include "game.h"
#include "game_manager.h"

//=============================================
// �ʏ�
//=============================================
void My::CNormal::Normal(CGame* game)
{
	//�I�u�W�F�N�g�̃A�b�v�f�[�g��������
	game->UpdateObjectDecision(false);

	CGamePlayer* player = CGameManager::GetInstance()->GetPlayer();
	if (typeid(*player->GetState()) == typeid(CAttackState))
	{
		CGameManager::GetInstance()->ChangeState(new CAttack);
		return;
	}

	CTimer* timer = CGameManager::GetInstance()->GetTimer();
	int old_time = timer->GetCurrentTimer();

	timer->DecreaseTime();

	int current_time = timer->GetCurrentTimer();
	if (current_time < SPECIAL_TIME)
	{//���݂̎��Ԃ��K�E�Z�̎��Ԃ�������Ă���
		//�ۑ����Ă��ߋ��̎��Ԃɖ߂�
		current_time = old_time;
		timer->SetCurrentTimer(current_time);
	}

	//NOTE:�����Ńe�N�X�`�����Y�������ߑO�̒i�K�Ń^�C���̐ݒ���s��
	timer->Update();

	//���̓f�o�C�X�擾
	CInputKeyboard* pKeyboard = GET_INPUT_KEYBOARD;

#ifdef _DEBUG
	if (pKeyboard->GetTrigger(DIK_0))
	{//�K�E�Z��Ԃ̎��Ԃ�
		timer->SetCurrentTimer(SPECIAL_TIME);
	}
#endif // DEBUG
	CGameMouseCursor* mouse = CGameManager::GetInstance()->GetMouseCursor();

	if (current_time <= SPECIAL_TIME
		&& typeid(*mouse->GetState()) == typeid(CNormalCursol))
	{//���Ԃ��K�E�Z���s����ԂŃJ�������ォ��A�}�E�X�J�[�\�����ʏ��ԂȂ�
		
		if (CGameManager::GetInstance()->GetGenerator()->ManyCreate(CGameManager::GetInstance()->GetField()))
		{
			CGameManager::GetInstance()->ChangeState(new CSpecialWrite);
		}
		return;
	}

	CBoardHolderGenerator* generator = CGameManager::GetInstance()->GetGenerator();

	if (generator != nullptr)
	{
		if (typeid(*mouse->GetState()) == typeid(CNormalCursol))
		{
			generator->Generate();
		}
	}

	//�|�[�Y�ڍs
	if (pKeyboard->GetTrigger(DIK_P) && game->GetPauseKey())
	{
		game->ResetPauseCnt();
		CGameManager::GetInstance()->ChangeState(new CPause);
		return;
	}
}

//=============================================
// �f�X�g���N�^
//=============================================
My::CAttack::~CAttack()
{
}

//=============================================
// �U��
//=============================================
void My::CAttack::Attack(CGame* game)
{
	//���̓f�o�C�X�擾
	CInputKeyboard* pKeyboard = GET_INPUT_KEYBOARD;

	CGamePlayer* player = CGameManager::GetInstance()->GetPlayer();
	if (typeid(*player->GetState()) != typeid(CAttackState))
	{
		CGameManager::GetInstance()->ChangeState(new CNormal);
		return;
	}
}

//=============================================
// �f�X�g���N�^
//=============================================
My::CPause::~CPause()
{
	CGameMouseCursor* mouse = CGameManager::GetInstance()->GetMouseCursor();

	if (mouse->GetTrailPointSize() > 0)
	{
		mouse->ChangeState(new CWrittenCursol);
		return;
	}
	mouse->ChangeState(new CNormalCursol);
}

//=============================================
// �|�[�Y
//=============================================
void My::CPause::Pause(CGame* game)
{
	//�I�u�W�F�N�g�̃A�b�v�f�[�g���~�߂�
	game->UpdateObjectDecision(true);

	//�}�E�X�̍X�V�͌Ă�
	CGameMouseCursor* mouse = CGameManager::GetInstance()->GetMouseCursor();
	mouse->ChangeState(new CPauseCursol);
	mouse->SetStop(false);

	//���̓f�o�C�X�擾
	CInputKeyboard* pKeyboard = GET_INPUT_KEYBOARD;

	if (pKeyboard->GetTrigger(DIK_P) && game->GetPauseKey())
	{
		game->ResetPauseCnt();
		CGameManager::GetInstance()->ChangeState(new CNormal);
		return;
	}
}

//=============================================
// �R���X�g���N�^
//=============================================
My::CSpecialWrite::CSpecialWrite()
{
	CPaper::Create({ SCREEN_WIDTH * HALF,SCREEN_HEIGHT * HALF,0.0f });

	std::list<CBoardHolder*>holder = CGameManager::GetInstance()->GetGenerator()->GetBoardHolderList();
	for (auto& itr : holder)
	{
		if (typeid(*itr) != typeid(CTrapHolderInfo))
		{
			continue;
		}
		itr->Uninit();
		itr = nullptr;
	}

	CCombo* combo = CGameManager::GetInstance()->GetPlayer()->GetComboUI();
	if (combo == nullptr)
	{
		return;
	}
	combo->Uninit();
	combo = nullptr;
	CGameManager::GetInstance()->GetPlayer()->SetComboUI(combo);

}

//=============================================
// �f�X�g���N�^
//=============================================
My::CSpecialWrite::~CSpecialWrite()
{
	CPaper* paper = CGameManager::GetInstance()->GetPaper();
	if (paper != nullptr)
	{
		paper->Uninit();
		paper = nullptr;
		CGameManager::GetInstance()->SetPaper(paper);
	}
}

//=============================================
// �K�E�Z��`��
//=============================================
void My::CSpecialWrite::SpecialWrite(CGame* game)
{
	//�v���C���[�̃A�b�v�f�[�g���~�߂�
	CGameManager::GetInstance()->GetPlayer()->SetStop(true);
	//�}�E�X�̍X�V�͌Ă�
	CGameMouseCursor* mouse = CGameManager::GetInstance()->GetMouseCursor();
	mouse->SetStop(false);
	CPaper* paper = CGameManager::GetInstance()->GetPaper();
	if (paper != nullptr)
	{
		paper->SetStop(false);
	}
}

//=============================================
// �R���X�g���N�^
//=============================================
My::CSpecialAttack::CSpecialAttack()
{
}

//=============================================
// �f�X�g���N�^
//=============================================
My::CSpecialAttack::~CSpecialAttack()
{
}

//=============================================
// �K�E�Z�U������
//=============================================
void My::CSpecialAttack::SpecialAttack(CGame* game)
{
	//�I�u�W�F�N�g�̃A�b�v�f�[�g������
	game->UpdateObjectDecision(false);

	//�}�E�X�J�[�\���̂ݍX�V���~�߁A�`�悵�Ȃ�
	CGameMouseCursor* mouse = CGameManager::GetInstance()->GetMouseCursor();
	mouse->SetStop(true);
	mouse->SetisDraw(false);

	//TODO: �����ɉ��o����	


	//TODO: ��U�S����C�Ɋ���悤�ɏ����Ă�A���o�ɍ��킹�Ċ����悤�ɕύX
	CBoardHolderGenerator* generator = CGameManager::GetInstance()->GetGenerator();

	std::list<CBoardHolder*> holderlist = generator->GetBoardHolderList();

	for (auto& itr : holderlist)
	{
		if (typeid(*itr) != typeid(CTrapHolderInfo))
		{
			CScore* pScore = GET_SCORE;
			int score = pScore->GetCurrentScore();
			++score;
			pScore->SetCurrentScore(score);
			itr->KnockDown();
		}
	}

	//�Q�[���I��
	CGameManager::GetInstance()->SetFinish(true);
}
