//=============================================
//
//�R���{�\�������ucombo.cpp�v
// Author���c�i�v
//
//=============================================
#include "combo.h"

namespace
{
	const int NUM_DIGIT = 1;										//����
	const float DIGIT_SHIFT = 40.0f;								//�����Ƃɍ��W�����炷
	const float SUB_ALPHA = 0.01f;									//�A���t�@�l�����l
	const D3DXVECTOR2 NUMBER_SIZE = D3DXVECTOR2(50.0f, 70.0f);		//�����̃T�C�Y
	const D3DXVECTOR2 UI_SIZE = D3DXVECTOR2(160.0f, 50.0f);			//UI�̃T�C�Y
	const float CORRECTION_NUM_POS_X = 80.0f;						//�����̈ʒu����
	const float CORRECTION_NUM_POS_Y = 30.0f;						//�����̈ʒu����
	const std::string TEXTURE_NAME = "data\\TEXTURE\\combo.png";	//�e�N�X�`���̖��O
}

//=============================================
// �R���X�g���N�^
//=============================================
My::CCombo::CCombo(int nPriority):CObject2D(nPriority),
	m_combo(INT_ZERO),				//�R���{
	m_num_pos(VEC3_RESET_ZERO),		//�����̈ʒu
	m_pCnt(nullptr),				//�J�E���g�̃|�C���^
	m_pNumber()						//�����̃|�C���^(�i�[�p)
{
	m_pNumber.clear();
}

//=============================================
// �f�X�g���N�^
//=============================================
My::CCombo::~CCombo()
{
}

//=============================================
// ������
//=============================================
HRESULT My::CCombo::Init()
{
	CObject2D::Init();

	CTexture* pTexture = GET_TEXTURE;
	BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME))); //�e�N�X�`���ݒ�

	SetSize(UI_SIZE);
	SetColor(COLOR_WHITE);

	m_num_pos = GetPos();

	m_num_pos.x -= CORRECTION_NUM_POS_X;
	m_num_pos.y -= CORRECTION_NUM_POS_Y;

	if (m_pCnt == nullptr)
	{
		m_pCnt = new CCount;
		m_pCnt->SetFrame(ONE_SECOND);
	}

	for (int nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		CNumber_2D* pNumber = CNumber_2D::Create(m_num_pos, NUMBER_SIZE, CNumber_2D::TEX_001);
		m_pNumber.push_back(pNumber);

		//���W�����炷
		m_num_pos.x -= DIGIT_SHIFT;
	}
	SetVtx();

	return S_OK;
}

//=============================================
// �I��
//=============================================
void My::CCombo::Uninit()
{
	if (m_pCnt != nullptr)
	{
		delete m_pCnt;
		m_pCnt = nullptr;
	}
	for (auto& itr : m_pNumber)
	{
		if (itr == nullptr)
		{
			continue;
		}
		itr->Uninit();
		itr = nullptr;
	}
	m_pNumber.clear();
	CObject2D::Uninit();
}

//=============================================
// �X�V
//=============================================
void My::CCombo::Update()
{
	if (!GetIsDelete())
	{
		SetCombo();
	}
	SubAlpha();

	CObject2D::Update();
	SetVtx();
}


//=============================================
// �A���t�@�l����
//=============================================
void My::CCombo::SubAlpha()
{
	if (GetIsDelete())
	{
		D3DXCOLOR col = GetColor();

		col.a -= SUB_ALPHA;

		SetColor(col);

		for (auto& itr : m_pNumber)
		{
			if (itr == nullptr)
			{
				continue;
			}
			itr->SetColor(col);
			itr->NumberVtx();
		}
	}
}

//=============================================
// �`��
//=============================================
void My::CCombo::Draw()
{
	CObject2D::Draw();
}

//=============================================
// ����
//=============================================
My::CCombo* My::CCombo::Create(D3DXVECTOR3 pos)
{
	CCombo* pCombo = new CCombo;
	if (pCombo == nullptr) { return nullptr; }
	pCombo->SetPos(pos);
	pCombo->Init();
	return pCombo;
}

//=============================================
// �R���{���̕\���ݒ�
//=============================================
void My::CCombo::SetCombo()
{
	//�����擾
	int num_digit = m_pNumber.size();

	std::vector<int> pos_texU;

	//���݌v�Z���Ă錅
	int nDigit = 1;
	int nCnt;
	for (nCnt = 0; nCnt < num_digit; nCnt++)
	{
		pos_texU.push_back(m_combo / nDigit % 10);

		//����i�߂�
		nDigit *= 10;
	}

	AddDigit(pos_texU, num_digit);

	for (nCnt = num_digit - 1; nCnt >= 0; nCnt--)
	{
		//�e�N�X�`���̍��W�v�Z�p�ϐ�
		float fMinTexU, fMaxTexU;

		fMinTexU = pos_texU[nCnt] * 0.1f;
		fMaxTexU = fMinTexU + 0.1f;

		m_pNumber[nCnt]->SetNumber(fMinTexU, fMaxTexU, COLOR_WHITE);
	}

	pos_texU.clear();
}

//=============================================
// ���ǉ�
//=============================================
void My::CCombo::AddDigit(std::vector<int>& pos_texU, int& num_digit)
{
	if (pos_texU[num_digit - 1] == 0)
	{//�������炷
		CNumber_2D* pNumber;

		//���W�����炷
		m_num_pos.x -= DIGIT_SHIFT;
		pNumber = CNumber_2D::Create(m_num_pos, NUMBER_SIZE,1);
		m_pNumber.push_back(pNumber);

		++num_digit;

		pos_texU.clear();
		int nDigit = 1;
		for (int nCnt = 0; nCnt < num_digit; nCnt++)
		{
			pos_texU.push_back(m_combo / nDigit % 10);

			//����i�߂�
			nDigit *= 10;
		}
	}
}
