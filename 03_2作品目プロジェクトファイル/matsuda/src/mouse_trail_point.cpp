//=============================================
//
//�}�E�X�̋O�Ղ�ݒu����|�C���g[mouse_trail_point.cpp]
//Author Matsuda Towa
//
//=============================================
#include "mouse_trail_point.h"
#include "mouse_trail_normal.h"
#include "field.h"
#include "board_holder.h"
namespace
{
	const D3DXVECTOR3 POLY_SYZE = { 5.0f,5.0f,0.0f };				//�|���S���T�C�Y
	const int TRAIL_CREATE_NUM = 10;									//���ŉ��񐶐����邩
	const D3DXVECTOR3 TRAIL_CREATE_MIN_POS = { -5.0f,0.0f,-5.0f };	//��������ŏ��ʒu
	const D3DXVECTOR3 TRAIL_CREATE_MAX_POS = { 5.0f,0.0f,5.0f };	//��������ő�ʒu
}

//=============================================
//������
//============================================
HRESULT My::CMouseTrailPoint::Init()
{
	//�e�N���X�̏�����
	CBillboard::Init();

	SetSize(POLY_SYZE);

	SetColor(COLOR_WHITE);

	//���_���W
	SetVtx(D3DXVECTOR3(0.0f, 1.0f, 0.0f));

	return S_OK;
}

//=============================================
//�I��
//============================================
void My::CMouseTrailPoint::Uninit()
{
	//�e�N���X�̏I��
	CBillboard::Uninit();
}

//=============================================
//�X�V
//============================================
void My::CMouseTrailPoint::Update()
{
	//�e�N���X�̍X�V
	CBillboard::Update();

	//���_���W
	SetVtx(D3DXVECTOR3(0.0f, 1.0f, 0.0f));
}

//=============================================
//�`��
//============================================
void My::CMouseTrailPoint::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;

	//���C�g��L���ɖ߂�
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//�e�N���X�̕`��
	CBillboard::Draw();

	//���C�g��L���ɖ߂�
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//=============================================
//����
//============================================
My::CMouseTrailPoint* My::CMouseTrailPoint::Create(D3DXVECTOR3 pos)
{
	CMouseTrailPoint* pTrailPoint = new CMouseTrailPoint;

	if (pTrailPoint == nullptr) { return nullptr; }

	pTrailPoint->SetPos(pos);

	pTrailPoint->SetType(OBJECT_MOUSE_DEBUG);

	pTrailPoint->Init();

	return pTrailPoint;
}

//=============================================
//�O�Ղ̐���
//=============================================
void My::CMouseTrailPoint::CreateTrail()
{
	D3DXVECTOR3 pos = GetPos();

	for (int i = 0; i < TRAIL_CREATE_NUM; ++i)
	{
		float x = 0.0f;
		float z = 0.0f;

		x = Rundom(TRAIL_CREATE_MIN_POS.x, TRAIL_CREATE_MAX_POS.x);
		z = Rundom(TRAIL_CREATE_MIN_POS.z, TRAIL_CREATE_MAX_POS.z);

		CMouseTrail::Create({ pos.x + x,pos.y + 0.5f,pos.z + z },new CMouseTrail_Normal);
	}
}
