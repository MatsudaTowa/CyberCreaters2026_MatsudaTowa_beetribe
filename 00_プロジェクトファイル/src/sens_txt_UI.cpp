//=============================================
//
//感度の文字UI[sens_txt_UI.cpp]
//Author Matsuda Towa
//
//=============================================
#include "sens_txt_UI.h"
#include "manager.h"

//テクスチャパス
const std::string CSensTxtUI::TEXTURE_NAME = "data\\TEXTURE\\sens_UI.png";
//=============================================
// コンストラクタ
//=============================================
CSensTxtUI::CSensTxtUI(int nPriority) :CObject2D(nPriority)
{
}

//=============================================
// デストラクタ
//=============================================
CSensTxtUI::~CSensTxtUI()
{
}

//=============================================
// 初期化
//=============================================
HRESULT CSensTxtUI::Init()
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
void CSensTxtUI::Uninit()
{
	CObject2D::Uninit();
}

//=============================================
// 更新
//=============================================
void CSensTxtUI::Update()
{
	CObject2D::Update();
	SetVtx(1.0f);
}

//=============================================
// 描画
//=============================================
void CSensTxtUI::Draw()
{
	CObject2D::Draw();
}

//=============================================
// 生成
//=============================================
CSensTxtUI* CSensTxtUI::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	CSensTxtUI* pTxt = new CSensTxtUI;
	if (pTxt == nullptr)
	{
		return nullptr;
	}
	pTxt->SetPos(pos);
	pTxt->SetSize(size);
	pTxt->Init();
	return pTxt;

}

