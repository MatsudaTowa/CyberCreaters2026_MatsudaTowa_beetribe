//=============================================
//
//�}�E�X�̃J�[�\��[mouse_cursor.cpp]
//Author Matsuda Towa
//
//=============================================
#include "mouse_cursor.h"
#include "field.h"
#include "mouse_trail.h"
#include "board_holder.h"

const std::string My::CMouseCursor::TEX_PATH = "data\\TEXTURE\\mouse_cursor_normal.png"; //�t�@�C���p�X

namespace
{
	const D3DXVECTOR2 POLY_SIZE = { 40.5f,40.5f };					//�|���S���T�C�Y
}

//=============================================
//�R���X�g���N�^
//=============================================
My::CMouseCursor::CMouseCursor(int nPriority):CObject2D(nPriority),
m_oldpos(VEC3_RESET_ZERO)				//�ߋ��̈ʒu
{
}

//=============================================
//�f�X�g���N�^
//=============================================
My::CMouseCursor::~CMouseCursor()
{
}

//=============================================
//������
//=============================================
HRESULT My::CMouseCursor::Init()
{
	//�e�N���X�̏��������Ă�
	CObject2D::Init();

	//�T�C�Y�ݒ�
	SetSize(POLY_SIZE);

	//�F�ݒ�
	SetColor(COLOR_WHITE);

	//���_�ݒ�
	SetVtx();

	return S_OK;
}

//=============================================
//�I��
//=============================================
void My::CMouseCursor::Uninit()
{
	//�e�N���X�̏I�����Ă�
	CObject2D::Uninit();
}

//=============================================
//�X�V
//=============================================
void My::CMouseCursor::Update()
{
	//�e�N���X�̍X�V���Ă�
	CObject2D::Update();

	POINT pMouseMove;

	GetCursorPos(&pMouseMove);

	m_oldpos = GetPos();

	D3DXVECTOR3 pos = { (float)pMouseMove.x ,(float)pMouseMove.y, 0.0f};

	SetPos(pos);

	//���_�ݒ�
	SetVtx();
}

//=============================================
//�`��
//=============================================
void My::CMouseCursor::Draw()
{
	//�e�N���X�̕`����Ă�
	CObject2D::Draw();
}


//=============================================
//����
//=============================================
My::CMouseCursor* My::CMouseCursor::Create(CMouseCursor* mouse_cursor)
{
	CTexture* pTexture = GET_TEXTURE;
	CMouseCursor* pMouseCursor = mouse_cursor;

	//null�Ȃ�null��Ԃ�
	if (pMouseCursor == nullptr) { return nullptr; }

	pMouseCursor->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEX_PATH)));

	pMouseCursor->SetType(OBJECT_MOUSE); //�^�C�v�ݒ�

	pMouseCursor->Init();

	return pMouseCursor;
}
