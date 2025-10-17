//=============================================
//
//�v���C���[���ړ�����|�C���g[player_move_point.cpp]
//Author Matsuda Towa
//
//=============================================
#include "player_move_point.h"

namespace
{
	const D3DXVECTOR3 POLY_SYZE = { 5.0f,5.0f,0.0f };				//�|���S���T�C�Y
}

//=============================================
// ������
//=============================================
HRESULT My::CPlayerMovePoint::Init()
{

	SetSize(POLY_SYZE);

	SetColor(COLOR_BLUE);

	//�e�N���X�̏�����
	CMovePoint::Init();

	return S_OK;
}

//=============================================
// �I��
//=============================================
void My::CPlayerMovePoint::Uninit()
{	
	//�e�N���X�̏I��
	CMovePoint::Uninit();
}

//=============================================
// �X�V
//=============================================
void My::CPlayerMovePoint::Update()
{
	//�e�N���X�̍X�V
	CMovePoint::Update();
}

//=============================================
// �`��
//=============================================
void My::CPlayerMovePoint::Draw()
{
	//�e�N���X�̕`��
	CMovePoint::Draw();
}