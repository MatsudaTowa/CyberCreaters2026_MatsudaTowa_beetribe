//=============================================
//
//�}�E�X�̋O��_�ʏ�[mouse_trail_normal.cpp]
//Author Matsuda Towa
//
//=============================================
#include "mouse_trail_normal.h"

namespace
{
	const int LIFE_FRAME = 20;								//�`��t���[����	
}

//=============================================
// �R���X�g���N�^
//=============================================
My::CMouseTrail_Normal::CMouseTrail_Normal(int nPriority)
{
}

//=============================================
// �f�X�g���N�^
//=============================================
My::CMouseTrail_Normal::~CMouseTrail_Normal()
{
}

//=============================================
// ������
//=============================================
HRESULT My::CMouseTrail_Normal::Init()
{
	CMouseTrail::Init();
	if (m_pCnt == nullptr)
	{
		m_pCnt = new CCount;
		m_pCnt->SetFrame(LIFE_FRAME);
	}
	return S_OK;
}

//=============================================
// �I��
//=============================================
void My::CMouseTrail_Normal::Uninit()
{
	if (m_pCnt != nullptr)
	{
		delete m_pCnt;
		m_pCnt = nullptr;
	}
	CMouseTrail::Uninit();
}

//=============================================
// �X�V
//=============================================
void My::CMouseTrail_Normal::Update()
{
	CMouseTrail::Update();
	if (m_pCnt != nullptr)
	{
		bool is_death = m_pCnt->CountUp();
		SetisDelete(is_death);
	}

	if (GetIsDelete())
	{
		D3DXVECTOR3 size = GetSize();
		size.x -= 0.5f;
		size.y -= 0.5f;

		//���݂̃T�C�Y�ɉ����ăA���t�@�l�ύX
		float current_alpha = (size.x * COLOR.a) / POLY_SIZE.x;
		D3DXCOLOR col = GetColor();
		col.a = current_alpha;

		//���
		SetColor(col);
		SetSize(size);

		if (size.x <= 0.0f && size.y <= 0.0f)
		{
			Uninit();
		}
	}
}

//=============================================
// �`��
//=============================================
void My::CMouseTrail_Normal::Draw()
{
	CMouseTrail::Draw();
}
