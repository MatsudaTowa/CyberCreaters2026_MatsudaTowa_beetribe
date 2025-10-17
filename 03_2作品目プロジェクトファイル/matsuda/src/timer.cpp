//=============================================
//
//タイマー処理「timer.cpp」
// Author松田永久
//
//=============================================
#include "timer.h"
#include "game_manager.h"

namespace
{
	const int LIMIT_TIME = 100;										//制限時間
	const int NUM_DIGIT = 3;										//桁数
	const float DIGIT_SHIFT = 50.0f;								//桁ごとに座標をずらす
	const D3DXVECTOR3 POS = D3DXVECTOR3(1000.0f, 50.0f, 0.0f);		//位置
	const D3DXVECTOR2 NUMBER_SIZE = D3DXVECTOR2(30.0f, 50.0f);		//サイズ
}

//=============================================
// コンストラクタ
//=============================================
My::CTimer::CTimer() :
m_pCnt(nullptr),
m_nCurrentTime(INT_ZERO),
m_pos(VEC3_RESET_ZERO)
{
	//数字クリア
	m_pNumber.clear();
	//タイマー
	m_nCurrentTime = LIMIT_TIME;
	//初期位置代入
	m_pos = POS;
}

//=============================================
// デストラクタ
//=============================================
My::CTimer::~CTimer()
{
}

//=============================================
// 初期化
//=============================================
HRESULT My::CTimer::Init()
{
	CGameManager::GetInstance()->SetTimer(this);

	if (m_pCnt == nullptr)
	{
		m_pCnt = new CCount;
		m_pCnt->SetFrame(ONE_SECOND);
	}

	for (int nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		CNumber_2D* pNumber = CNumber_2D::Create(m_pos, NUMBER_SIZE, CNumber_2D::TEX_000);
		m_pNumber.push_back(pNumber);
	
		//座標をずらす
		m_pos.x -= DIGIT_SHIFT;
	}

	return S_OK;
}

//=============================================
// 終了
//=============================================
void My::CTimer::Uninit()
{
	if (m_pCnt != nullptr)
	{
		delete m_pCnt;
		m_pCnt = nullptr;
	}
	m_pNumber.clear();
}

//=============================================
// 更新
//=============================================
void My::CTimer::Update()
{
	if (m_nCurrentTime <= INT_ZERO)
	{
		m_nCurrentTime = INT_ZERO;
		GET_FADE->SetFade(CScene::MODE_RESULT);
	}
	SetTimer();

}

//=============================================
// タイマー減少
//=============================================
void My::CTimer::DecreaseTime()
{
	bool is_decrease_time = m_pCnt->CountUp();

	if (is_decrease_time)
	{
		m_nCurrentTime--;
		m_pCnt->SetCnt(INT_ZERO);
	}
}

//=============================================
// タイマー設定
//=============================================
void My::CTimer::SetTimer()
{
	//桁数取得
	int num_digit = m_pNumber.size();

	std::vector<int> pos_texU;

	//現在計算してる桁
	int nDigit = 1;
	int nCnt;
	for (nCnt = 0; nCnt < num_digit; nCnt++)
	{
		pos_texU.push_back(m_nCurrentTime / nDigit % 10);

		//桁を進める
		nDigit *= 10;
	}

	EraseDigit(pos_texU, num_digit);

	for (nCnt = num_digit - 1; nCnt >= 0; nCnt--)
	{
		//テクスチャの座標計算用変数
		float fMinTexU, fMaxTexU;

		fMinTexU = pos_texU[nCnt] * 0.1f;
		fMaxTexU = fMinTexU + 0.1f;

		m_pNumber[nCnt]->SetNumber(fMinTexU, fMaxTexU,COLOR_BLACK);
	}

	pos_texU.clear();
}

//=============================================
// 桁削除
//=============================================
void My::CTimer::EraseDigit(std::vector<int> pos_texU, int& num_digit)
{
	if (pos_texU[num_digit - 1] == INT_ZERO)
	{//桁を減らす
		if (num_digit - 1 == 0)
		{
			return;
		}
		CNumber_2D* pNumber = m_pNumber[num_digit - 1];
		pNumber->Uninit();
		pNumber = nullptr;

		m_pNumber.erase(m_pNumber.end() - 1);

		--num_digit;

		if (num_digit <= 0)
		{
			return;
		}
	}
}
