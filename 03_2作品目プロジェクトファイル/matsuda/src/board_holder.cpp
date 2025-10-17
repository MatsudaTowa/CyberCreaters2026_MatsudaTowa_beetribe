//=============================================
//
//板持ち人[board_holder.cpp]
//Author Matsuda Towa
//
//=============================================
#include "board_holder.h"
#include "game_manager.h"
#include "json.h"
#include "board_danger.h"
#include "board_hard.h"
#include "board_normal.h"
#include "splash_effect.h"
#include "ink_field.h"

namespace
{
	const int DELAY_DETH_FRAME = 5;
	const int NUM_PARTICLE = 10;
	const D3DXVECTOR3 SHADOW_SIZE = { 20.0f, 0.0, 20.0f };	//影のサイズ
}

//=============================================
// コンストラクタ
//=============================================
My::CBoardHolder::CBoardHolder(int nPriority):CCharacter(nPriority),
m_DelayDethCnt(nullptr),
m_pHitUI(nullptr)
{
	//マネージャーに登録
	CGameManager::GetInstance()->GetGenerator()->Regist(this);
	if (m_DelayDethCnt == nullptr)
	{
		m_DelayDethCnt = new CCount;
		m_DelayDethCnt->SetFrame(DELAY_DETH_FRAME);
	}
	m_pBoard.clear();
}

//=============================================
// デストラクタ
//=============================================
My::CBoardHolder::~CBoardHolder()
{
	if (m_DelayDethCnt != nullptr)
	{
		delete m_DelayDethCnt;
		m_DelayDethCnt = nullptr;
	}
	//マネージャーに登録
	CGameManager::GetInstance()->GetGenerator()->Delete(this,this->GetPos());
}

//=============================================
// 初期化
//=============================================
HRESULT My::CBoardHolder::Init()
{
	CCharacter::Init();

	//初期モーション設定
	SetMotion(MOTION_NEUTRAL);

	//影のサイズ設定
	SetShadowSize(SHADOW_SIZE);
	return S_OK;
}

//=============================================
// 終了
//=============================================
void My::CBoardHolder::Uninit()
{
	for (auto& itr : m_pBoard)
	{
		if (itr != nullptr)
		{
			itr->Unload();
			itr = nullptr;
		}
	}
	m_pBoard.clear();

	if (m_pHitUI != nullptr)
	{
		m_pHitUI->Uninit();
		m_pHitUI = nullptr;
	}

	//親クラスの終了処理を呼ぶ
	CCharacter::Uninit();
}

//=============================================
// 更新
//=============================================
void My::CBoardHolder::Update()
{
	if (GetIsDelete())
	{
		if (m_DelayDethCnt->CountUp())
		{
			Uninit();
		}
		return;
	}
	CCharacter::Update();

	LookAtPlayer();

	Motion(); //モーション処理

	if (m_pHitUI != nullptr)
	{
		D3DXVECTOR3 screen_pos = ConvertToScreenPos(GET_CAMERA(GET_CAMERA_IDX), GetPos()); //スクリーン座標に変換
		m_pHitUI->SetPos(screen_pos);
	}

	if (GetPos().y < KILL_Y)
	{
		Uninit();
	}
}

//=============================================
// 描画
//=============================================
void My::CBoardHolder::Draw()
{
	//親クラスのモーション用の描画を呼ぶ
	MotionDraw();

	for (auto& itr : m_pBoard)
	{
		if (itr != nullptr)
		{
			itr->Draw();
		}
	}
}

//=============================================
// 倒される
//=============================================
void My::CBoardHolder::KnockDown()
{
	for (int i = INT_ZERO; i < NUM_PARTICLE; ++i)
	{
		CSplashEffect::Create({ GetPos().x,5.0f,GetPos().z });
	}

	CInkField::Create({ GetPos().x,1.0f,GetPos().z });

	Uninit();
}

//=============================================
// 生成
//=============================================
My::CBoardHolder* My::CBoardHolder::Create(D3DXVECTOR3 pos, CBoardHolder* pBoardHolder)
{
	CBoardHolder* pBoardHorder = pBoardHolder;

	// nullならnullを返す
	if (pBoardHorder == nullptr) { return nullptr; }

	pBoardHorder->SetPos({ pos.x,0.2f,pos.z }); //pos設定

	pBoardHorder->Load_Parts("data\\MOTION\\motion_BoardHolder.bin"); //パーツ読み込み

	pBoardHorder->Init(); //初期化処理

	pBoardHorder->SetType(OBJECT_TYPE_BOARD_HORDER); //タイプ設定

	return pBoardHorder;
}

//=============================================
// ヒットUI生成
//=============================================
void My::CBoardHolder::CreateHitUI()
{
	if (GetIsDelete())
	{
		return;
	}
	if (m_pHitUI == nullptr)
	{
		D3DXVECTOR3 screen_pos = ConvertToScreenPos(GET_CAMERA(GET_CAMERA_IDX), GetPos()); //スクリーン座標に変換

		m_pHitUI = CHit_UI::Create(screen_pos, 0); //TODO: タイプは一旦0で代入、クラス先で殴っちゃいけないものに
		CGamePlayer* player = CGameManager::GetInstance()->GetPlayer();
		player->SetBoardHolder(this);
	}
}

//=============================================
// プレイヤーを見つめる
//=============================================
void My::CBoardHolder::LookAtPlayer()
{
	CGamePlayer* pPlayer = CGameManager::GetInstance()->GetPlayer();

	//プレイヤーとの距離算出
	D3DXVECTOR3 Distance = pPlayer->GetPos() - GetPos();

	//プレイヤーに向ける角度を算出
	float fAngle = atan2f(Distance.x, Distance.z);

	//親クラスからrotを取得
	D3DXVECTOR3 rot = GetRot();

	rot.y = fAngle + D3DX_PI;

	SetRot(rot);
}

//===========================================================================================================================================
//板持ちの情報処理
//===========================================================================================================================================


//板の回転量
const D3DXVECTOR3 My::CBoardHolderInfo::RIGHT_TURN = { 0.0f,0.0f,-1.0f };
const D3DXVECTOR3 My::CBoardHolderInfo::LEFT_TURN = { 0.0f,0.0f,-2.0f };

//=============================================
// コンストラクタ
//=============================================
My::CBoardHolderInfo::CBoardHolderInfo(int nPriority) :CBoardHolder(nPriority)
{
	CJson::GetJson()->GetKarate(CJson::BOARDHOLDER_NUMBER)->PlusCreateobjCount();
}

//=============================================
// デストラクタ
//=============================================
My::CBoardHolderInfo::~CBoardHolderInfo()
{

}

//=============================================
// 初期化
//=============================================
HRESULT My::CBoardHolderInfo::Init()
{
	//初期化に失敗したとき
	if (FAILED(CBoardHolder::Init()))
	{
		return E_FAIL; //失敗を返す
	}
	CBoard* pBoard = nullptr;
	for (int i = 0; i < MAX; ++i)
	{
		switch (i)
		{
		case RIGHT:
			pBoard = CBoard::Create({ VEC3_RESET_ZERO },new CBoardNormal);
			pBoard->SetParent(GetModelParts(5));
			break;
		case LEFT:
			pBoard = CBoard::Create({OFFSET_X,FLOAT_ZERO,FLOAT_ZERO}, new CBoardNormal);
			pBoard->SetParent(GetModelParts(8));
			break;
		default:
			break;
		}
		pBoard->ConversionMtxWorld();
		PushBoard(pBoard);
	}
	return S_OK;
}

//=============================================
// 終了処理
//=============================================
void My::CBoardHolderInfo::Uninit()
{
	CGameManager::GetInstance()->GetGenerator()->SubHolder();

	if (CJson::GetJson() != nullptr)
	{
		//板持のカウントの調整関数を呼ぶ
		CJson::GetJson()->GetKarate(CJson::BOARDHOLDER_NUMBER)->AdjsutobjCount();

		//NOTE 同時に上限数分生成したい時は各この場所にゲージを増やす処理を追加する
		for (int nCount = 0; nCount < CJson::MAX_KARATEOBJ; nCount++)
		{
			CJson::GetJson()->GetKarate(nCount)->GetGage()++;
		}
	}

	CBoardHolder::Uninit();
}

//=============================================
// 更新処理
//=============================================
void My::CBoardHolderInfo::Update()
{
	CBoardHolder::Update();
}

//=============================================
// 描画処理
//=============================================
void My::CBoardHolderInfo::Draw()
{
	CBoardHolder::Draw();
}

//=============================================
// 割られた時の処理
//=============================================
void My::CBoardHolderInfo::BreakBoard()
{
	//板を割ってるように見せるため
	GetBoard(CBoardHolder::RIGHT)->SetRot(RIGHT_TURN);
	GetBoard(CBoardHolder::LEFT)->SetPos(VEC3_RESET_ZERO);
	GetBoard(CBoardHolder::LEFT)->SetRot(LEFT_TURN);
}

//===========================================================================================================================================
//瓦の情報処理
//===========================================================================================================================================

//=============================================
// コンストラクタ
//=============================================
My::CKawaraInfo::CKawaraInfo(int nPriority) :CBoardHolder(nPriority)
{
	CJson::GetJson()->GetKarate(CJson::KAWARA_NUMBER)->PlusCreateobjCount();
}

//=============================================
// デストラクタ
//=============================================
My::CKawaraInfo::~CKawaraInfo()
{

}

//=============================================
// 初期化
//=============================================
HRESULT My::CKawaraInfo::Init()
{
	//初期化に失敗したとき
	if (FAILED(CBoardHolder::Init()))
	{
		return E_FAIL; //失敗を返す
	}
	return S_OK;
}

//=============================================
// 終了処理
//=============================================
void My::CKawaraInfo::Uninit()
{
	CGameManager::GetInstance()->GetGenerator()->SubKawara();

	if (CJson::GetJson() != nullptr)
	{
		//板持のカウントの調整関数を呼ぶ
		CJson::GetJson()->GetKarate(CJson::KAWARA_NUMBER)->AdjsutobjCount();

		//NOTE 同時に上限数分生成したい時は各この場所にゲージを増やす処理を追加する
		for (int nCount = 0; nCount < CJson::MAX_KARATEOBJ; nCount++)
		{
			CJson::GetJson()->GetKarate(nCount)->GetGage()++;
		}
	}

	CBoardHolder::Uninit();
}

//=============================================
// 更新処理
//=============================================
void My::CKawaraInfo::Update()
{
	CBoardHolder::Update();
}

//=============================================
// 描画処理
//=============================================
void My::CKawaraInfo::Draw()
{
	CBoardHolder::Draw();
}

//===========================================================================================================================================
//罠持ちの情報処理
//===========================================================================================================================================

//=============================================
// コンストラクタ
//=============================================
My::CTrapHolderInfo::CTrapHolderInfo(int nPriority) :CBoardHolder(nPriority)
{
	CJson::GetJson()->GetKarate(CJson::TRAPHOLDER_NUMBER)->PlusCreateobjCount();
}

//=============================================
// デストラクタ
//=============================================
My::CTrapHolderInfo::~CTrapHolderInfo()
{

}

//=============================================
// 初期化
//=============================================
HRESULT My::CTrapHolderInfo::Init()
{
	//初期化に失敗したとき
	if (FAILED(CBoardHolder::Init()))
	{
		return E_FAIL; //失敗を返す
	}
	CBoard* pBoard = nullptr;

	pBoard = CBoard::Create({ OFFSET_X,FLOAT_ZERO,FLOAT_ZERO }, new CBoardDanger);
	pBoard->SetRot({-HALF_PI,FLOAT_ZERO,FLOAT_ZERO});
	pBoard->SetParent(GetModelParts(5));
	pBoard->ConversionMtxWorld();
	PushBoard(pBoard);
	return S_OK;
}

//=============================================
// 終了処理
//=============================================
void My::CTrapHolderInfo::Uninit()
{
	CGameManager::GetInstance()->GetGenerator()->SubTrap();

	if (CJson::GetJson() != nullptr)
	{
		//板持のカウントの調整関数を呼ぶ
		CJson::GetJson()->GetKarate(CJson::TRAPHOLDER_NUMBER)->AdjsutobjCount();

		//NOTE 同時に上限数分生成したい時は各この場所にゲージを増やす処理を追加する
		for (int nCount = 0; nCount < CJson::MAX_KARATEOBJ; nCount++)
		{
			CJson::GetJson()->GetKarate(nCount)->GetGage()++;
		}
	}
	CBoardHolder::Uninit();
}

//=============================================
// 更新処理
//=============================================
void My::CTrapHolderInfo::Update()
{
	CBoardHolder::Update();
}

//=============================================
// 描画処理
//=============================================
void My::CTrapHolderInfo::Draw()
{
	CBoardHolder::Draw();
}

//=============================================
// Hit_UIの作成
//=============================================
void My::CTrapHolderInfo::CreateHitUI()
{
	CHit_UI* hit_UI = GetHitUI();
	if (hit_UI == nullptr)
	{
		D3DXVECTOR3 screen_pos = ConvertToScreenPos(GET_CAMERA(GET_CAMERA_IDX), GetPos()); //スクリーン座標に変換

		hit_UI = CHit_UI::Create(screen_pos, 1);
		CGamePlayer* player = CGameManager::GetInstance()->GetPlayer();
		player->SetBoardHolder(this);
	}
	SetHitUI(hit_UI);
}