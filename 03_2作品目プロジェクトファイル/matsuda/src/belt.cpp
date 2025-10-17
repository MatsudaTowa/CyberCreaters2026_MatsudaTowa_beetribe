//=============================================
//
//��[belt.h]
//Author Matsuda Towa
//
//=============================================
#include "belt.h"

namespace
{
	const char* MODEL_NAME = "data\\MODEL\\karateka\\Belt.x";	//x�t�@�C���̃t�@�C���p�X
	const D3DXVECTOR3 SCALE = { 1.0f, 1.0f, 1.0f };		//�X�P�[��
	const D3DXCOLOR COLOR = { 1.0f, 1.0f, 1.0f, 1.0f };		//�J���[
}

//=============================================
// �R���X�g���N�^
//=============================================
My::CBelt::CBelt(int nPriority):CObjectX(nPriority),
m_level(WHITE)
{
}

//=============================================
// �f�X�g���N�^
//=============================================
My::CBelt::~CBelt()
{
}

//=============================================
// ������
//=============================================
HRESULT My::CBelt::Init()
{
	//�`��ɕK�v�ȏ��ݒ�
	SetScale(SCALE);
	SetColor(COLOR);
	CObjectX::Init();
	return S_OK;
}

//=============================================
// �I��
//=============================================
void My::CBelt::Uninit()
{
	CObjectX::Uninit();
}

//=============================================
// �X�V
//=============================================
void My::CBelt::Update()
{
	ColorLevel();

	int level = (GET_SCORE->GetCurrentScore() * CBelt::MAX) / (CScore::MAX_SCORE + 1);
	m_level = ((CBelt::LEVEL)level);
	if (GET_SCORE->GetCurrentScore() > CScore::MAX_SCORE)
	{
		m_level = CBelt::BLACK;
	}
	CObjectX::Update();
}

//=============================================
// ���x���ɍ��킹�ĐF�ύX
//=============================================
void My::CBelt::ColorLevel()
{
	D3DXCOLOR col = GetCol();
	switch (m_level)
	{
	case My::CBelt::WHITE:
		col = COLOR_WHITE;
		break;
	case My::CBelt::YELLOW:
		col = COLOR_YELLOW;
		break;
	case My::CBelt::ORANGE:
		col = COLOR_ORANGE;
		break;
	case My::CBelt::BLUE:
		col = COLOR_BLUE;
		break;
	case My::CBelt::GREEN:
		col = COLOR_GREEN;
		break;
	case My::CBelt::PURPLE:
		col = COLOR_PURPLE;
		break;
	case My::CBelt::BLOWN:
		col = COLOR_BLOWN;
		break;
	case My::CBelt::BLACK:
		col = COLOR_BLACK;
		break;
	}
	SetColor(col);
}

//=============================================
// �`��
//=============================================
void My::CBelt::Draw()
{
	CObjectX::Draw();
}

//=============================================
// ����
//=============================================
My::CBelt* My::CBelt::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CBelt* pBelt = new CBelt;
	if (pBelt == nullptr) { return nullptr; }

	pBelt->SetPos(pos);	//�ʒu�ݒ�

	pBelt->SetRot(rot);	//�����ݒ�

	CModel* pModel = CManager::GetInstance()->GetModel();

	//X�t�@�C���ǂݍ���
	pBelt->BindXFile(pModel->GetModelInfo(pModel->Regist(MODEL_NAME)).pBuffMat,
		pModel->GetModelInfo(pModel->Regist(MODEL_NAME)).dwNumMat,
		pModel->GetModelInfo(pModel->Regist(MODEL_NAME)).pMesh);

	pBelt->Init();	//�������ݒ�

	return pBelt;
}
