//=============================================
//
//�Q�[���v���C���[[game_player.cpp]
//Author Matsuda Towa
//
//=============================================
#include "game_player.h"
#include "game_manager.h"
#include "sound_bgm.h"
#include "sound_se.h"

//=============================================
// �R���X�g���N�^
//=============================================
My::CGamePlayer::CGamePlayer(int nPriority):CPlayer(nPriority),
m_pState(nullptr),		//�X�e�[�g������
m_pCombo(nullptr),
m_pBoardHolder(),		//�����l�ۑ��ϐ�������
m_pMovePoint()			//�ړ��|�C���g������
{
	//�J���i���ʁA�Đ��j
	CSoundBGM_000::Open();
	CSoundBGM_000::volume(CSoundBGM_000::MAX_VOLUME);
	CSoundBGM_000::Play();

	CSoundSE_000::Open();
}

//=============================================
// �f�X�g���N�^
//=============================================
My::CGamePlayer::~CGamePlayer()
{
	//�e�t�@�C���̒�~�ƏI��
	CSoundBGM_000::Stop();
	CSoundBGM_000::Close();

	CSoundSE_000::Stop();
	CSoundSE_000::Close();
}

//=============================================
// ������
//=============================================
HRESULT My::CGamePlayer::Init()
{
	if (m_pState == nullptr)
	{
		m_pState = new CNeutralState;
	}

	//�e�N���X�̏��������s
	CPlayer::Init();

	//�Q�[���̃}�l�[�W���Ɏ�������
	CGameManager::GetInstance()->SetPlayer(this);
	return S_OK;
}

//=============================================
// �I��
//=============================================
void My::CGamePlayer::Uninit()
{
	m_pBoardHolder.clear();

	if (m_pState != nullptr)
	{
		delete m_pState;
		m_pState = nullptr;
	}

	if (m_pCombo != nullptr)
	{
		m_pCombo->Uninit();
		m_pCombo = nullptr;
	}

	ClearMovePoint();

	//�e�N���X�̏I������
	CPlayer::Uninit();
}

//=============================================
// �Q�[�����������؂ꂽ���̏���
//=============================================
void  My::CGamePlayer::Play_Sound_BGM_000()
{
	char uReturnLength[10];                                            //���݂̏�Ԃ̎擾�p�ϐ�
	char A[] = "stopped";                                              //��Ԑݒ�i�~�܂��Ă���j
	mciSendString(TEXT("status BGM0 mode"), uReturnLength, 100, NULL);  //���݂̏�Ԃ𑪒�

	//��Ԃ����v������
	if (strcmp(uReturnLength, A) == 0)
	{
		CSoundBGM_000::Stop(); //�~�߂�
		CSoundBGM_000::Zero(); //�[������Đ�
	}
}

//=============================================
// �X�V
//=============================================
void My::CGamePlayer::Update()
{
	Play_Sound_BGM_000();

	if (m_pState != nullptr)
	{
		m_pState->Attack(this);
		m_pState->MovetoFree(this);
		m_pState->Neutral(this);
	}

	//�e�N���X�̍X�V
	CPlayer::Update();

	CBelt* pBelt = GetBelt();
	if (pBelt != nullptr)
	{//�т���������
	 //�т𓮂���
		CModel_Parts* parts = GetModelParts(0);
		float fAngle = atan2f(sinf(GetRot().y), cosf(GetRot().y));
		pBelt->SetPos({ parts->GetMtxWorld()._41 + GetMove().x,parts->GetMtxWorld()._42 - CORRECTION_VALUE_BELT,parts->GetMtxWorld()._43 + GetMove().z });
		pBelt->SetRot({ FLOAT_ZERO,fAngle,FLOAT_ZERO });
		pBelt->SetisDraw(GetisDraw());
	}

	if (m_pCombo != nullptr)
	{
		if (!m_pCombo->GetIsDelete())
		{
			return;
		}
		if (m_pCombo->GetColor().a > FLOAT_ZERO)
		{
			return;
		}
	
		m_pCombo->Uninit();
		m_pCombo = nullptr;
	}
}

//=============================================
// �`��
//=============================================
void My::CGamePlayer::Draw()
{
	//�e�N���X�̕`��
	CPlayer::Draw();
}

//=============================================
// �X�e�[�g�ύX
//=============================================
void My::CGamePlayer::ChangeState(CGamePlayerState* state)
{
	//���̃X�e�[�g�����������̃X�e�[�g�ɐ؂�ւ���
	if (m_pState != nullptr)
	{
		delete m_pState;
		m_pState = state;
	}
}

//=============================================
// ����
//=============================================
void My::CGamePlayer::Input()
{
}

//=============================================
//�v���C���[�̃f�o�b�O�\��
//=============================================
void My::CGamePlayer::Debug()
{
#ifdef _DEBUG
	LPD3DXFONT pFont = CManager::GetInstance()->GetRenderer()->GetFont();
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	sprintf(&aStr[0], "\n\n[player]\npos:%.1f,%.1f,%.1f\nrot:%.1f,%.1f,%.1f\nmove:%.1f,%.1f,%.1f\n�������邩%d\n�X�R�A%d"
		, GetPos().x, GetPos().y, GetPos().z, GetRot().x, GetRot().y, GetRot().z, GetMove().x, GetMove().y, GetMove().z,m_pBoardHolder.size(),GET_SCORE->GetCurrentScore());
	//�e�L�X�g�̕`��
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 0, 0, 255));
#endif // _DEBUG
}