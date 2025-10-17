//=============================================
//
//ポーズのUI_コンティニュー[pause_select_continue.cpp]
//Author Matsuda Towa
//
//=============================================
#include "pause_select_continue.h"
#include "manager.h"

//テクスチャパス
const std::string CPauseSelectContinue::TEXTURE_NAME = "data\\TEXTURE\\Continue.png";

//=============================================
//コンストラクタ
//=============================================
CPauseSelectContinue::CPauseSelectContinue(int nPriority):CPauseSelect(nPriority)
{
}

//=============================================
// デストラクタ
//=============================================
CPauseSelectContinue::~CPauseSelectContinue()
{
}

//=============================================
// 初期化
//=============================================
HRESULT CPauseSelectContinue::Init()
{
	//テクスチャ情報取得
	CTexture* pTexture = CManager::GetInstance()->GetTexture();
	//テクスチャ登録
	BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME)));
	CPauseSelect::Init();
	return S_OK;
}

//=============================================
// 終了
//=============================================
void CPauseSelectContinue::Uninit()
{
	CPauseSelect::Uninit();
}

//=============================================
// 更新
//=============================================
void CPauseSelectContinue::Update()
{
	CPauseSelect::Update();
}

//=============================================
// 描画
//=============================================
void CPauseSelectContinue::Draw()
{
	CPauseSelect::Draw();
}

