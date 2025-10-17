//=============================================
//
//�Q�[���}�E�X�̃J�[�\��[game_mouse_cursor.cpp]
//Author Matsuda Towa
//
//=============================================
#include "game_mouse_cursor.h"
#include "field.h"
#include "mouse_trail.h"
#include "board_holder.h"
#include "game_manager.h"

const std::string My::CGameMouseCursor::WRITE_TEX_PATH = "data\\TEXTURE\\mouse_cursor_write_anim.png"; //�t�@�C���p�X

//=============================================
//�R���X�g���N�^
//=============================================
My::CGameMouseCursor::CGameMouseCursor(int nPriority) :CMouseCursor(nPriority),
m_pMouse_Trail_Point(),					//�O�Ր����|�C���g������
m_max_tex_x(FLOAT_ZERO),				//�e�N�X�`�����W�ő�l
m_min_tex_x(FLOAT_ZERO),				//�e�N�X�`�����W�ŏ��l
m_pState(nullptr)						//�}�E�X�̏��
{
}

//=============================================
//�f�X�g���N�^
//=============================================
My::CGameMouseCursor::~CGameMouseCursor()
{
	for (auto& itr : m_pMouse_Trail_Point)
	{//���������������폜
		if (itr == nullptr) { continue; }

		itr->Uninit();
		itr = nullptr;
	}
	m_pMouse_Trail_Point.clear();
}

//=============================================
//������
//=============================================
HRESULT My::CGameMouseCursor::Init()
{
	//�e�N�X�`���擾
	CTexture* pTexture = GET_TEXTURE;

	BindTexture(pTexture->GetAddress(pTexture->Regist(&WRITE_TEX_PATH)));
	if (m_pState == nullptr)
	{
		m_pState = new CNormalCursol;
	}

	m_min_tex_x = 1.0f / (float)SPLIT * (SPLIT - 1);
	m_max_tex_x = 1.0f / (float)SPLIT * SPLIT;

	CGameManager::GetInstance()->SetMouseCursor(this);
	//�e�N���X�̏��������Ă�
	CMouseCursor::Init();

	return S_OK;
}

//=============================================
//�I��
//=============================================
void My::CGameMouseCursor::Uninit()
{
	if (m_pState != nullptr)
	{
		delete m_pState;
		m_pState = nullptr;
	}

	for (auto& itr : m_pMouse_Trail_Point)
	{//���������������폜
		if (itr == nullptr) { continue; }

		itr->Uninit();
		itr = nullptr;
	}
	m_pMouse_Trail_Point.clear();

	//�e�N���X�̏I�����Ă�
	CMouseCursor::Uninit();
}

//=============================================
//�X�V
//=============================================
void My::CGameMouseCursor::Update()
{
	if (m_pState != nullptr)
	{
		m_pState->Normal(this);
		m_pState->Write(this);
		m_pState->Written(this);
		m_pState->Pause(this);
	}

	//�e�N���X�̍X�V���Ă�
	CMouseCursor::Update();
	SetTexPos();
}

//=============================================
//�X�e�[�g�ύX
//=============================================
void My::CGameMouseCursor::ChangeState(CMouseCursorState* state)
{
	//���̃X�e�[�g�����������̃X�e�[�g�ɐ؂�ւ���
	if (m_pState != nullptr)
	{
		if (typeid(*m_pState) == typeid(*state))
		{
			return;
		}
		delete m_pState;
		m_pState = state;
	}
}

//=============================================
//�e�N�X�`�����W�ݒ�
//=============================================
void My::CGameMouseCursor::SetTexPos()
{

	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;

	LPDIRECT3DVERTEXBUFFER9 pBuff = GetVtxBuff();

	if (pBuff == nullptr)
	{
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &pBuff, NULL);
	}
	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	pBuff->Lock(0, 0, (void**)&pVtx, 0);
	pVtx[0].tex = D3DXVECTOR2(m_min_tex_x, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(m_max_tex_x, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(m_min_tex_x, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(m_max_tex_x, 1.0f);

	//�A�����b�N
	pBuff->Unlock();

	SetVtxBuff(pBuff);
}

//=============================================
//�`��
//=============================================
void My::CGameMouseCursor::Draw()
{
	//�e�N���X�̕`����Ă�
	CMouseCursor::Draw();
	DebugDraw();
}

//=============================================
//�O�Ղ̐��`��
//=============================================
void My::CGameMouseCursor::DebugDraw() 
{
#ifdef _DEBUG
	LPD3DXFONT pFont = CManager::GetInstance()->GetRenderer()->GetFont();
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	sprintf(&aStr[0], "\n\n\n\n\n\n\n\n�O�Ղ̐�%d"
		,m_pMouse_Trail_Point.size());
	//�e�L�X�g�̕`��
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 0, 0, 255));
#endif // _DEBUG
}