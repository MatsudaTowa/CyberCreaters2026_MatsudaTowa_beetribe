//=============================================
//
//�n�̔�юU��[ink_field.cpp]
//Author Matsuda Towa
//
//=============================================
#include "ink_field.h"
#include "ink_dot.h"

namespace
{
	const int NUM_TEX = 3;
	const int NUM_DOT = 20;
	const float DOT_COLECTION = 1.25f;
	const float MAX_SIZE = 30.0f;
	const float MIN_SIZE = 15.0f;
	const std::string TEX_NAME[NUM_TEX] =
	{
		"data\\TEXTURE\\ink_field_000.png",
		"data\\TEXTURE\\ink_field_001.png",
		"data\\TEXTURE\\ink_field_002.png"
	};
}

//=============================================
// �R���X�g���N�^
//=============================================
My::CInkField::CInkField(int nPriority):CObject3D(nPriority)
{
}

//=============================================
// �f�X�g���N�^
//=============================================
My::CInkField::~CInkField()
{
}

//=============================================
// ������
//=============================================
HRESULT My::CInkField::Init()
{
	SetColor({COLOR_WHITE.r,COLOR_WHITE.g,COLOR_WHITE.b,0.0f });
	CObject3D::Init();

	int tex_type = Rundom(0, NUM_TEX);
	//�e�N�X�`���ݒ�
	CTexture* pTexture = GET_TEXTURE;
	BindTexture(pTexture->GetAddress(pTexture->Regist(&TEX_NAME[tex_type])));

	float size = FLOAT_ZERO;

	size = Rundom(MIN_SIZE, MAX_SIZE);

	SetSize({ size,0.0f,size });

	//�T�C�Y��菭���ł��߂ɒ���
	float dot_correction = size * DOT_COLECTION;

	for (int i = INT_ZERO; i < NUM_DOT; ++i)
	{
		//���ˏ�Ƀ����_��
		float fVertex = CICRLE_RAND;
		D3DXVECTOR3 create_pos = { GetPos().x + dot_correction * sinf(fVertex),1.0f,GetPos().z + dot_correction * cosf(fVertex) };

		CInkDot::Create(create_pos);
	}

	//���_�ݒ�
	SetVtx(D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	return S_OK;
}

//=============================================
// �I��
//=============================================
void My::CInkField::Uninit()
{
	CObject3D::Uninit();
}

//=============================================
// �X�V
//=============================================
void My::CInkField::Update()
{
	CObject3D::Update();

	D3DXCOLOR col = GetColor();
	if (col.a < 1.0f)
	{
		col.a += 0.1f;
	}
	SetColor(col);

	//���_�ݒ�
	SetVtx(D3DXVECTOR3(0.0f, 1.0f, 0.0f));
}

//=============================================
// �`��
//=============================================
void My::CInkField::Draw()
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
My::CInkField* My::CInkField::Create(D3DXVECTOR3 pos)
{
	CInkField* pInkField = new CInkField;
	if (pInkField == nullptr)
	{
		return nullptr;
	}
	pInkField->SetPos(pos);
	pInkField->Init();

	return pInkField;
}
