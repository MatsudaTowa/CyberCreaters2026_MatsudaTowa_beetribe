//=============================================
//
//�A�^�b�N�|�C���g[attack_point.cpp]
//Author Matsuda Towa
//
//=============================================
#include "hit_UI.h"
#include "hit_UI_break.h"
#include "hit_UI_stun.h"

namespace
{
	D3DXVECTOR2 POLY_SIZE = { 30.0f,30.0f };					//�|���S���T�C�Y
}

//=============================================
// �R���X�g���N�^
//=============================================
My::CHit_UI::CHit_UI(int nPriority):CObject2D(nPriority)
{
}

//=============================================
// �f�X�g���N�^
//=============================================
My::CHit_UI::~CHit_UI()
{
}

//=============================================
// ������
//=============================================
HRESULT My::CHit_UI::Init()
{
	//�e�N���X�̏��������Ă�
	CObject2D::Init();

	//�T�C�Y�ݒ�
	SetSize(POLY_SIZE);

	//�F�ݒ�
	SetColor(COLOR_WHITE);

	//���_�ݒ�
	SetVtx();

	return S_OK;
}

//=============================================
// �I��
//=============================================
void My::CHit_UI::Uninit()
{
	//�e�N���X�̏I�����Ă�
	CObject2D::Uninit();
}

//=============================================
// �X�V
//=============================================
void My::CHit_UI::Update()
{
	//�e�N���X�̍X�V���Ă�
	CObject2D::Update();

	//���_�ݒ�
	SetVtx();
}

//=============================================
// �`��
//=============================================
void My::CHit_UI::Draw()
{
	//�e�N���X�̕`����Ă�
	CObject2D::Draw();
}

//=============================================
// ����
//=============================================
My::CHit_UI* My::CHit_UI::Create(D3DXVECTOR3 pos, int type)
{
	CHit_UI* pHitUI = nullptr;

	switch (type)
	{
	case CHit_UI::BREAK:
		pHitUI = new CHit_UI_Break;
		break;
	case CHit_UI::STUN:
		pHitUI = new CHit_UI_Stun;
		break;
	default:
		assert(false && "���݂��Ȃ��^�C�v�ł�");
		break;
	}
	if (pHitUI == nullptr) { return nullptr; }

	pHitUI->SetPos({pos.x,pos.y,pos.z});

	pHitUI->SetType(OBJECT_TYPE_ATTACK_POINT);

	pHitUI->Init();

	return pHitUI;
}
