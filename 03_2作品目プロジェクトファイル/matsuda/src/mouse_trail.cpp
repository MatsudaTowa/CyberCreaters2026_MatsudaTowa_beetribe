//=============================================
//
//�}�E�X�̋O��[mouse_trail.cpp]
//Author Matsuda Towa
//
//=============================================
#include "mouse_trail.h"
#include "game_manager.h"
namespace 
{
	const std::string TEX_NAME = "data\\TEXTURE\\fude.png";	//�t�@�C���p�X
}

const D3DXVECTOR3 My::CMouseTrail::POLY_SIZE = { 12.5f,12.5f,0.0f };		//�|���S���T�C�Y
const D3DXCOLOR My::CMouseTrail::COLOR = { 0.0f,0.0f,0.0f,0.5f };		//�J���[

//=============================================
//�R���X�g���N�^
//============================================
My::CMouseTrail::CMouseTrail(int nPriority):CBillboard(nPriority)
{
}

//=============================================
//�f�X�g���N�^
//============================================
My::CMouseTrail::~CMouseTrail()
{
}

//=============================================
//������
//============================================
HRESULT My::CMouseTrail::Init()
{
	//�e�N���X�̏�����
	CBillboard::Init();

	SetSize(POLY_SIZE);

	SetColor(COLOR);

	//���_���W
	SetVtx(D3DXVECTOR3(0.0f, 1.0f, 0.0f));

	return S_OK;
}

//=============================================
//�I��
//============================================
void My::CMouseTrail::Uninit()
{
	//�e�N���X�̏I��
	CBillboard::Uninit();
}

//=============================================
//�X�V
//============================================
void My::CMouseTrail::Update()
{
	//�e�N���X�̍X�V
	CBillboard::Update();

	//���_���W
	SetVtx(D3DXVECTOR3(0.0f, 1.0f, 0.0f));
}

//=============================================
//�`��
//============================================
void My::CMouseTrail::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;

	//z�̔�r���@�ύX
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	//z�o�b�t�@�ɏ������܂Ȃ�
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//���C�g��L���ɖ߂�
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//�e�N���X�̕`��
	CBillboard::Draw();

	//z�̔�r���@�ύX
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	//z�o�b�t�@�ɏ������܂Ȃ�
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//���C�g��L���ɖ߂�
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//=============================================
//����
//============================================
My::CMouseTrail* My::CMouseTrail::Create(D3DXVECTOR3 pos, CMouseTrail* trail)
{
	CTexture* pTexture = GET_TEXTURE;

	CMouseTrail* pTrail = trail;
	
	if (pTrail == nullptr) { return nullptr; }

	pTrail->SetPos(pos);

	pTrail->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEX_NAME)));

	pTrail->Init();

	return pTrail;
}
