//=============================================
//
//帯[belt.h]
//Author Matsuda Towa
//
//=============================================
#include "belt.h"

namespace
{
	const char* MODEL_NAME = "data\\MODEL\\karateka\\Belt.x";	//xファイルのファイルパス
	const D3DXVECTOR3 SCALE = { 1.0f, 1.0f, 1.0f };		//スケール
	const D3DXCOLOR COLOR = { 1.0f, 1.0f, 1.0f, 1.0f };		//カラー
}

//=============================================
// コンストラクタ
//=============================================
My::CBelt::CBelt(int nPriority):CObjectX(nPriority),
m_level(WHITE)
{
}

//=============================================
// デストラクタ
//=============================================
My::CBelt::~CBelt()
{
}

//=============================================
// 初期化
//=============================================
HRESULT My::CBelt::Init()
{
	//描画に必要な情報設定
	SetScale(SCALE);
	SetColor(COLOR);
	CObjectX::Init();
	return S_OK;
}

//=============================================
// 終了
//=============================================
void My::CBelt::Uninit()
{
	CObjectX::Uninit();
}

//=============================================
// 更新
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
// レベルに合わせて色変更
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
// 描画
//=============================================
void My::CBelt::Draw()
{
	CObjectX::Draw();
}

//=============================================
// 生成
//=============================================
My::CBelt* My::CBelt::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CBelt* pBelt = new CBelt;
	if (pBelt == nullptr) { return nullptr; }

	pBelt->SetPos(pos);	//位置設定

	pBelt->SetRot(rot);	//方向設定

	CModel* pModel = CManager::GetInstance()->GetModel();

	//Xファイル読み込み
	pBelt->BindXFile(pModel->GetModelInfo(pModel->Regist(MODEL_NAME)).pBuffMat,
		pModel->GetModelInfo(pModel->Regist(MODEL_NAME)).dwNumMat,
		pModel->GetModelInfo(pModel->Regist(MODEL_NAME)).pMesh);

	pBelt->Init();	//初期化設定

	return pBelt;
}
