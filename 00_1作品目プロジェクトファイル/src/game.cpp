//=============================================
//
//ゲーム[game.cpp]
//Author Matsuda Towa
//
//=============================================
#include "game.h"
#include "object.h"
#include "object2D.h"
#include "object3D.h"
#include "objectX.h"
#include "colision.h"
#include "block.h"
#include "field.h"
#include "manager.h"
#include "dash_effect.h"
#include "active_player.h"

//ウェーブ
CWave* CGame::m_pWave = nullptr;
//=============================================
//コンストラクタ
//=============================================
CGame::CGame():
m_nResultDelay(INT_ZERO),	//リザルトの遷移ディレイ
m_next_wave()				//次のウェーブ格納変数
{
}

//=============================================
//デストラクタ
//=============================================
CGame::~CGame()
{
}

//=============================================
//初期化
//=============================================
HRESULT CGame::Init()
{
	CManager::GetInstance()->GetSound()->PlaySound(CSound::SOUND_LABEL_BGM_GAME);

	CActiveScene::Init();

	ChangeState(new CGameNormal);

	SetWave(CWave::WAVE::ONE);

	return S_OK;
}

//=============================================
//終了
//=============================================
void CGame::Uninit()
{
	CActiveScene::Uninit();

	CManager::GetInstance()->GetSound()->StopSound();

	if (m_pWave != nullptr)
	{
		m_pWave->Uninit();
		m_pWave = nullptr;
	}

	CObject::ReleaseAll();
}

//=============================================
//更新
//=============================================
void CGame::Update()
{
	CActiveScene::Update();
}

//=============================================
//死んだ数だけスコアマイナス
//=============================================
void CGame::ApplyDeathPenalty()
{
	for (int i = 0; i < CObject::MAX_OBJECT; i++)
	{
		//オブジェクト取得
		CObject* pObj = CObject::Getobject(CPlayer::PLAYER_PRIORITY, i);
		if (pObj == nullptr)
		{//ヌルポインタなら
			//オブジェクトを探し続ける
			continue;
		}

		//タイプ取得
		CObject::OBJECT_TYPE type = pObj->GetType();
			
		if (type != CObject::OBJECT_TYPE::OBJECT_TYPE_PLAYER)
		{//プレイヤーじゃなかったら
			//プレイヤーを探し続ける
			continue;
		}

		CActivePlayer* pPlayer = dynamic_cast<CActivePlayer*>(pObj);

		for (int j = 0; j < pPlayer->GetDeathCnt(); j++)
		{
			CScore* pScore = CWave::GetScore();

			if (pScore->GetScore() > INT_ZERO)
			{
				pScore->AddScore(DEATH_PENALTY);

				if (pScore->GetScore() <= INT_ZERO)
				{//0を下回ったら
					//スコア0に
					pScore->SetScore();
				}
			}
		}
	}
}

//=============================================
//描画
//=============================================
void CGame::Draw()
{
}

//=============================================
//ウェーブ設定
//=============================================
void CGame::SetWave(CWave::WAVE wave)
{
	//ウェーブ終了
	if (m_pWave != nullptr)
	{
		m_pWave->Uninit();
		delete m_pWave;
		m_pWave = nullptr;
	}

	//ウェーブ切り替え
	if (m_pWave == nullptr)
	{
		m_pWave = CWave::Create(wave);
	}
}

//=============================================
//ウェーブ設定
//=============================================
void CGame::SetWave(CWave::WAVE wave, CWave::WAVE next_wave,const char* ResultFile)
{
	//ウェーブ終了
	if (m_pWave != nullptr)
	{
		m_pWave->Uninit();
		delete m_pWave;
		m_pWave = nullptr;
	}

	//ウェーブ切り替え
	if (m_pWave == nullptr)
	{
		m_pWave = CWave::Create(wave, next_wave, ResultFile);
	}
}