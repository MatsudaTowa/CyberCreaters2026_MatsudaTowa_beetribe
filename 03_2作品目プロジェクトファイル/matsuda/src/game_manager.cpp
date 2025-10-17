//=============================================
//
//ゲームマネージャー[gamemaneger.cpp]
//Auther MatsudaTowa
//
//=============================================
#include "game_manager.h"

//=============================================
// コンストラクタ
//=============================================
My::CGameManager::CGameManager():
m_pState(nullptr),			//ゲームのステート
m_pPlayer(nullptr),			//プレイヤーのポインタ
m_pField(nullptr),			//床のポインタ
m_pTimer(nullptr),			//タイマーのポインタ
m_pMouseCursor(nullptr),	//マウスカーソルのポインタ
m_pPaper(nullptr),			//紙のポインタ
m_pTimeScale(nullptr),
m_isFinish(false)
{
}

//=============================================
// デストラクタ
//=============================================
My::CGameManager::~CGameManager()
{
}

//=============================================
// 終了
//=============================================
void My::CGameManager::Uninit()
{
	if (m_pState != nullptr)
	{
		delete m_pState;
		m_pState = nullptr;
	}

	if (m_pGenerator != nullptr)
	{
		delete m_pGenerator;
		m_pGenerator = nullptr;
	}

	if (m_pTimeScale != nullptr)
	{
		delete m_pTimeScale;
		m_pTimeScale = nullptr;
	}

	if (m_pTimer != nullptr)
	{
		m_pTimer->Uninit();
		delete m_pTimer;
		m_pTimer = nullptr;
	}

	if (m_pPlayer != nullptr)
	{
		m_pPlayer->Uninit();
		m_pPlayer = nullptr;
	}
	if (m_pField != nullptr)
	{
		m_pField->Uninit();
		m_pField = nullptr;
	}
	if (m_pPaper != nullptr)
	{
		m_pPaper->Uninit();
		m_pPaper = nullptr;
	}
	if (m_pMouseCursor != nullptr)
	{
		m_pMouseCursor->Uninit();
		m_pMouseCursor = nullptr;
	}
}

//=============================================
//ステート変更
//=============================================
void My::CGameManager::ChangeState(CGameState* state)
{
	CGameState* current_state = CGameManager::GetInstance()->GetState();
	//今のステートを消し引数のステートに切り替える
	if (current_state != nullptr)
	{
		if (typeid(*current_state) == typeid(*state))
		{//現在と同じだったら関数を抜ける
			return;
		}
		delete current_state;

		current_state = state;
		CGameManager::GetInstance()->SetState(current_state);
	}
}