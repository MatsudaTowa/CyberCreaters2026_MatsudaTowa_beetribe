//=============================================
//
//�n�̓_[ink_dot.cpp]
//Author Matsuda Towa
//
//=============================================
#include "ink_dot.h"

namespace
{
	const float MAX_SIZE = 1.0f;
	const float MIN_SIZE = 3.0f;
	const std::string TEX_NAME =
	{
		"data\\TEXTURE\\ink_dot.png",
	};
}
//=============================================
// �R���X�g���N�^
//=============================================
My::CInkDot::CInkDot(int nPriority):CObject3D(nPriority)
{
}

//=============================================
// �f�X�g���N�^
//=============================================
My::CInkDot::~CInkDot()
{
}

//=============================================
// ������
//=============================================
HRESULT My::CInkDot::Init()
{
	SetColor(COLOR_WHITE);
	CObject3D::Init();

	//�e�N�X�`���ݒ�
	CTexture* pTexture = GET_TEXTURE;
	BindTexture(pTexture->GetAddress(pTexture->Regist(&TEX_NAME)));

	float size = FLOAT_ZERO;

	size = Rundom(MIN_SIZE, MAX_SIZE);

	SetSize({ size,0.0f,size });

	//���_�ݒ�
	SetVtx(D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	return S_OK;
}

//=============================================
// �I��
//=============================================
void My::CInkDot::Uninit()
{
	CObject3D::Uninit();
}

//=============================================
// �X�V
//=============================================
void My::CInkDot::Update()
{
	CObject3D::Update();

	//���_�ݒ�
	SetVtx(D3DXVECTOR3(0.0f, 1.0f, 0.0f));
}

//=============================================
// �`��
//=============================================
void My::CInkDot::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;
	//z�o�b�t�@�ɏ������܂Ȃ�
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	CObject3D::Draw();
	//z�o�b�t�@�ɏ�������
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

//=============================================
// ����
//=============================================
My::CInkDot* My::CInkDot::Create(D3DXVECTOR3 pos)
{
	CInkDot* pInkDot = new CInkDot;
	if (pInkDot == nullptr)
	{
		return nullptr;
	}
	pInkDot->SetPos(pos);
	pInkDot->Init();

	return pInkDot;
}
