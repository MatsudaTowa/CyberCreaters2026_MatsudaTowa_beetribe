//=============================================
//
//�v���C���[[result_player.cpp]
//Author Matsuda Towa
//
//=============================================
#include "result_player.h"

namespace
{
	const float BELT_TARGET_POS_Y = 80.0f;
	const float BELT_TARGET_POS_Z = 30.0f;
}

//=============================================
// �R���X�g���N�^
//=============================================
My::CResultPlayer::CResultPlayer(int nPriority):CPlayer(nPriority)
{
}

//=============================================
// �f�X�g���N�^
//=============================================
My::CResultPlayer::~CResultPlayer()
{
}

//=============================================
// ������
//=============================================
HRESULT My::CResultPlayer::Init()
{
	//�e�N���X�̏��������s
	CPlayer::Init();
	return S_OK;
}

//=============================================
// �I��
//=============================================
void My::CResultPlayer::Uninit()
{
	//�e�N���X�̏I������
	CPlayer::Uninit();
}

//=============================================
// �X�V
//=============================================
void My::CResultPlayer::Update()
{
	Motion();

	CBelt* pBelt = GetBelt();
	D3DXVECTOR3 pos = pBelt->GetPos();
	if (pos.y < BELT_TARGET_POS_Y)
	{
		pos.y += 1.5f;

		D3DXVECTOR3 scale = pBelt->GetScale();
		scale += {0.1f, 0.1f, 0.1f};
		pBelt->SetScale(scale);
	}
	if (pos.z < BELT_TARGET_POS_Z)
	{
		pos.z += 0.5f;
	}

	pBelt->SetPos(pos);
}

//=============================================
// �`��
//=============================================
void My::CResultPlayer::Draw()
{
	//�e�N���X�̕`��
	CPlayer::Draw();
}
