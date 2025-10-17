//=============================================
//
//�A�^�b�N�|�C���g��[attack_point_down.cpp]
//Author Matsuda Towa
//
//=============================================
#include "hit_UI_stun.h"

namespace
{
	std::string TEX_NAME = "data\\TEXTURE\\stun.png";	//�t�@�C���p�X
}

//=============================================
//�R���X�g���N�^
//=============================================
My::CHit_UI_Stun::CHit_UI_Stun(int nPriority) :CHit_UI(nPriority)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
My::CHit_UI_Stun::~CHit_UI_Stun()
{
}

//=============================================
//������
//=============================================
HRESULT My::CHit_UI_Stun::Init()
{
	//�e�N���X�̏�����
	CHit_UI::Init();

	CTexture* pTexture = GET_TEXTURE;

	BindTexture(pTexture->GetAddress(pTexture->Regist(&TEX_NAME)));

	return S_OK;
}

//=============================================
//�I��
//=============================================
void My::CHit_UI_Stun::Uninit()
{
	//�e�N���X�̏I��
	CHit_UI::Uninit();
}

//=============================================
//�X�V
//=============================================
void My::CHit_UI_Stun::Update()
{
	//�e�N���X�̍X�V
	CHit_UI::Update();
}

//=============================================
//�`��
//=============================================
void My::CHit_UI_Stun::Draw()
{
	//�e�N���X�̕`��
	CHit_UI::Draw();
}