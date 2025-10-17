//=============================================
//
//����G�t�F�N�g[flash_effect.cpp]
//Author Matsuda Towa
//
//=============================================
#include "flash_effect.h"

namespace
{
	const D3DXVECTOR3 POLY_SIZE = { 10.0f,10.0f,0.0f };
	const int ANIM_FRAME = 3;
	const int SPLIT_X = 8;
	const int SPLIT_Y = 1;
	std::string TEX_NAME = "data\\TEXTURE\\flash_anim.png";	//�t�@�C���p�X
}

//=============================================
// �R���X�g���N�^
//=============================================
My::CFlashEffect::CFlashEffect(int nPriority):CBillboard_Anim(nPriority)
{
}

//=============================================
// �f�X�g���N�^
//=============================================
My::CFlashEffect::~CFlashEffect()
{
}

//=============================================
// ������
//=============================================
HRESULT My::CFlashEffect::Init()
{
	CBillboard_Anim::Init();

	//�e�N�X�`���ݒ�
	CTexture* pTexture = GET_TEXTURE;
	BindTexture(pTexture->GetAddress(pTexture->Regist(&TEX_NAME)));

	SetSize(POLY_SIZE);
	SetColor(COLOR_WHITE);

	//�e�N�X�`���ړ��ʎ擾
	D3DXVECTOR2 tex_move = GetTexMove();
	tex_move.x = 1.0f / (float)SPLIT_X;
	tex_move.y = 1.0f / (float)SPLIT_Y;
	//�e�N�X�`���ړ��ʑ��
	SetTexMove(tex_move);

	//�e�N�X�`�����W�擾
	D3DXVECTOR2 tex_pos = GetTexPos();
	tex_pos.x = 0.0f;
	tex_pos.y = 0.0f;
	//�e�N�X�`�����W���
	SetTexPos(tex_pos);
	SetAnimFrame(ANIM_FRAME);

	SetVtx({ 0.0f,1.0f,0.0f });
	AnimationTex(tex_pos, tex_move);
	return S_OK;
}

//=============================================
// �I��
//=============================================
void My::CFlashEffect::Uninit()
{
	CBillboard_Anim::Uninit();
}

//=============================================
// �X�V
//=============================================
void My::CFlashEffect::Update()
{
	CBillboard_Anim::Update();
	//�e�N�X�`�����擾
	D3DXVECTOR2 tex_pos = GetTexPos();
	D3DXVECTOR2 tex_move = GetTexMove();
	//�A�j���[�V������̃e�N�X�`�����W�擾
	tex_pos = GetTexPos();
	//�A�j���[�V�������J��Ԃ�
	if (tex_pos.x >= FLOAT_ONE)
	{
		Uninit();
		return;
	}

	SetVtx({ 0.0f,1.0f,0.0f });

	//���_���W
	AnimationTex(tex_pos, tex_move);
}

//=============================================
// �`��
//=============================================
void My::CFlashEffect::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;
	//���C�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	//z�o�b�t�@�ɏ������܂Ȃ�
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//���Z��������
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);

	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	CBillboard_Anim::Draw();

	//�ʏ�̍����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);

	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//z�o�b�t�@�ɏ������܂Ȃ�
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	//���C�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//=============================================
// ����
//=============================================
My::CFlashEffect* My::CFlashEffect::Create(D3DXVECTOR3 pos)
{
	CFlashEffect* pEffect = new CFlashEffect;

	//���g���Ȃ��Ȃ����̑O��return
	if (pEffect == nullptr) { return nullptr; }

	pEffect->SetPos(pos);	//�ʒu�ݒ�

	pEffect->Init();		//������

	return pEffect;
}
