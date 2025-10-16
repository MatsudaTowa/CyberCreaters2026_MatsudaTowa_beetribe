//=============================================
//
//ポーズのUI_リトライ[pause_select_setting.cpp]
//Author Matsuda Towa
//
//=============================================
#include "pause_select_setting.h"
#include "manager.h"

//テクスチャパス
const std::string CPauseSelectSetting::TEXTURE_NAME = "data\\TEXTURE\\Setting.png";
//=============================================
// コンストラクタ
//=============================================
CPauseSelectSetting::CPauseSelectSetting(int nPriority):CPauseSelect(nPriority)
{
}

//=============================================
// デストラクタ
//=============================================
CPauseSelectSetting::~CPauseSelectSetting()
{
}

//=============================================
// 初期化
//=============================================
HRESULT CPauseSelectSetting::Init()
{
	//テクスチャ情報取得
	CTexture* pTexture = CManager::GetInstance()->GetTexture();
	//テクスチャ登録
	BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME)));
	CPauseSelect::Init();
	return S_OK;
}
//=============================================
void CPauseSelectSetting::Uninit()
{
	CPauseSelect::Uninit();
}

//=============================================
// 更新
//=============================================
void CPauseSelectSetting::Update()
{
	CPauseSelect::Update();
}

//=============================================
// 描画
//=============================================
void CPauseSelectSetting::Draw()
{
	CPauseSelect::Draw();
}
