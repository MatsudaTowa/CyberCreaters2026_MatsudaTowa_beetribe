//=============================================
//
//殴っちゃいけない板「board_danger.cpp」
// Author松田永久
//
//=============================================
#include "board_danger.h"

namespace
{
	const char* FILE_PATH = "data\\MODEL\\board\\trap_000.x";
}

//=============================================
// コンストラクタ
//=============================================
My::CBoardDanger::CBoardDanger(int nPriority):CBoard(nPriority)
{
	CModel* pModel = CManager::GetInstance()->GetModel();

	//Xファイル読み込み
	BindXFile(pModel->GetModelInfo(pModel->Regist(FILE_PATH)).pBuffMat,
		pModel->GetModelInfo(pModel->Regist(FILE_PATH)).dwNumMat,
		pModel->GetModelInfo(pModel->Regist(FILE_PATH)).pMesh);
}

//=============================================
// デストラクタ
//=============================================
My::CBoardDanger::~CBoardDanger()
{
}

//=============================================
// 描画
//=============================================
void My::CBoardDanger::Draw()
{
	//親クラスの描画
	CBoard::Draw();
}
