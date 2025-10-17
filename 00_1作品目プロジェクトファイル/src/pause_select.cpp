//=============================================
//
//ポーズのUI[pause_select.cpp]
//Author Matsuda Towa
//
//=============================================
#include "pause_select.h"
#include "manager.h"

//色
const D3DXCOLOR CPauseSelect::DEFAULT_COLOR = { 0.3f,0.3f,0.3f,1.0f };
//サイズ
const D3DXVECTOR2 CPauseSelect::SIZE = { 140.0f,30.0f };

//=============================================
// コンストラクタ
//=============================================
CPauseSelect::CPauseSelect(int nPriority):CObject2D(nPriority),
m_isSelect(false)
{
}

//=============================================
// デストラクタ
//=============================================
CPauseSelect::~CPauseSelect()
{
}

//=============================================
// 初期化
//=============================================
HRESULT CPauseSelect::Init()
{
	CObject2D::Init();
	//サイズ
	SetSize(SIZE);
	//頂点生成
	SetVtx(FLOAT_ONE);
	return S_OK;
}

//=============================================
// 終了
//=============================================
void CPauseSelect::Uninit()
{
	CObject2D::Uninit();
}

//=============================================
// 更新
//=============================================
void CPauseSelect::Update()
{
	CObject2D::Update();
	//頂点生成
	SetVtx(FLOAT_ONE);
	POINT pMousePos;
	GetCursorPos(&pMousePos);
	ScreenToClient(CManager::GetInstance()->GetHWnd(), &pMousePos);

	if (!m_isSelect)
	{
		SetColor(DEFAULT_COLOR);
		return;
	}

	SetColor(COLOR_WHITE);

}

//=============================================
// 描画
//=============================================
void CPauseSelect::Draw()
{
	CObject2D::Draw();
}

//=============================================
// 生成
//=============================================
CPauseSelect* CPauseSelect::Create(D3DXVECTOR3 pos, CPauseSelect* select)
{
	CPauseSelect* pSelect = select;
	if (pSelect == nullptr)
	{
		return nullptr;
	}
	pSelect->SetPos(pos);
	pSelect->SetType(OBJECT_TYPE_PAUSE_SELECT);
	pSelect->Init();
	return pSelect;
}