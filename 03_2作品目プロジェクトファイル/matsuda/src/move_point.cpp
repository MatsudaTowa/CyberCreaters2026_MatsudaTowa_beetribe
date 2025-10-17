//=============================================
//
//�ړ�����|�C���g[move_point.cpp]
//Author Matsuda Towa
//
//=============================================
#include "move_point.h"

//=============================================
// ������
//=============================================
HRESULT My::CMovePoint::Init()
{
	//�e�N���X�̏�����
	CBillboard::Init();

	//���_���W
	SetVtx({0.0f,1.0f,0.0f});
	return S_OK;
}

//=============================================
// �I��
//=============================================
void My::CMovePoint::Uninit()
{
	//�e�N���X�̏I��
	CBillboard::Uninit();
}

//=============================================
// �X�V
//=============================================
void My::CMovePoint::Update()
{
	//�e�N���X�̍X�V
	CBillboard::Update();

	//���_���W
	SetVtx({ 0.0f,1.0f,0.0f });
}

//=============================================
// �`��
//=============================================
void My::CMovePoint::Draw()
{
	//�e�N���X�̕`��
	CBillboard::Draw();
}

//=============================================
// ����
//=============================================
My::CMovePoint* My::CMovePoint::Create(D3DXVECTOR3 pos, CMovePoint* point)
{
	CMovePoint* move_point = point;

	if (move_point == nullptr) { return nullptr; }

	move_point->SetPos(pos);

	move_point->SetType(OBJECT_TYPE_MOVE_POINT);

	move_point->Init();

	return move_point;
}
