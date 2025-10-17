//=============================================
//
//�����l[board_holder.cpp]
//Author Matsuda Towa
//
//=============================================
#include "board_holder.h"
#include "game_manager.h"
#include "json.h"
#include "board_danger.h"
#include "board_hard.h"
#include "board_normal.h"
#include "splash_effect.h"
#include "ink_field.h"

namespace
{
	const int DELAY_DETH_FRAME = 5;
	const int NUM_PARTICLE = 10;
	const D3DXVECTOR3 SHADOW_SIZE = { 20.0f, 0.0, 20.0f };	//�e�̃T�C�Y
}

//=============================================
// �R���X�g���N�^
//=============================================
My::CBoardHolder::CBoardHolder(int nPriority):CCharacter(nPriority),
m_DelayDethCnt(nullptr),
m_pHitUI(nullptr)
{
	//�}�l�[�W���[�ɓo�^
	CGameManager::GetInstance()->GetGenerator()->Regist(this);
	if (m_DelayDethCnt == nullptr)
	{
		m_DelayDethCnt = new CCount;
		m_DelayDethCnt->SetFrame(DELAY_DETH_FRAME);
	}
	m_pBoard.clear();
}

//=============================================
// �f�X�g���N�^
//=============================================
My::CBoardHolder::~CBoardHolder()
{
	if (m_DelayDethCnt != nullptr)
	{
		delete m_DelayDethCnt;
		m_DelayDethCnt = nullptr;
	}
	//�}�l�[�W���[�ɓo�^
	CGameManager::GetInstance()->GetGenerator()->Delete(this,this->GetPos());
}

//=============================================
// ������
//=============================================
HRESULT My::CBoardHolder::Init()
{
	CCharacter::Init();

	//�������[�V�����ݒ�
	SetMotion(MOTION_NEUTRAL);

	//�e�̃T�C�Y�ݒ�
	SetShadowSize(SHADOW_SIZE);
	return S_OK;
}

//=============================================
// �I��
//=============================================
void My::CBoardHolder::Uninit()
{
	for (auto& itr : m_pBoard)
	{
		if (itr != nullptr)
		{
			itr->Unload();
			itr = nullptr;
		}
	}
	m_pBoard.clear();

	if (m_pHitUI != nullptr)
	{
		m_pHitUI->Uninit();
		m_pHitUI = nullptr;
	}

	//�e�N���X�̏I���������Ă�
	CCharacter::Uninit();
}

//=============================================
// �X�V
//=============================================
void My::CBoardHolder::Update()
{
	if (GetIsDelete())
	{
		if (m_DelayDethCnt->CountUp())
		{
			Uninit();
		}
		return;
	}
	CCharacter::Update();

	LookAtPlayer();

	Motion(); //���[�V��������

	if (m_pHitUI != nullptr)
	{
		D3DXVECTOR3 screen_pos = ConvertToScreenPos(GET_CAMERA(GET_CAMERA_IDX), GetPos()); //�X�N���[�����W�ɕϊ�
		m_pHitUI->SetPos(screen_pos);
	}

	if (GetPos().y < KILL_Y)
	{
		Uninit();
	}
}

//=============================================
// �`��
//=============================================
void My::CBoardHolder::Draw()
{
	//�e�N���X�̃��[�V�����p�̕`����Ă�
	MotionDraw();

	for (auto& itr : m_pBoard)
	{
		if (itr != nullptr)
		{
			itr->Draw();
		}
	}
}

//=============================================
// �|�����
//=============================================
void My::CBoardHolder::KnockDown()
{
	for (int i = INT_ZERO; i < NUM_PARTICLE; ++i)
	{
		CSplashEffect::Create({ GetPos().x,5.0f,GetPos().z });
	}

	CInkField::Create({ GetPos().x,1.0f,GetPos().z });

	Uninit();
}

//=============================================
// ����
//=============================================
My::CBoardHolder* My::CBoardHolder::Create(D3DXVECTOR3 pos, CBoardHolder* pBoardHolder)
{
	CBoardHolder* pBoardHorder = pBoardHolder;

	// null�Ȃ�null��Ԃ�
	if (pBoardHorder == nullptr) { return nullptr; }

	pBoardHorder->SetPos({ pos.x,0.2f,pos.z }); //pos�ݒ�

	pBoardHorder->Load_Parts("data\\MOTION\\motion_BoardHolder.bin"); //�p�[�c�ǂݍ���

	pBoardHorder->Init(); //����������

	pBoardHorder->SetType(OBJECT_TYPE_BOARD_HORDER); //�^�C�v�ݒ�

	return pBoardHorder;
}

//=============================================
// �q�b�gUI����
//=============================================
void My::CBoardHolder::CreateHitUI()
{
	if (GetIsDelete())
	{
		return;
	}
	if (m_pHitUI == nullptr)
	{
		D3DXVECTOR3 screen_pos = ConvertToScreenPos(GET_CAMERA(GET_CAMERA_IDX), GetPos()); //�X�N���[�����W�ɕϊ�

		m_pHitUI = CHit_UI::Create(screen_pos, 0); //TODO: �^�C�v�͈�U0�ő���A�N���X��ŉ������Ⴂ���Ȃ����̂�
		CGamePlayer* player = CGameManager::GetInstance()->GetPlayer();
		player->SetBoardHolder(this);
	}
}

//=============================================
// �v���C���[�����߂�
//=============================================
void My::CBoardHolder::LookAtPlayer()
{
	CGamePlayer* pPlayer = CGameManager::GetInstance()->GetPlayer();

	//�v���C���[�Ƃ̋����Z�o
	D3DXVECTOR3 Distance = pPlayer->GetPos() - GetPos();

	//�v���C���[�Ɍ�����p�x���Z�o
	float fAngle = atan2f(Distance.x, Distance.z);

	//�e�N���X����rot���擾
	D3DXVECTOR3 rot = GetRot();

	rot.y = fAngle + D3DX_PI;

	SetRot(rot);
}

//===========================================================================================================================================
//�����̏�񏈗�
//===========================================================================================================================================


//�̉�]��
const D3DXVECTOR3 My::CBoardHolderInfo::RIGHT_TURN = { 0.0f,0.0f,-1.0f };
const D3DXVECTOR3 My::CBoardHolderInfo::LEFT_TURN = { 0.0f,0.0f,-2.0f };

//=============================================
// �R���X�g���N�^
//=============================================
My::CBoardHolderInfo::CBoardHolderInfo(int nPriority) :CBoardHolder(nPriority)
{
	CJson::GetJson()->GetKarate(CJson::BOARDHOLDER_NUMBER)->PlusCreateobjCount();
}

//=============================================
// �f�X�g���N�^
//=============================================
My::CBoardHolderInfo::~CBoardHolderInfo()
{

}

//=============================================
// ������
//=============================================
HRESULT My::CBoardHolderInfo::Init()
{
	//�������Ɏ��s�����Ƃ�
	if (FAILED(CBoardHolder::Init()))
	{
		return E_FAIL; //���s��Ԃ�
	}
	CBoard* pBoard = nullptr;
	for (int i = 0; i < MAX; ++i)
	{
		switch (i)
		{
		case RIGHT:
			pBoard = CBoard::Create({ VEC3_RESET_ZERO },new CBoardNormal);
			pBoard->SetParent(GetModelParts(5));
			break;
		case LEFT:
			pBoard = CBoard::Create({OFFSET_X,FLOAT_ZERO,FLOAT_ZERO}, new CBoardNormal);
			pBoard->SetParent(GetModelParts(8));
			break;
		default:
			break;
		}
		pBoard->ConversionMtxWorld();
		PushBoard(pBoard);
	}
	return S_OK;
}

//=============================================
// �I������
//=============================================
void My::CBoardHolderInfo::Uninit()
{
	CGameManager::GetInstance()->GetGenerator()->SubHolder();

	if (CJson::GetJson() != nullptr)
	{
		//���̃J�E���g�̒����֐����Ă�
		CJson::GetJson()->GetKarate(CJson::BOARDHOLDER_NUMBER)->AdjsutobjCount();

		//NOTE �����ɏ�������������������͊e���̏ꏊ�ɃQ�[�W�𑝂₷������ǉ�����
		for (int nCount = 0; nCount < CJson::MAX_KARATEOBJ; nCount++)
		{
			CJson::GetJson()->GetKarate(nCount)->GetGage()++;
		}
	}

	CBoardHolder::Uninit();
}

//=============================================
// �X�V����
//=============================================
void My::CBoardHolderInfo::Update()
{
	CBoardHolder::Update();
}

//=============================================
// �`�揈��
//=============================================
void My::CBoardHolderInfo::Draw()
{
	CBoardHolder::Draw();
}

//=============================================
// ����ꂽ���̏���
//=============================================
void My::CBoardHolderInfo::BreakBoard()
{
	//�������Ă�悤�Ɍ����邽��
	GetBoard(CBoardHolder::RIGHT)->SetRot(RIGHT_TURN);
	GetBoard(CBoardHolder::LEFT)->SetPos(VEC3_RESET_ZERO);
	GetBoard(CBoardHolder::LEFT)->SetRot(LEFT_TURN);
}

//===========================================================================================================================================
//���̏�񏈗�
//===========================================================================================================================================

//=============================================
// �R���X�g���N�^
//=============================================
My::CKawaraInfo::CKawaraInfo(int nPriority) :CBoardHolder(nPriority)
{
	CJson::GetJson()->GetKarate(CJson::KAWARA_NUMBER)->PlusCreateobjCount();
}

//=============================================
// �f�X�g���N�^
//=============================================
My::CKawaraInfo::~CKawaraInfo()
{

}

//=============================================
// ������
//=============================================
HRESULT My::CKawaraInfo::Init()
{
	//�������Ɏ��s�����Ƃ�
	if (FAILED(CBoardHolder::Init()))
	{
		return E_FAIL; //���s��Ԃ�
	}
	return S_OK;
}

//=============================================
// �I������
//=============================================
void My::CKawaraInfo::Uninit()
{
	CGameManager::GetInstance()->GetGenerator()->SubKawara();

	if (CJson::GetJson() != nullptr)
	{
		//���̃J�E���g�̒����֐����Ă�
		CJson::GetJson()->GetKarate(CJson::KAWARA_NUMBER)->AdjsutobjCount();

		//NOTE �����ɏ�������������������͊e���̏ꏊ�ɃQ�[�W�𑝂₷������ǉ�����
		for (int nCount = 0; nCount < CJson::MAX_KARATEOBJ; nCount++)
		{
			CJson::GetJson()->GetKarate(nCount)->GetGage()++;
		}
	}

	CBoardHolder::Uninit();
}

//=============================================
// �X�V����
//=============================================
void My::CKawaraInfo::Update()
{
	CBoardHolder::Update();
}

//=============================================
// �`�揈��
//=============================================
void My::CKawaraInfo::Draw()
{
	CBoardHolder::Draw();
}

//===========================================================================================================================================
//㩎����̏�񏈗�
//===========================================================================================================================================

//=============================================
// �R���X�g���N�^
//=============================================
My::CTrapHolderInfo::CTrapHolderInfo(int nPriority) :CBoardHolder(nPriority)
{
	CJson::GetJson()->GetKarate(CJson::TRAPHOLDER_NUMBER)->PlusCreateobjCount();
}

//=============================================
// �f�X�g���N�^
//=============================================
My::CTrapHolderInfo::~CTrapHolderInfo()
{

}

//=============================================
// ������
//=============================================
HRESULT My::CTrapHolderInfo::Init()
{
	//�������Ɏ��s�����Ƃ�
	if (FAILED(CBoardHolder::Init()))
	{
		return E_FAIL; //���s��Ԃ�
	}
	CBoard* pBoard = nullptr;

	pBoard = CBoard::Create({ OFFSET_X,FLOAT_ZERO,FLOAT_ZERO }, new CBoardDanger);
	pBoard->SetRot({-HALF_PI,FLOAT_ZERO,FLOAT_ZERO});
	pBoard->SetParent(GetModelParts(5));
	pBoard->ConversionMtxWorld();
	PushBoard(pBoard);
	return S_OK;
}

//=============================================
// �I������
//=============================================
void My::CTrapHolderInfo::Uninit()
{
	CGameManager::GetInstance()->GetGenerator()->SubTrap();

	if (CJson::GetJson() != nullptr)
	{
		//���̃J�E���g�̒����֐����Ă�
		CJson::GetJson()->GetKarate(CJson::TRAPHOLDER_NUMBER)->AdjsutobjCount();

		//NOTE �����ɏ�������������������͊e���̏ꏊ�ɃQ�[�W�𑝂₷������ǉ�����
		for (int nCount = 0; nCount < CJson::MAX_KARATEOBJ; nCount++)
		{
			CJson::GetJson()->GetKarate(nCount)->GetGage()++;
		}
	}
	CBoardHolder::Uninit();
}

//=============================================
// �X�V����
//=============================================
void My::CTrapHolderInfo::Update()
{
	CBoardHolder::Update();
}

//=============================================
// �`�揈��
//=============================================
void My::CTrapHolderInfo::Draw()
{
	CBoardHolder::Draw();
}

//=============================================
// Hit_UI�̍쐬
//=============================================
void My::CTrapHolderInfo::CreateHitUI()
{
	CHit_UI* hit_UI = GetHitUI();
	if (hit_UI == nullptr)
	{
		D3DXVECTOR3 screen_pos = ConvertToScreenPos(GET_CAMERA(GET_CAMERA_IDX), GetPos()); //�X�N���[�����W�ɕϊ�

		hit_UI = CHit_UI::Create(screen_pos, 1);
		CGamePlayer* player = CGameManager::GetInstance()->GetPlayer();
		player->SetBoardHolder(this);
	}
	SetHitUI(hit_UI);
}