//=============================================
//
//リロードの表記[reload_icon.cpp]
//Author Matsuda Towa
//
//=============================================
#include "reload_txt.h"
#include "manager.h"

//テクスチャパス
const std::string CReloatTxt::TEXTURE_NAME = "data\\TEXTURE\\reloading.png";

//=============================================
// コンストラクタ
//=============================================
CReloatTxt::CReloatTxt(int nPriority):CObject2D(nPriority)
{
}

//=============================================
// デストラクタ
//=============================================
CReloatTxt::~CReloatTxt()
{
}

//=============================================
// 初期化
//=============================================
HRESULT CReloatTxt::Init()
{
	//初期化
	CObject2D::Init();

	//テクスチャ登録
	CTexture* pTexture = CManager::GetInstance()->GetTexture();
	BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME)));

	SetVtx(FLOAT_ONE);

	return S_OK;
}

//=============================================
// 終了
//=============================================
void CReloatTxt::Uninit()
{
	//終了
	CObject2D::Uninit();
}

//=============================================
// 更新
//=============================================
void CReloatTxt::Update()
{
	//更新
	CObject2D::Update();

	SetVtx(FLOAT_ONE);
}

//=============================================
// 描画
//=============================================
void CReloatTxt::Draw()
{
	//描画
	CObject2D::Draw();
}

//=============================================
// 生成
//=============================================
CReloatTxt* CReloatTxt::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXCOLOR col)
{
	CReloatTxt* pTxt = new CReloatTxt;

	if (pTxt == nullptr) { return nullptr; }

	pTxt->SetPos(pos);		//位置設定
	pTxt->SetSize(size);	//サイズ設定
	pTxt->SetColor(col);	//カラー設定

	pTxt->Init();			//初期化設定

	return pTxt;
}
