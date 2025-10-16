//=============================================
//
//設定のUI「setting_UI.cpp」
// Author松田永久
//
//=============================================
#include "setting_UI.h"
#include "manager.h"

//ゲージの位置
const D3DXVECTOR3 CSetting_UI::GAUGE_POS = { 450.0f, 300.0f, 0.0f };
//ゲージのサイズ
const D3DXVECTOR2 CSetting_UI::GAUGE_SIZE = { 400.0f,60.0f };

//番号の位置
const D3DXVECTOR3 CSetting_UI::NUM_POS = { 935.0f, 270.0f, 0.0f };
//番号のサイズ
const D3DXVECTOR2 CSetting_UI::NUM_SIZE = { 17.0f, 25.0f };

//小数点の位置
const D3DXVECTOR3 CSetting_UI::DECIMAL_POINT_POS = { 882.0f, 285.0f, 0.0f };
//小数点のサイズ
const D3DXVECTOR2 CSetting_UI::DECIMAL_POINT__SIZE = { 2.5f, 2.5f };

//文字の位置
const D3DXVECTOR3 CSetting_UI::TXT_POS = { 380.0f, 275.0f, 0.0f };
//文字のサイズ
const D3DXVECTOR2 CSetting_UI::TXT_SIZE = { 85.0f, 45.0f };
//=============================================
//コンストラクタ
//=============================================
CSetting_UI::CSetting_UI() :
m_pNumber(),			//数字のポインタ
m_pDecimalPoint(),		//小数点のポインタ
m_NumPos(),				//数字の位置
m_pGauge(),				//ゲージのポインタ
m_pTxtUI(),				//テキストポインタ
m_pMask(nullptr)
{
}

//=============================================
//デストラクタ
//=============================================
CSetting_UI::~CSetting_UI()
{
}

//=============================================
//初期化
//=============================================
HRESULT CSetting_UI::Init()
{
	m_NumPos = NUM_POS;

	m_pMask = CMask::Create(new CPauseMask);

	if (m_pTxtUI == nullptr)
	{
		m_pTxtUI = CSensTxtUI::Create(TXT_POS, TXT_SIZE);
	}

	//体力ゲージ生成
	if (m_pGauge == nullptr)
	{
		m_pGauge = CGauge_2D::Create(GAUGE_POS, GAUGE_SIZE, CGauge_2D::GAUGE2D_TYPE::GAUGE_TYPE_SENS, COLOR_WHITE);
	}

	//数字生成
	for (int nCnt = INT_ZERO; nCnt < NUM_DIGIT; nCnt++)
	{
		if (m_pNumber[nCnt] == nullptr)
		{
			m_pNumber[nCnt] = CNumber_2D::Create(m_NumPos, NUM_SIZE, new CSensNumber);
			//座標をずらす
			m_NumPos.x -= DIGIT_SHIFT;
		}
	}
	if (m_pDecimalPoint == nullptr)
	{
		m_pDecimalPoint = CDecimalPoint::Create(DECIMAL_POINT_POS,DECIMAL_POINT__SIZE,COLOR_WHITE);
	}
	return S_OK;
}

//=============================================
//終了
//=============================================
void CSetting_UI::Uninit()
{
	for (int nCnt = INT_ZERO; nCnt < NUM_DIGIT; nCnt++)
	{
		if (m_pNumber[nCnt] != nullptr)
		{
			m_pNumber[nCnt]->Uninit();
			m_pNumber[nCnt] = nullptr;
		}
	}

	if (m_pDecimalPoint != nullptr)
	{
		m_pDecimalPoint->Uninit();
		m_pDecimalPoint = nullptr;
	}

	if (m_pGauge != nullptr)
	{
		m_pGauge->Uninit();
		m_pGauge = nullptr;
	}

	if (m_pTxtUI != nullptr)
	{
		m_pTxtUI->Uninit();
		m_pTxtUI = nullptr;
	}

	if (m_pMask != nullptr)
	{
		m_pMask->Uninit();
		m_pMask = nullptr;
	}
	delete this;
}

//=============================================
//更新
//=============================================
void CSetting_UI::Update()
{
	if (m_pGauge != nullptr)
	{
		m_pGauge->Update();
	}
}

//=============================================
//感度UI
//=============================================
void CSetting_UI::SetSens_UI(float sens)
{
	SetNumber(sens);

	float gaugeWidth = (sens * GAUGE_SIZE.x) / FLOAT_ONE;

	m_pGauge->SetGauge({ gaugeWidth , m_pGauge->GetSize().y });
}

//=============================================
//感度の数字
//=============================================
void CSetting_UI::SetNumber(float sens)
{
	//テクスチャ座標設定
	int a_PosTexU[NUM_DIGIT];

	sens *= 100;	//0.01～1.00を整数にするために

	//現在計算してる桁
	int nDigit = 1;
	int nCnt;
	for (nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		//今の時間から計算
		a_PosTexU[nCnt] = (int)sens / nDigit % 10;

		//桁を進める
		nDigit *= 10;
	}

	for (nCnt = NUM_DIGIT - 1; nCnt >= 0; nCnt--)
	{
		//テクスチャの座標計算用変数
		float fMinTexU, fMaxTexU;

		fMinTexU = a_PosTexU[nCnt] * 0.1f;
		fMaxTexU = fMinTexU + 0.1f;

		m_pNumber[nCnt]->SetNumber(fMinTexU, fMaxTexU, COLOR_WHITE);
	}
}
