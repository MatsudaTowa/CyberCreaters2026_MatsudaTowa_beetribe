//=============================================
//
//�K�E�Z���ɏ�����[paper.cpp]
//Author Matsuda Towa
//
//=============================================
#include "paper.h"
#include "game_manager.h"

namespace
{
	D3DXVECTOR2 POLY_SIZE = { SCREEN_WIDTH*0.45f,SCREEN_HEIGHT*0.45f };						//�T�C�Y
	const std::string TEX_NAME = "data\\TEXTURE\\paper.png";		//�e�N�X�`��
}
//=============================================
// �R���X�g���N�^
//=============================================
My::CPaper::CPaper(int nPriority):CObject2D(nPriority)
{
}

//=============================================
// �f�X�g���N�^
//=============================================
My::CPaper::~CPaper()
{
}

//=============================================
// ������
//=============================================
HRESULT My::CPaper::Init()
{
	CGameManager::GetInstance()->SetPaper(this);
	CObject2D::Init();
	CTexture* pTexture = GET_TEXTURE;

	BindTexture(pTexture->GetAddress(pTexture->Regist(&TEX_NAME)));

	SetSize(POLY_SIZE);
	SetColor(COLOR_WHITE);
	SetVtx();
	return S_OK;
}

//=============================================
// �I��
//=============================================
void My::CPaper::Uninit()
{
	CObject2D::Uninit();
}

//=============================================
// �X�V
//=============================================
void My::CPaper::Update()
{
	CObject2D::Update();
	SetVtx();
}

//=============================================
// �`��
//=============================================
void My::CPaper::Draw()
{
	CObject2D::Draw();
}

//=============================================
// �`��
//=============================================
My::CPaper* My::CPaper::Create(D3DXVECTOR3 pos)
{
	CPaper* pPaper = new CPaper;
	if (pPaper == nullptr)
	{
		return nullptr;
	}

	pPaper->SetPos(pos);
	pPaper->Init();
	return pPaper;
}
