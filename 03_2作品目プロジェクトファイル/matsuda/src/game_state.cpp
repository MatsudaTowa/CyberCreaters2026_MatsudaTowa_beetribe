//=============================================
//
//ゲームのステートパターン[game_state.cpp]
//Author Matsuda Towa
//
//=============================================
#include "game_state.h"
#include "game.h"
#include "game_manager.h"

//=============================================
// 通常
//=============================================
void My::CNormal::Normal(CGame* game)
{
	//オブジェクトのアップデートを許可する
	game->UpdateObjectDecision(false);

	CGamePlayer* player = CGameManager::GetInstance()->GetPlayer();
	if (typeid(*player->GetState()) == typeid(CAttackState))
	{
		CGameManager::GetInstance()->ChangeState(new CAttack);
		return;
	}

	CTimer* timer = CGameManager::GetInstance()->GetTimer();
	int old_time = timer->GetCurrentTimer();

	timer->DecreaseTime();

	int current_time = timer->GetCurrentTimer();
	if (current_time < SPECIAL_TIME)
	{//現在の時間が必殺技の時間を下回ってたら
		//保存してた過去の時間に戻す
		current_time = old_time;
		timer->SetCurrentTimer(current_time);
	}

	//NOTE:ここでテクスチャをズラすため前の段階でタイムの設定を行う
	timer->Update();

	//入力デバイス取得
	CInputKeyboard* pKeyboard = GET_INPUT_KEYBOARD;

#ifdef _DEBUG
	if (pKeyboard->GetTrigger(DIK_0))
	{//必殺技状態の時間へ
		timer->SetCurrentTimer(SPECIAL_TIME);
	}
#endif // DEBUG
	CGameMouseCursor* mouse = CGameManager::GetInstance()->GetMouseCursor();

	if (current_time <= SPECIAL_TIME
		&& typeid(*mouse->GetState()) == typeid(CNormalCursol))
	{//時間が必殺技を行う状態でカメラが上から、マウスカーソルが通常状態なら
		
		if (CGameManager::GetInstance()->GetGenerator()->ManyCreate(CGameManager::GetInstance()->GetField()))
		{
			CGameManager::GetInstance()->ChangeState(new CSpecialWrite);
		}
		return;
	}

	CBoardHolderGenerator* generator = CGameManager::GetInstance()->GetGenerator();

	if (generator != nullptr)
	{
		if (typeid(*mouse->GetState()) == typeid(CNormalCursol))
		{
			generator->Generate();
		}
	}

	//ポーズ移行
	if (pKeyboard->GetTrigger(DIK_P) && game->GetPauseKey())
	{
		game->ResetPauseCnt();
		CGameManager::GetInstance()->ChangeState(new CPause);
		return;
	}
}

//=============================================
// デストラクタ
//=============================================
My::CAttack::~CAttack()
{
}

//=============================================
// 攻撃
//=============================================
void My::CAttack::Attack(CGame* game)
{
	//入力デバイス取得
	CInputKeyboard* pKeyboard = GET_INPUT_KEYBOARD;

	CGamePlayer* player = CGameManager::GetInstance()->GetPlayer();
	if (typeid(*player->GetState()) != typeid(CAttackState))
	{
		CGameManager::GetInstance()->ChangeState(new CNormal);
		return;
	}
}

//=============================================
// デストラクタ
//=============================================
My::CPause::~CPause()
{
	CGameMouseCursor* mouse = CGameManager::GetInstance()->GetMouseCursor();

	if (mouse->GetTrailPointSize() > 0)
	{
		mouse->ChangeState(new CWrittenCursol);
		return;
	}
	mouse->ChangeState(new CNormalCursol);
}

//=============================================
// ポーズ
//=============================================
void My::CPause::Pause(CGame* game)
{
	//オブジェクトのアップデートを止める
	game->UpdateObjectDecision(true);

	//マウスの更新は呼ぶ
	CGameMouseCursor* mouse = CGameManager::GetInstance()->GetMouseCursor();
	mouse->ChangeState(new CPauseCursol);
	mouse->SetStop(false);

	//入力デバイス取得
	CInputKeyboard* pKeyboard = GET_INPUT_KEYBOARD;

	if (pKeyboard->GetTrigger(DIK_P) && game->GetPauseKey())
	{
		game->ResetPauseCnt();
		CGameManager::GetInstance()->ChangeState(new CNormal);
		return;
	}
}

//=============================================
// コンストラクタ
//=============================================
My::CSpecialWrite::CSpecialWrite()
{
	CPaper::Create({ SCREEN_WIDTH * HALF,SCREEN_HEIGHT * HALF,0.0f });

	std::list<CBoardHolder*>holder = CGameManager::GetInstance()->GetGenerator()->GetBoardHolderList();
	for (auto& itr : holder)
	{
		if (typeid(*itr) != typeid(CTrapHolderInfo))
		{
			continue;
		}
		itr->Uninit();
		itr = nullptr;
	}

	CCombo* combo = CGameManager::GetInstance()->GetPlayer()->GetComboUI();
	if (combo == nullptr)
	{
		return;
	}
	combo->Uninit();
	combo = nullptr;
	CGameManager::GetInstance()->GetPlayer()->SetComboUI(combo);

}

//=============================================
// デストラクタ
//=============================================
My::CSpecialWrite::~CSpecialWrite()
{
	CPaper* paper = CGameManager::GetInstance()->GetPaper();
	if (paper != nullptr)
	{
		paper->Uninit();
		paper = nullptr;
		CGameManager::GetInstance()->SetPaper(paper);
	}
}

//=============================================
// 必殺技を描く
//=============================================
void My::CSpecialWrite::SpecialWrite(CGame* game)
{
	//プレイヤーのアップデートを止める
	CGameManager::GetInstance()->GetPlayer()->SetStop(true);
	//マウスの更新は呼ぶ
	CGameMouseCursor* mouse = CGameManager::GetInstance()->GetMouseCursor();
	mouse->SetStop(false);
	CPaper* paper = CGameManager::GetInstance()->GetPaper();
	if (paper != nullptr)
	{
		paper->SetStop(false);
	}
}

//=============================================
// コンストラクタ
//=============================================
My::CSpecialAttack::CSpecialAttack()
{
}

//=============================================
// デストラクタ
//=============================================
My::CSpecialAttack::~CSpecialAttack()
{
}

//=============================================
// 必殺技攻撃処理
//=============================================
void My::CSpecialAttack::SpecialAttack(CGame* game)
{
	//オブジェクトのアップデートを許可
	game->UpdateObjectDecision(false);

	//マウスカーソルのみ更新を止め、描画しない
	CGameMouseCursor* mouse = CGameManager::GetInstance()->GetMouseCursor();
	mouse->SetStop(true);
	mouse->SetisDraw(false);

	//TODO: ここに演出処理	


	//TODO: 一旦全部一気に割るように書いてる、演出に合わせて割れるように変更
	CBoardHolderGenerator* generator = CGameManager::GetInstance()->GetGenerator();

	std::list<CBoardHolder*> holderlist = generator->GetBoardHolderList();

	for (auto& itr : holderlist)
	{
		if (typeid(*itr) != typeid(CTrapHolderInfo))
		{
			CScore* pScore = GET_SCORE;
			int score = pScore->GetCurrentScore();
			++score;
			pScore->SetCurrentScore(score);
			itr->KnockDown();
		}
	}

	//ゲーム終了
	CGameManager::GetInstance()->SetFinish(true);
}
