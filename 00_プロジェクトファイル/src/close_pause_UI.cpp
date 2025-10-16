//=============================================
//
//ポーズをとじるUI[close_pause_UI.cpp]
//Author Matsuda Towa
//
//=============================================
#include "close_pause_UI.h"
#include "manager.h"

//テクスチャパス
const std::string CClosePauseUI::TEXTURE_NAME = "data\\TEXTURE\\cloase_pause_UI.png";

//=============================================
// コンストラクタ
//=============================================
CClosePauseUI::CClosePauseUI(int nPriority):CObject2D(nPriority)
{
}

//=============================================
// デストラクタ
//=============================================
CClosePauseUI::~CClosePauseUI()
{
}

//=============================================
// 初期化
//=============================================
HRESULT CClosePauseUI::Init()
{
	//テクスチャ情報取得
	CTexture* pTexture = CManager::GetInstance()->GetTexture();
	SetColor(COLOR_WHITE);
	//テクスチャ登録
	BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME)));
	CObject2D::Init();
	SetVtx(1.0f);
	return S_OK;
}

//=============================================
// 終了
//=============================================
void CClosePauseUI::Uninit()
{
	CObject2D::Uninit();
}

//=============================================
// 更新
//=============================================
void CClosePauseUI::Update()
{
	CObject2D::Update();
	SetVtx(1.0f);
}

//=============================================
// 描画
//=============================================
void CClosePauseUI::Draw()
{
	CObject2D::Draw();
}

//=============================================
// 生成
//=============================================
CClosePauseUI* CClosePauseUI::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	CClosePauseUI* pPauseUI = new CClosePauseUI;
	if (pPauseUI == nullptr)
	{
		return nullptr;
	}
	pPauseUI->SetPos(pos);
	pPauseUI->SetSize(size);
	pPauseUI->Init();
	return pPauseUI;

}
