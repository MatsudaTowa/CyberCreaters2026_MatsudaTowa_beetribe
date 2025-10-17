//=============================================
//
//�q�b�gUI(����)[hit_UI_break.cpp]
//Author Matsuda Towa
//
//=============================================
#include "hit_UI_break.h"

namespace
{
	std::string TEX_NAME = "data\\TEXTURE\\break.png";	//�t�@�C���p�X
}

//=============================================
//�R���X�g���N�^
//=============================================
My::CHit_UI_Break::CHit_UI_Break(int nPriority) :CHit_UI(nPriority)
{
}

//=============================================
//�f�X�g���N�^
//=============================================
My::CHit_UI_Break::~CHit_UI_Break()
{
}

//=============================================
//������
//=============================================
HRESULT My::CHit_UI_Break::Init()
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
void My::CHit_UI_Break::Uninit()
{
	//�e�N���X�̏I��
	CHit_UI::Uninit();
}

//=============================================
//�X�V
//=============================================
void My::CHit_UI_Break::Update()
{
	//�e�N���X�̍X�V
	CHit_UI::Update();
}

//=============================================
//�`��
//=============================================
void My::CHit_UI_Break::Draw()
{
	//�e�N���X�̕`��
	CHit_UI::Draw();
}