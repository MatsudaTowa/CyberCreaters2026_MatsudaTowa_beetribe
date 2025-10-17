//=============================================
//
//チュートリアルのステートパターン[tutorial_state.cpp]
//Author Matsuda Towa
//
//=============================================
#include "tutorial_state.h"
#include "tutorial.h"
#include "pause_select_setting.h"

//=============================================
// コンストラクタ
//=============================================
CTutorialNormal::CTutorialNormal()
{
}

//=============================================
// 通常処理
//=============================================
void CTutorialNormal::Normal(CActiveScene* active_scene)
{
	CNormal::Normal(active_scene);

	CTutorial* pTutorial = dynamic_cast<CTutorial*>(active_scene);
	pTutorial->Active();

	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetKeyboard();
	if (pKeyboard->GetTrigger(DIK_P) && active_scene->GetPauseKey())
	{
		active_scene->ResetPauseCnt();
		active_scene->ChangeState(new CTutorialPause);
	}
}

//=============================================
// ポーズ処理
//=============================================
void CTutorialPause::Pause(CActiveScene* active_scene)
{
	CPause::Pause(active_scene);
}

//=============================================
// 選択処理
//=============================================
void CTutorialPause::HandlePoseSelection(CActiveScene* active_scene)
{
	CPauseSelect* pSelect = GetSelectUI(GetSelect());
	if (typeid(*pSelect) == typeid(CPauseSelectContinue))
	{
		active_scene->ChangeState(new CTutorialNormal);
		return;
	}
	if (typeid(*pSelect) == typeid(CPauseSelectRetry))
	{
		CManager::GetInstance()->GetFade()->SetFade(CScene::MODE::MODE_TUTORIAL);
		return;
	}
	if (typeid(*pSelect) == typeid(CPauseSelectSetting))
	{
		active_scene->ChangeState(new CTutorialSetting);
		return;
	}
	CPause::HandlePoseSelection(active_scene);
}

//=============================================
// ポーズキャンセル処理
//=============================================
void CTutorialPause::CancelPause(CActiveScene* active_scene)
{
	active_scene->ChangeState(new CTutorialNormal);
}

//=============================================
// 設定処理
//=============================================
void CTutorialSetting::Setting(CActiveScene* active_scene)
{
	CSetting::Setting(active_scene);
	//入力デバイス取得
	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetKeyboard();
	if (pKeyboard->GetTrigger(DIK_P))
	{
		active_scene->ChangeState(new CTutorialNormal);
	}
}
