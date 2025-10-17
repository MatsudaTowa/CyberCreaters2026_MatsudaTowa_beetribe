//=============================================
//
//�^�C�}�[�����utimer.cpp�v
// Author���c�i�v
//
//=============================================
#include "timer.h"
#include "game_manager.h"

namespace
{
	const int LIMIT_TIME = 100;										//��������
	const int NUM_DIGIT = 3;										//����
	const float DIGIT_SHIFT = 50.0f;								//�����Ƃɍ��W�����炷
	const D3DXVECTOR3 POS = D3DXVECTOR3(1000.0f, 50.0f, 0.0f);		//�ʒu
	const D3DXVECTOR2 NUMBER_SIZE = D3DXVECTOR2(30.0f, 50.0f);		//�T�C�Y
}

//=============================================
// �R���X�g���N�^
//=============================================
My::CTimer::CTimer() :
m_pCnt(nullptr),
m_nCurrentTime(INT_ZERO),
m_pos(VEC3_RESET_ZERO)
{
	//�����N���A
	m_pNumber.clear();
	//�^�C�}�[
	m_nCurrentTime = LIMIT_TIME;
	//�����ʒu���
	m_pos = POS;
}

//=============================================
// �f�X�g���N�^
//=============================================
My::CTimer::~CTimer()
{
}

//=============================================
// ������
//=============================================
HRESULT My::CTimer::Init()
{
	CGameManager::GetInstance()->SetTimer(this);

	if (m_pCnt == nullptr)
	{
		m_pCnt = new CCount;
		m_pCnt->SetFrame(ONE_SECOND);
	}

	for (int nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		CNumber_2D* pNumber = CNumber_2D::Create(m_pos, NUMBER_SIZE, CNumber_2D::TEX_000);
		m_pNumber.push_back(pNumber);
	
		//���W�����炷
		m_pos.x -= DIGIT_SHIFT;
	}

	return S_OK;
}

//=============================================
// �I��
//=============================================
void My::CTimer::Uninit()
{
	if (m_pCnt != nullptr)
	{
		delete m_pCnt;
		m_pCnt = nullptr;
	}
	m_pNumber.clear();
}

//=============================================
// �X�V
//=============================================
void My::CTimer::Update()
{
	if (m_nCurrentTime <= INT_ZERO)
	{
		m_nCurrentTime = INT_ZERO;
		GET_FADE->SetFade(CScene::MODE_RESULT);
	}
	SetTimer();

}

//=============================================
// �^�C�}�[����
//=============================================
void My::CTimer::DecreaseTime()
{
	bool is_decrease_time = m_pCnt->CountUp();

	if (is_decrease_time)
	{
		m_nCurrentTime--;
		m_pCnt->SetCnt(INT_ZERO);
	}
}

//=============================================
// �^�C�}�[�ݒ�
//=============================================
void My::CTimer::SetTimer()
{
	//�����擾
	int num_digit = m_pNumber.size();

	std::vector<int> pos_texU;

	//���݌v�Z���Ă錅
	int nDigit = 1;
	int nCnt;
	for (nCnt = 0; nCnt < num_digit; nCnt++)
	{
		pos_texU.push_back(m_nCurrentTime / nDigit % 10);

		//����i�߂�
		nDigit *= 10;
	}

	EraseDigit(pos_texU, num_digit);

	for (nCnt = num_digit - 1; nCnt >= 0; nCnt--)
	{
		//�e�N�X�`���̍��W�v�Z�p�ϐ�
		float fMinTexU, fMaxTexU;

		fMinTexU = pos_texU[nCnt] * 0.1f;
		fMaxTexU = fMinTexU + 0.1f;

		m_pNumber[nCnt]->SetNumber(fMinTexU, fMaxTexU,COLOR_BLACK);
	}

	pos_texU.clear();
}

//=============================================
// ���폜
//=============================================
void My::CTimer::EraseDigit(std::vector<int> pos_texU, int& num_digit)
{
	if (pos_texU[num_digit - 1] == INT_ZERO)
	{//�������炷
		if (num_digit - 1 == 0)
		{
			return;
		}
		CNumber_2D* pNumber = m_pNumber[num_digit - 1];
		pNumber->Uninit();
		pNumber = nullptr;

		m_pNumber.erase(m_pNumber.end() - 1);

		--num_digit;

		if (num_digit <= 0)
		{
			return;
		}
	}
}
