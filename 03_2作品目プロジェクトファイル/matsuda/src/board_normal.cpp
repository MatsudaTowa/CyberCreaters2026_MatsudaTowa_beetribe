//=============================================
//
//�ʏ�̔uboard_normal.cpp�v
// Author���c�i�v
//
//=============================================
#include "board_normal.h"

namespace
{
	const char* FILE_PATH = "data\\MODEL\\board\\Board_Left_000.x";
	const D3DXCOLOR COLOR = { 0.65f,0.35f,0.0f,1.0f };
}
//=============================================
// �R���X�g���N�^
//=============================================
My::CBoardNormal::CBoardNormal(int nPriority):CBoard(nPriority)
{
	CModel* pModel = CManager::GetInstance()->GetModel();

	//X�t�@�C���ǂݍ���
	BindXFile(pModel->GetModelInfo(pModel->Regist(FILE_PATH)).pBuffMat,
		pModel->GetModelInfo(pModel->Regist(FILE_PATH)).dwNumMat,
		pModel->GetModelInfo(pModel->Regist(FILE_PATH)).pMesh);
}

//=============================================
// �f�X�g���N�^
//=============================================
My::CBoardNormal::~CBoardNormal()
{
}

//=============================================
// �`��
//=============================================
void My::CBoardNormal::Draw()
{
	//�e�N���X�̕`��
	CBoard::Draw(COLOR);
}
