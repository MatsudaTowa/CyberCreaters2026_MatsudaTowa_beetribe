//=============================================
//
//通常の板「board_normal.cpp」
// Author松田永久
//
//=============================================
#include "board_normal.h"

namespace
{
	const char* FILE_PATH = "data\\MODEL\\board\\Board_Left_000.x";
	const D3DXCOLOR COLOR = { 0.65f,0.35f,0.0f,1.0f };
}
//=============================================
// コンストラクタ
//=============================================
My::CBoardNormal::CBoardNormal(int nPriority):CBoard(nPriority)
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
My::CBoardNormal::~CBoardNormal()
{
}

//=============================================
// 描画
//=============================================
void My::CBoardNormal::Draw()
{
	//親クラスの描画
	CBoard::Draw(COLOR);
}
