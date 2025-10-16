//=============================================
//
//ゲージ管理[gauge.cpp]
//Author Matsuda Towa
//
//=============================================
#include "gauge.h"
#include "manager.h"

//テクスチャパス
const std::string CGauge_2D::TEXTURE_NAME = "data\\TEXTURE\\gauge.png";

//=============================================
//コンストラクタ
//=============================================
CGauge_2D::CGauge_2D(int nPriority) :CObject2D(nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CGauge_2D::~CGauge_2D()
{
}

//=============================================
//初期化
//=============================================
HRESULT CGauge_2D::Init()
{
	//親クラスの初期化を呼ぶ
	CObject2D::Init();

	//テクスチャ座標設定
	SetTexPos(VEC2_RESET_ONE);

	//頂点設定
	SetGaugeVtx(FLOAT_ONE);

	return S_OK;
}

//=============================================
//終了
//=============================================
void CGauge_2D::Uninit()
{
	//親クラスの終了呼ぶ
	CObject2D::Uninit();
}

//=============================================
//更新
//=============================================
void CGauge_2D::Update()
{
	//親クラスの更新呼ぶ
	CObject2D::Update();

	//頂点設定
	SetGaugeVtx(FLOAT_ONE);
}

//=============================================
//描画
//=============================================
void CGauge_2D::Draw()
{
	//親クラスの描画呼ぶ
	CObject2D::Draw();
}


//=============================================
//ゲージ設定
//=============================================
void CGauge_2D::SetGauge(D3DXVECTOR2 size)
{
	SetSize(size);
}

//=============================================
//生成
//=============================================
CGauge_2D* CGauge_2D::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, GAUGE2D_TYPE type, D3DXCOLOR col)
{
	CGauge_2D* pGauge = nullptr;

	switch (type)
	{
	case GAUGE_TYPE_LIFE:
		pGauge = new CGauge_Life;
		break;
	case GAUGE_TYPE_SENS:
		pGauge = new CGauge_Sens;
		break;
	default:
		assert(false);
		break;
	}

	// nullならnullを返す
	if (pGauge == nullptr) { return nullptr; }

	pGauge->SetPos(pos); //pos設定

	pGauge->SetSize(size); //size設定

	pGauge->SetColor(col); //色設定

	pGauge->m_type = type; //ゲージのタイプ設定

	pGauge->SetType(OBJECT_TYPE_GAUGE); //タイプ設定

	pGauge->Init();

	return pGauge;
}

//=============================================
//コンストラクタ
//=============================================
CGauge_Life::CGauge_Life(int nPriority) :CGauge_2D(nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CGauge_Life::~CGauge_Life()
{
}

//=============================================
//初期化
//=============================================
HRESULT CGauge_Life::Init()
{
	//親クラスの初期化
	CGauge_2D::Init();

	return S_OK;
}

//=============================================
//終了
//=============================================
void CGauge_Life::Uninit()
{
	//親クラスの終了
	CGauge_2D::Uninit();
}

//=============================================
//更新
//=============================================
void CGauge_Life::Update()
{
	//親クラスの更新
	CGauge_2D::Update();
}

//=============================================
//描画
//=============================================
void CGauge_Life::Draw()
{
	//親クラスの描画
	CGauge_2D::Draw();
}

//=============================================
//コンストラクタ
//=============================================
CGauge_Sens::CGauge_Sens(int nPriority):CGauge_2D(nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CGauge_Sens::~CGauge_Sens()
{
}

//=============================================
//初期化
//=============================================
HRESULT CGauge_Sens::Init()
{
	//親クラスの初期化
	CGauge_2D::Init();
	return S_OK;
}

//=============================================
//終了
//=============================================
void CGauge_Sens::Uninit()
{
	//親クラスの終了
	CGauge_2D::Uninit();
}

//=============================================
//更新
//=============================================
void CGauge_Sens::Update()
{
	//親クラスの更新
	CGauge_2D::Update();
}

//=============================================
//描画
//=============================================
void CGauge_Sens::Draw()
{
	//親クラスの描画
	CGauge_2D::Draw();
}
