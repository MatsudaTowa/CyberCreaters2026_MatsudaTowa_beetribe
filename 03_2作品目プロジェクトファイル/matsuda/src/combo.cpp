//=============================================
//
//コンボ表示処理「combo.cpp」
// Author松田永久
//
//=============================================
#include "combo.h"

namespace
{
	const int NUM_DIGIT = 1;										//桁数
	const float DIGIT_SHIFT = 40.0f;								//桁ごとに座標をずらす
	const float SUB_ALPHA = 0.01f;									//アルファ値減少値
	const D3DXVECTOR2 NUMBER_SIZE = D3DXVECTOR2(50.0f, 70.0f);		//数字のサイズ
	const D3DXVECTOR2 UI_SIZE = D3DXVECTOR2(160.0f, 50.0f);			//UIのサイズ
	const float CORRECTION_NUM_POS_X = 80.0f;						//数字の位置調整
	const float CORRECTION_NUM_POS_Y = 30.0f;						//数字の位置調整
	const std::string TEXTURE_NAME = "data\\TEXTURE\\combo.png";	//テクスチャの名前
}

//=============================================
// コンストラクタ
//=============================================
My::CCombo::CCombo(int nPriority):CObject2D(nPriority),
	m_combo(INT_ZERO),				//コンボ
	m_num_pos(VEC3_RESET_ZERO),		//数字の位置
	m_pCnt(nullptr),				//カウントのポインタ
	m_pNumber()						//数字のポインタ(格納用)
{
	m_pNumber.clear();
}

//=============================================
// デストラクタ
//=============================================
My::CCombo::~CCombo()
{
}

//=============================================
// 初期化
//=============================================
HRESULT My::CCombo::Init()
{
	CObject2D::Init();

	CTexture* pTexture = GET_TEXTURE;
	BindTexture(pTexture->GetAddress(pTexture->Regist(&TEXTURE_NAME))); //テクスチャ設定

	SetSize(UI_SIZE);
	SetColor(COLOR_WHITE);

	m_num_pos = GetPos();

	m_num_pos.x -= CORRECTION_NUM_POS_X;
	m_num_pos.y -= CORRECTION_NUM_POS_Y;

	if (m_pCnt == nullptr)
	{
		m_pCnt = new CCount;
		m_pCnt->SetFrame(ONE_SECOND);
	}

	for (int nCnt = 0; nCnt < NUM_DIGIT; nCnt++)
	{
		CNumber_2D* pNumber = CNumber_2D::Create(m_num_pos, NUMBER_SIZE, CNumber_2D::TEX_001);
		m_pNumber.push_back(pNumber);

		//座標をずらす
		m_num_pos.x -= DIGIT_SHIFT;
	}
	SetVtx();

	return S_OK;
}

//=============================================
// 終了
//=============================================
void My::CCombo::Uninit()
{
	if (m_pCnt != nullptr)
	{
		delete m_pCnt;
		m_pCnt = nullptr;
	}
	for (auto& itr : m_pNumber)
	{
		if (itr == nullptr)
		{
			continue;
		}
		itr->Uninit();
		itr = nullptr;
	}
	m_pNumber.clear();
	CObject2D::Uninit();
}

//=============================================
// 更新
//=============================================
void My::CCombo::Update()
{
	if (!GetIsDelete())
	{
		SetCombo();
	}
	SubAlpha();

	CObject2D::Update();
	SetVtx();
}


//=============================================
// アルファ値減少
//=============================================
void My::CCombo::SubAlpha()
{
	if (GetIsDelete())
	{
		D3DXCOLOR col = GetColor();

		col.a -= SUB_ALPHA;

		SetColor(col);

		for (auto& itr : m_pNumber)
		{
			if (itr == nullptr)
			{
				continue;
			}
			itr->SetColor(col);
			itr->NumberVtx();
		}
	}
}

//=============================================
// 描画
//=============================================
void My::CCombo::Draw()
{
	CObject2D::Draw();
}

//=============================================
// 生成
//=============================================
My::CCombo* My::CCombo::Create(D3DXVECTOR3 pos)
{
	CCombo* pCombo = new CCombo;
	if (pCombo == nullptr) { return nullptr; }
	pCombo->SetPos(pos);
	pCombo->Init();
	return pCombo;
}

//=============================================
// コンボ数の表示設定
//=============================================
void My::CCombo::SetCombo()
{
	//桁数取得
	int num_digit = m_pNumber.size();

	std::vector<int> pos_texU;

	//現在計算してる桁
	int nDigit = 1;
	int nCnt;
	for (nCnt = 0; nCnt < num_digit; nCnt++)
	{
		pos_texU.push_back(m_combo / nDigit % 10);

		//桁を進める
		nDigit *= 10;
	}

	AddDigit(pos_texU, num_digit);

	for (nCnt = num_digit - 1; nCnt >= 0; nCnt--)
	{
		//テクスチャの座標計算用変数
		float fMinTexU, fMaxTexU;

		fMinTexU = pos_texU[nCnt] * 0.1f;
		fMaxTexU = fMinTexU + 0.1f;

		m_pNumber[nCnt]->SetNumber(fMinTexU, fMaxTexU, COLOR_WHITE);
	}

	pos_texU.clear();
}

//=============================================
// 桁追加
//=============================================
void My::CCombo::AddDigit(std::vector<int>& pos_texU, int& num_digit)
{
	if (pos_texU[num_digit - 1] == 0)
	{//桁を減らす
		CNumber_2D* pNumber;

		//座標をずらす
		m_num_pos.x -= DIGIT_SHIFT;
		pNumber = CNumber_2D::Create(m_num_pos, NUMBER_SIZE,1);
		m_pNumber.push_back(pNumber);

		++num_digit;

		pos_texU.clear();
		int nDigit = 1;
		for (int nCnt = 0; nCnt < num_digit; nCnt++)
		{
			pos_texU.push_back(m_combo / nDigit % 10);

			//桁を進める
			nDigit *= 10;
		}
	}
}
