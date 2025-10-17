//=============================================
//
//ゲームプレイヤー[game_player.cpp]
//Author Matsuda Towa
//
//=============================================
#include "game_player.h"
#include "game_manager.h"
#include "sound_bgm.h"
#include "sound_se.h"

//=============================================
// コンストラクタ
//=============================================
My::CGamePlayer::CGamePlayer(int nPriority):CPlayer(nPriority),
m_pState(nullptr),		//ステート初期化
m_pCombo(nullptr),
m_pBoardHolder(),		//板持ち人保存変数初期化
m_pMovePoint()			//移動ポイント初期化
{
	//開く（音量、再生）
	CSoundBGM_000::Open();
	CSoundBGM_000::volume(CSoundBGM_000::MAX_VOLUME);
	CSoundBGM_000::Play();

	CSoundSE_000::Open();
}

//=============================================
// デストラクタ
//=============================================
My::CGamePlayer::~CGamePlayer()
{
	//各ファイルの停止と終了
	CSoundBGM_000::Stop();
	CSoundBGM_000::Close();

	CSoundSE_000::Stop();
	CSoundSE_000::Close();
}

//=============================================
// 初期化
//=============================================
HRESULT My::CGamePlayer::Init()
{
	if (m_pState == nullptr)
	{
		m_pState = new CNeutralState;
	}

	//親クラスの初期化実行
	CPlayer::Init();

	//ゲームのマネージャに自分を代入
	CGameManager::GetInstance()->SetPlayer(this);
	return S_OK;
}

//=============================================
// 終了
//=============================================
void My::CGamePlayer::Uninit()
{
	m_pBoardHolder.clear();

	if (m_pState != nullptr)
	{
		delete m_pState;
		m_pState = nullptr;
	}

	if (m_pCombo != nullptr)
	{
		m_pCombo->Uninit();
		m_pCombo = nullptr;
	}

	ClearMovePoint();

	//親クラスの終了処理
	CPlayer::Uninit();
}

//=============================================
// ゲーム内音源が切れた時の処理
//=============================================
void  My::CGamePlayer::Play_Sound_BGM_000()
{
	char uReturnLength[10];                                            //現在の状態の取得用変数
	char A[] = "stopped";                                              //状態設定（止まっている）
	mciSendString(TEXT("status BGM0 mode"), uReturnLength, 100, NULL);  //現在の状態を測定

	//状態が合致した時
	if (strcmp(uReturnLength, A) == 0)
	{
		CSoundBGM_000::Stop(); //止める
		CSoundBGM_000::Zero(); //ゼロから再生
	}
}

//=============================================
// 更新
//=============================================
void My::CGamePlayer::Update()
{
	Play_Sound_BGM_000();

	if (m_pState != nullptr)
	{
		m_pState->Attack(this);
		m_pState->MovetoFree(this);
		m_pState->Neutral(this);
	}

	//親クラスの更新
	CPlayer::Update();

	CBelt* pBelt = GetBelt();
	if (pBelt != nullptr)
	{//帯があったら
	 //帯を動かす
		CModel_Parts* parts = GetModelParts(0);
		float fAngle = atan2f(sinf(GetRot().y), cosf(GetRot().y));
		pBelt->SetPos({ parts->GetMtxWorld()._41 + GetMove().x,parts->GetMtxWorld()._42 - CORRECTION_VALUE_BELT,parts->GetMtxWorld()._43 + GetMove().z });
		pBelt->SetRot({ FLOAT_ZERO,fAngle,FLOAT_ZERO });
		pBelt->SetisDraw(GetisDraw());
	}

	if (m_pCombo != nullptr)
	{
		if (!m_pCombo->GetIsDelete())
		{
			return;
		}
		if (m_pCombo->GetColor().a > FLOAT_ZERO)
		{
			return;
		}
	
		m_pCombo->Uninit();
		m_pCombo = nullptr;
	}
}

//=============================================
// 描画
//=============================================
void My::CGamePlayer::Draw()
{
	//親クラスの描画
	CPlayer::Draw();
}

//=============================================
// ステート変更
//=============================================
void My::CGamePlayer::ChangeState(CGamePlayerState* state)
{
	//今のステートを消し引数のステートに切り替える
	if (m_pState != nullptr)
	{
		delete m_pState;
		m_pState = state;
	}
}

//=============================================
// 入力
//=============================================
void My::CGamePlayer::Input()
{
}

//=============================================
//プレイヤーのデバッグ表示
//=============================================
void My::CGamePlayer::Debug()
{
#ifdef _DEBUG
	LPD3DXFONT pFont = CManager::GetInstance()->GetRenderer()->GetFont();
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	sprintf(&aStr[0], "\n\n[player]\npos:%.1f,%.1f,%.1f\nrot:%.1f,%.1f,%.1f\nmove:%.1f,%.1f,%.1f\n何枚割るか%d\nスコア%d"
		, GetPos().x, GetPos().y, GetPos().z, GetRot().x, GetRot().y, GetRot().z, GetMove().x, GetMove().y, GetMove().z,m_pBoardHolder.size(),GET_SCORE->GetCurrentScore());
	//テキストの描画
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 0, 0, 255));
#endif // _DEBUG
}