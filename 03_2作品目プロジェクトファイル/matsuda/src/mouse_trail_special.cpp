//=============================================
//
//�}�E�X�̋O��_�K�E�Z[mouse_trail_special.cpp]
//Author Matsuda Towa
//
//=============================================
#include "mouse_trail_special.h"

//=============================================
// �R���X�g���N�^
//=============================================
My::CMouseTrail_Special::CMouseTrail_Special(int nPriority):CMouseTrail(nPriority)
{
}

//=============================================
// �f�X�g���N�^
//=============================================
My::CMouseTrail_Special::~CMouseTrail_Special()
{
}

//=============================================
// ������
//=============================================
HRESULT My::CMouseTrail_Special::Init()
{
	CMouseTrail::Init();
	return S_OK;
}

//=============================================
// �I��
//=============================================
void My::CMouseTrail_Special::Uninit()
{
	CMouseTrail::Uninit();
}

//=============================================
// �X�V
//=============================================
void My::CMouseTrail_Special::Update()
{
	CMouseTrail::Update();
}

//=============================================
// �`��
//=============================================
void My::CMouseTrail_Special::Draw()
{
	CMouseTrail::Draw();
}
