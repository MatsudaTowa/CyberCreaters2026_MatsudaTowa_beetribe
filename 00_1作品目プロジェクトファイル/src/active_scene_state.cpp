//=============================================
//
//アクティブシーンのステートパターン[active_scene_state.cpp]
//Author Matsuda Towa
//
//=============================================
#include "active_scene_state.h"
#include "active_scene.h"
#include "manager.h"
#include "pause_select_setting.h"

//=============================================
// コンストラクタ
//=============================================
CNormal::CNormal()
{
	while (1)
	{
		int nCnt = ShowCursor(FALSE);
		if (nCnt > 0)
		{
			continue;
		}
		break;
	}
	ShowCursor(FALSE);
}

//=============================================
// 通常処理
//=============================================
void CNormal::Normal(CActiveScene* active_scene)
{
	//オブジェクトのアップデートを許可する
	active_scene->UpdateObjectDecision(true);
	//カメラも
	CManager::GetInstance()->GetCamera()->SetActive(true);
}

//ポーズUI表示位置
const D3DXVECTOR3 CPause::SELECT_POS[CPause::MAX]
{
	{SCREEN_WIDTH * HALF,200.0f,0.0f},
	{SCREEN_WIDTH * HALF,300.0f,0.0f},
	{SCREEN_WIDTH * HALF,400.0f,0.0f},
	{SCREEN_WIDTH * HALF,500.0f,0.0f}
};

//閉じるUIの位置
const D3DXVECTOR3 CPause::CLOSE_POS = { 1000.0f,600.0f,0.0f };
//閉じるUIのサイズ
const D3DXVECTOR2 CPause::CLOSE_SIZE = { 130.0f,40.0f };

//=============================================
// コンストラクタ
//=============================================
CPause::CPause() :
	m_pSelect(),			//セレクトUIの数
	m_pMask(nullptr),		//黒いマスク
	m_pClosePause(nullptr)	//ポーズを閉じるUI
{
	while (1)
	{
		int nCnt = ShowCursor(TRUE);
		if (nCnt < 0)
		{
			continue;
		}
		break;
	}

	for (int i = 0; i < CPause::MAX; ++i)
	{
		if (m_pSelect[i] != nullptr)
		{
			continue;
		}
		switch (i)
		{
		case CONTINUE:
			m_pSelect[i] = CPauseSelect::Create(SELECT_POS[i], new CPauseSelectContinue);
			break;
		case SETTING:
			m_pSelect[i] = CPauseSelect::Create(SELECT_POS[i], new CPauseSelectSetting);
			break;
		case RETRY:
			m_pSelect[i] = CPauseSelect::Create(SELECT_POS[i], new CPauseSelectRetry);
			break;
		case QUIT:
			m_pSelect[i] = CPauseSelect::Create(SELECT_POS[i], new CPauseSelectQuit);
			break;
		default:
			break;
		}

	}

	m_pMask = CMask::Create(new CPauseMask);

	m_pClosePause = CClosePauseUI::Create(CLOSE_POS, CLOSE_SIZE);
}

//=============================================
// デストラクタ
//=============================================
CPause::~CPause()
{
	for (int i = 0; i < CPause::MAX; ++i)
	{
		if (m_pSelect[i] != nullptr)
		{
			m_pSelect[i]->Uninit();
			m_pSelect[i] = nullptr;
		}
	}
	if (m_pClosePause != nullptr)
	{
		m_pClosePause->Uninit();
		m_pClosePause = nullptr;
	}
	if (m_pMask != nullptr)
	{
		m_pMask->Uninit();
		m_pMask = nullptr;
	}
}

//=============================================
// ポーズ処理
//=============================================
void CPause::Pause(CActiveScene* active_scene)
{
	//オブジェクトのアップデートを止める
	active_scene->UpdateObjectDecision(false);

	//ポーズ関連のオブジェクトの更新は許可
	m_pMask->SetisActive(true);

	for (int i = 0; i < CPause::MAX; ++i)
	{
		if (m_pSelect[i] != nullptr)
		{
			m_pSelect[i]->SetisActive(true);
			m_pSelect[m_nSelect]->SetSelect(false);
		}
	}

	CInputKeyboard* pKeyBoard = CManager::GetInstance()->GetKeyboard();

	if (pKeyBoard->GetTrigger(DIK_S) || pKeyBoard->GetTrigger(DIK_DOWNARROW))
	{
		if (m_nSelect >= CPause::QUIT)
		{
			m_nSelect = CPause::CONTINUE;
			return;
		}
		++m_nSelect;
	}
	if (pKeyBoard->GetTrigger(DIK_W) || pKeyBoard->GetTrigger(DIK_UPARROW))
	{
		if (m_nSelect <= CPause::CONTINUE)
		{
			m_nSelect = CPause::QUIT;
			return;
		}
		--m_nSelect;
	}

	m_pSelect[m_nSelect]->SetSelect(true);

	if (pKeyBoard->GetTrigger(DIK_RETURN))
	{
		active_scene->ResetPauseCnt();
		HandlePoseSelection(active_scene);
		return;
	}

	//カメラも
	CManager::GetInstance()->GetCamera()->SetActive(false);

	//入力デバイス取得
	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetKeyboard();

	if (pKeyboard->GetTrigger(DIK_P) && active_scene->GetPauseKey())
	{
		active_scene->ResetPauseCnt();
		CancelPause(active_scene);
	}
}

//=============================================
// 選択処理
//=============================================
void CPause::HandlePoseSelection(CActiveScene* )
{
	if (typeid(*m_pSelect[m_nSelect]) == typeid(CPauseSelectQuit))
	{
		CManager::GetInstance()->GetFade()->SetFade(CScene::MODE::MODE_TITLE);
		return;
	}
}

//閉じるUIの位置
const D3DXVECTOR3 CSetting::CLOSE_POS = { 1000.0f,600.0f,0.0f };
//閉じるUIのサイズ
const D3DXVECTOR2 CSetting::CLOSE_SIZE = { 130.0f,40.0f };

//=============================================
// コンストラクタ
//=============================================
CSetting::CSetting():
m_pSettingUI(nullptr),
m_pClosePause(nullptr)
{
	if (m_pSettingUI == nullptr)
	{
		m_pSettingUI = new CSetting_UI;
		m_pSettingUI->Init();
	}
	m_pClosePause = CClosePauseUI::Create(CLOSE_POS, CLOSE_SIZE);
}

//=============================================
// デストラクタ
//=============================================
CSetting::~CSetting()
{
	if (m_pSettingUI != nullptr)
	{
		m_pSettingUI->Uninit();
		m_pSettingUI = nullptr;
	}
	if (m_pClosePause != nullptr)
	{
		m_pClosePause->Uninit();
		m_pClosePause = nullptr;
	}
}

//=============================================
// 設定処理
//=============================================
void CSetting::Setting(CActiveScene* )
{
	if (m_pSettingUI != nullptr)
	{
		m_pSettingUI->Update();

		float sens = CManager::GetInstance()->GetCamera()->ConvertSensToSettingValue();

		ChangeSens(sens);
	}
}

//=============================================
// 感度変更
//=============================================
void CSetting::ChangeSens(float& sens)
{
	//入力デバイス取得
	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetKeyboard();
	if (pKeyboard->GetPress(DIK_A)||pKeyboard->GetPress(DIK_LEFTARROW))
	{
		++m_nPressCnt;
		if (m_nPressCnt <= PRESS_FRAME)
		{
			return;
		}
		if (sens > MIN_SENS)
		{
			m_nPressCnt = 0;
			sens -= CHANGE_SENS;
		}
		if (pKeyboard->GetRelease(DIK_A)||pKeyboard->GetPress(DIK_LEFTARROW))
		{
			m_nPressCnt = 0;
		}
	}

	if (pKeyboard->GetPress(DIK_D)||pKeyboard->GetPress(DIK_RIGHTARROW))
	{
		++m_nPressCnt;

		if (m_nPressCnt <= PRESS_FRAME)
		{
			return;
		}
		if (sens < MAX_SENS)
		{
			m_nPressCnt = 0;
			sens += CHANGE_SENS;
		}
		if (pKeyboard->GetRelease(DIK_D) || pKeyboard->GetPress(DIK_RIGHTARROW))
		{
			m_nPressCnt = 0;
		}
	}
	CManager::GetInstance()->GetCamera()->ConvertSens(sens);
	m_pSettingUI->SetSens_UI(sens);
	m_pSettingUI->SetNumber(sens);
}
