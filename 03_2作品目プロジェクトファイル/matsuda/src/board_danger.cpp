//=============================================
//
//�������Ⴂ���Ȃ��uboard_danger.cpp�v
// Author���c�i�v
//
//=============================================
#include "board_danger.h"

namespace
{
	const char* FILE_PATH = "data\\MODEL\\board\\trap_000.x";
}

//=============================================
// �R���X�g���N�^
//=============================================
My::CBoardDanger::CBoardDanger(int nPriority):CBoard(nPriority)
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
My::CBoardDanger::~CBoardDanger()
{
}

//=============================================
// �`��
//=============================================
void My::CBoardDanger::Draw()
{
	//�e�N���X�̕`��
	CBoard::Draw();
}
