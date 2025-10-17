//=============================================
//
//ゲーム[game.cpp]
//Author Matsuda Towa
//
//=============================================
#include "game.h"
#include "game_field.h"
#include "game_player.h"
#include "game_camera.h"
#include "board_holder.h"
#include "game_mouse_cursor.h"
#include "game_manager.h"
#include "board_holder_generator.h"
#include "timer.h"
#include "json.h"

namespace
{
	const D3DXVECTOR3 FIELD_SIZE = { 1000.0f,0.0f,1000.0f };
	const int COOL_TIME = 1;
	const int DELAY_FRAME = 90;
}

//=============================================
//コンストラクタ
//=============================================
My::CGame::CGame():
m_pPauseCnt(nullptr),				//ポーズのキーを有効化するためのカウント
m_pDelayCnt(nullptr)				//リザルトに遷移するまでのディレイカウント
{
	CGameManager::GetInstance()->SetFinish(false);
}

//=============================================
//デストラクタ
//=============================================
My::CGame::~CGame()
{
}

//=============================================
//初期化
//=============================================
HRESULT My::CGame::Init()
{
	//ジェイソンの生成
	//CJson::GetJson() = new CJson();
	CJson::GetJson()->Create();
	CJson::GetJson()->DeleteJson();

	for (int i = 0; i < CAMERA_MAX; ++i)
	{
		CREATE_CAMERA(new CGameCamera);
		switch (i)
		{
		case GAME_CAMERA:
			GET_CAMERA(i)->ChangeCameraState(new CDiagonaView);
			break;
		case EVENT_CAMERA_000:
			GET_CAMERA(i)->ChangeCameraState(new CThirdView);
			break;
		case EVENT_CAMERA_001:
			GET_CAMERA(i)->ChangeCameraState(new CSideView);
			break;
		case BOARD_GENERATE_CAMERA:
			GET_CAMERA(i)->ChangeCameraState(new CTrailView);
			break;
		default:
			break;
		}
	}
	SET_CAMERA_IDX(GAME_CAMERA);

	CGameState* current_state = CGameManager::GetInstance()->GetState();
	if (current_state == nullptr)
	{
		current_state = new CNormal;
	}		
	CGameManager::GetInstance()->SetState(current_state);

	if (m_pPauseCnt == nullptr)
	{
		m_pPauseCnt = new CCount;
		m_pPauseCnt->SetFrame(COOL_TIME);
	}

	if (m_pDelayCnt == nullptr)
	{
		m_pDelayCnt = new CCount;
		m_pDelayCnt->SetFrame(DELAY_FRAME);
	}
	//地面生成
	CField::Create(VEC3_RESET_ZERO, FIELD_SIZE,new CGameField);

	//プレイヤー生成
	CPlayer::Create(new CGamePlayer);

	CMouseCursor::Create(new CGameMouseCursor);

	CBoardHolderGenerator* generator = new CBoardHolderGenerator;
	generator->Init();

	CTimer* timer = new CTimer;
	timer->Init();

	CTimeScale* ptimescale = new CTimeScale();
	ptimescale->Init();

	return S_OK;
}

//=============================================
//終了
//=============================================
void My::CGame::Uninit()
{
	////ジェイソンの情報削除
	//if (CJson::GetJson() != nullptr)
	//{
	//	delete CJson::GetJson();
	//	CJson::GetJson() = nullptr;
	//}

	if (m_pDelayCnt != nullptr)
	{
		delete m_pDelayCnt;
		m_pDelayCnt = nullptr;
	}

	if (m_pPauseCnt != nullptr)
	{
		delete m_pPauseCnt;
		m_pPauseCnt = nullptr;
	}
	CJson::GetJson()->Uninit();

	//ステート初期化
	CGameManager::GetInstance()->ChangeState(new CNormal);

	//マネージャーで管理しているオブジェクトをここで削除
	//NOTE: オブジェクトのReleaseAll前に消すことで二重で削除することを防止
	//NOTE: 紙は上のステート変更される際に消される
	CGameManager::GetInstance()->GetPlayer()->Uninit();
	CGameManager::GetInstance()->SetPlayer(nullptr);
	CGameManager::GetInstance()->GetField()->Uninit();
	CGameManager::GetInstance()->SetField(nullptr);
	CGameManager::GetInstance()->GetMouseCursor()->Uninit();
	CGameManager::GetInstance()->SetMouseCursor(nullptr);

	CObject::ReleaseAll();
	CGameManager::GetInstance()->Uninit();
}

//=============================================
//更新
//=============================================
void My::CGame::Update()
{
	if (!CGameManager::GetInstance()->GetFinish())
	{
		for (int nCount = 0; nCount < 3; nCount++)
		{
			CJson::GetJson()->GetKarate(nCount)->Createobj(); //板持の生成
		}

		//ポーズのカウントアップ
		m_pPauseCnt->CountUp();

		GET_CAMERA(GET_CAMERA_IDX)->SetCamera();
		GET_CAMERA(BOARD_GENERATE_CAMERA)->SetCamera();
		GET_CAMERA(BOARD_GENERATE_CAMERA)->ChangeCameraState(new CTrailView);

		CGameManager::GetInstance()->GameStateExecution(this);
		return;
	}

	if (!m_pDelayCnt->CountUp())
	{
		return;
	}
	//ステート初期化
	CGameManager::GetInstance()->ChangeState(new CNormal);
	GET_FADE->SetFade(CScene::MODE::MODE_RESULT);
}


//=============================================
//オブジェクトの更新を行うか決定
//=============================================
void My::CGame::UpdateObjectDecision(bool isStop)
{
	for (int i = 0; i < CObject::PRI_MAX; ++i)
	{
		for (int j = 0; j < CObject::MAX_OBJECT; ++j)
		{
			//オブジェクト取得
			CObject* pObj = CObject::Getobject(i,j);	//先頭取得

			if (pObj == nullptr)
			{
				continue;
			}

			if (pObj->GetStop() != isStop)
			{
				pObj->SetStop(isStop);
			}
		}
	}
}

//=============================================
//描画
//=============================================
void My::CGame::Draw()
{
	GET_CAMERA(GET_CAMERA_IDX)->SetCamera();
	GET_CAMERA(BOARD_GENERATE_CAMERA)->SetCamera();
}
