//=============================================
//
//ポーズのUI_リトライ[pause_select_retry.cpp]
//Author Matsuda Towa
//
//=============================================
#include "pause_select_retry.h"
#include "manager.h"

//テクスチャパス
const std::string CPauseSelectRetry::TEXTURE_NAME = "data\\TEXTURE\\Retry.png";
//=============================================
//コンストラクタ
//=============================================
CPauseSelectRetry::CPauseSelectRetry(int nPriority):CPauseSelect(nPriority)
{
}

//=============================================
// デストラクタ
//=============================================
CPauseSelectRetry::~CPauseSelectRetry()
{
}

//=============================================
// 初期化
//=============================================
HRESULT CPauseSelectRetry::Init()
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
void CPauseSelectRetry::Uninit()
{
	CPauseSelect::Uninit();
}

//=============================================
// 更新
//=============================================
void CPauseSelectRetry::Update()
{
	CPauseSelect::Update();
}

//=============================================
// 描画
//=============================================
void CPauseSelectRetry::Draw()
{
	CPauseSelect::Draw();
}
