//=============================================
//
//ポーズのUI_タイトルに[pause_select_quit.cpp]
//Author Matsuda Towa
//
//=============================================
#include "pause_select_quit.h"
#include "manager.h"

//テクスチャパス
const std::string CPauseSelectQuit::TEXTURE_NAME = "data\\TEXTURE\\Quit.png";
//=============================================
//コンストラクタ
//=============================================
CPauseSelectQuit::CPauseSelectQuit(int nPriority):CPauseSelect(nPriority)
{
}

//=============================================
// デストラクタ
//=============================================
CPauseSelectQuit::~CPauseSelectQuit()
{
}

//=============================================
// 初期化
//=============================================
HRESULT CPauseSelectQuit::Init()
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
void CPauseSelectQuit::Uninit()
{
	CPauseSelect::Uninit();
}

//=============================================
// 更新
//=============================================
void CPauseSelectQuit::Update()
{
	CPauseSelect::Update();
}

//=============================================
// 描画
//=============================================
void CPauseSelectQuit::Draw()
{
	CPauseSelect::Draw();
}
