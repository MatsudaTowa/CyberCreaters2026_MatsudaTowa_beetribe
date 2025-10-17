//=============================================
//
//マウスカーソルのステートパターン[mouse_cursor_state.cpp]
//Author Matsuda Towa
//
//=============================================
#include "mouse_cursor_state.h"
#include "board_holder.h"
#include"camera.h"
#include"player.h"
#include "field.h"
#include "game_manager.h"
#include "game.h"
#include "mouse_trail_special.h"
#include "sound_bgm.h"
#include "sound_se.h"

//=============================================
// コンストラクタ
//=============================================
My::CNormalCursol::CNormalCursol()
{
}

//=============================================
// デストラクタ
//=============================================
My::CNormalCursol::~CNormalCursol()
{
}

//=============================================
// 通常処理
//=============================================
void My::CNormalCursol::Normal(CGameMouseCursor* mouse)
{
	if (GET_INPUT_MOUSE->GetPress(0))
	{
		//止めた事が無い時
		if (CSoundSE_000::m_boneflag == false)
		{
			CSoundSE_000::Zero();
			CSoundSE_000::m_boneflag = true; //止めたに変更
		}

		CGameState* state = CGameManager::GetInstance()->GetState();

		if (typeid(*state) == typeid(CSpecialWrite))
		{
			mouse->ChangeState(new CWriteCursol_Special);
			return;
		}

		CGamePlayer* player = CGameManager::GetInstance()->GetPlayer();
		D3DXVECTOR3 player_pos = ConvertToScreenPos(GET_CAMERA(GET_CAMERA_IDX), player->GetPos());

		// 開始位置をプレイヤーに
		SetCursorPos(player_pos.x, player_pos.y);
		mouse->SetPos(player_pos);
		mouse->ChangeState(new CWriteCursol_Normal);
	}
	else if (!GET_INPUT_MOUSE->GetPress(0))
	{
		//止めた事が有る時
		if (CSoundSE_000::m_boneflag == true)
		{
			CSoundSE_000::m_boneflag = false;    //止めてないに変更
		}
		if (CSoundBGM_000::m_nvolume < CSoundBGM_000::MAX_VOLUME)
		{
			CSoundBGM_000::m_nvolume += 2;
			CSoundBGM_000::volume(CSoundBGM_000::m_nvolume);
		}
	}

	D3DXVECTOR3 trail_pos = VEC3_RESET_ZERO;
	for (int nCnt = 0; nCnt < CObject::MAX_OBJECT; nCnt++)
	{
		CField* pField = CGameManager::GetInstance()->GetField();
#if 0
		if (GET_INPUT_MOUSE->GetTrigger(1))
		{
			D3DXVECTOR3 trail_pos = mouse->CursolWorldPoint(mouse->GetPos());

			CGamePlayer* player = CGameManager::GetInstance()->GetPlayer();


			//HACK: フリー移動の際は一個しか生成しないから削除も最初だけにしちゃってる
			player->EraseMovePoint(0);
			player->SetMovePoint(trail_pos);
		}
#else
		trail_pos = ConvertToWorldPoint(GET_CAMERA(GET_CAMERA_IDX), mouse->GetPos(), pField->GetPos());
	}

	CGamePlayer* player = CGameManager::GetInstance()->GetPlayer();

	//HACK: フリー移動の際は一個しか生成しないから削除も最初だけにしちゃってる
	CMovePoint* point = player->GetMovePoint(0);
	//if (GET_INPUT_MOUSE->GetPress(1))
	//{
	//	player->ChangeState(new CMovetoFreeState);
	//	if (point == nullptr)
	//	{
	//		player->SetMovePoint(trail_pos);
	//	}

	//	if (point != nullptr)
	//	{
	//		point->SetPos(trail_pos);
	//	}
	//}
	//if (GET_INPUT_MOUSE->GetRelease(1))
	//{
	//	if (point != nullptr)
	//	{
	//		player->ClearMovePoint();
	//		player->ChangeState(new CNeutralState);
	//	}
	//}
#endif
}

namespace WIRTE_FIXED
{
	int MAX_AMONT = 150;										//一回で描ける量
	int POINT_CREATE_FRAME = 5;									//移動ポイント生成フレーム
	float CREATE_DISTANCE = 10.0f;								//どれくらい離れたら生成するか
	D3DXVECTOR3 NORMAL_COLISION_SIZE = { 10.0f,0.0f,10.0f };	//通常コリジョンサイズ
	D3DXVECTOR3 TRAP_COLISION_SIZE = { 7.0f,0.0f,7.0f };		//トラップコリジョンサイズ
}

//=============================================
// コンストラクタ
//=============================================
My::CWriteCursol::CWriteCursol():
m_current_amont(INT_ZERO),				//現在の量初期化
m_create_num(INT_ZERO),					//生成数初期化
m_start_pos(VEC3_RESET_ZERO),			//開始位置初期化
m_create_frame(),						//フレーム初期化
m_pCreateCnt(nullptr)					//生成カウント初期化
{
	//量代入
	m_current_amont = WIRTE_FIXED::MAX_AMONT;
}

//=============================================
// デストラクタ
//=============================================
My::CWriteCursol::~CWriteCursol()
{
	m_create_frame.clear();
}

//=============================================
// 軌跡描画
//=============================================
void My::CWriteCursol::Write(CGameMouseCursor* mouse)
{
	int split = WIRTE_FIXED::MAX_AMONT / mouse->SPLIT;
	mouse->SetTexIdx(m_current_amont / split);
	if (m_pCreateCnt == nullptr)
	{
		m_pCreateCnt = new CCount;
	}
	CreateTrailPos(mouse);
}

//=============================================
//コンストラクタ
//=============================================
My::CWriteCursol_Normal::CWriteCursol_Normal()
{
}

//=============================================
//デストラクタ
//=============================================
My::CWriteCursol_Normal::~CWriteCursol_Normal()
{
}

//=============================================
//書く処理
//=============================================
void My::CWriteCursol_Normal::Write(CGameMouseCursor* mouse)
{
	CWriteCursol::Write(mouse);
}

//=============================================
//カーソルの軌跡生成
//=============================================
void My::CWriteCursol_Normal::CreateTrailPos(CGameMouseCursor* mouse)
{
	D3DXVECTOR3 trail_pos = VEC3_RESET_ZERO;

	CField* pField = CGameManager::GetInstance()->GetField();

	trail_pos = ConvertToWorldPoint(GET_CAMERA(GET_CAMERA_IDX), mouse->GetPos(), pField->GetPos());

	D3DXVECTOR3 field_size = pField->GetSize();
	if (trail_pos.x > field_size.x || trail_pos.x < -field_size.x
		|| trail_pos.z > field_size.z || trail_pos.z < -field_size.z)
	{//床の外での処理
		if (GET_INPUT_MOUSE->GetRelease(0))
		{
			CGamePlayer* player = CGameManager::GetInstance()->GetPlayer();
			mouse->SetTexIdx(mouse->SPLIT);

			//プレイヤーの描画を止める
			player->SetisDraw(false);
			mouse->ChangeState(new CWrittenCursol);
		}
		return;
	}

	int current_amont = GetAmont();

	if (GET_INPUT_MOUSE->GetPress(0))
	{
		//押されている時間計測
		GetCreateCnt()->CountMeasure();

		D3DXVECTOR3 start_pos = GetStartPos();

		if (current_amont == WIRTE_FIXED::MAX_AMONT)
		{//最初に押された際に始点を保存
			start_pos = trail_pos;

			SetStartPos(start_pos);
		}
		if (current_amont > 0)
		{
			if (GET_INPUT_MOUSE->GetMouseMove().x == 0.0f
				&& GET_INPUT_MOUSE->GetMouseMove().y == 0.0f)
			{
				return;
			}

			--current_amont;

			SetAmont(current_amont);

			//軌跡生成ポイントを計算し生成
			GenerateInterpolatedPos(mouse, trail_pos);

			for (int nCnt = 0; nCnt < CObject::MAX_OBJECT; nCnt++)
			{
				//オブジェクト取得
				CObject* pObj = CObject::Getobject(CBoardHolder::PRIORITY, nCnt);
				if (pObj == nullptr)
				{//ヌルポインタなら
					//オブジェクトを探し続ける
					continue;
				}
				//タイプ取得
				CObject::OBJECT_TYPE type = pObj->GetType();

				if (type != CObject::OBJECT_TYPE::OBJECT_TYPE_BOARD_HORDER)
				{//プレイヤーじゃなければ
					//プレイヤーを探し続ける
					continue;
				}
				CBoardHolder* pBoardHorder = dynamic_cast<CBoardHolder*>(pObj);

				float radius = FLOAT_ZERO;
				if (typeid(*pBoardHorder) == typeid(CTrapHolderInfo))
				{
					// 対角線の長さを求めてから半径にする
					radius = 0.5f * sqrtf(WIRTE_FIXED::TRAP_COLISION_SIZE.x * WIRTE_FIXED::TRAP_COLISION_SIZE.x + WIRTE_FIXED::TRAP_COLISION_SIZE.z * WIRTE_FIXED::TRAP_COLISION_SIZE.z);
				}
				else
				{
					// 対角線の長さを求めてから半径にする
					radius = 0.5f * sqrtf(WIRTE_FIXED::NORMAL_COLISION_SIZE.x * WIRTE_FIXED::NORMAL_COLISION_SIZE.x + WIRTE_FIXED::NORMAL_COLISION_SIZE.z * WIRTE_FIXED::NORMAL_COLISION_SIZE.z);
				}

				CColision::CIRCLE circle = GET_COLISION->CheckColisionCircle(trail_pos, radius, pBoardHorder->GetPos());

				if (!circle.colision)
				{
					continue;
				}

				pBoardHorder->CreateHitUI();
			};
		}
	}

	if ((GET_INPUT_MOUSE->GetRelease(0) || current_amont / (WIRTE_FIXED::MAX_AMONT / mouse->SPLIT) <= 0))
	{//マウスを離すか、インクの上限に到達したとき

		CGamePlayer* player = CGameManager::GetInstance()->GetPlayer();
		mouse->SetTexIdx(mouse->SPLIT);

		//プレイヤーの描画を止める
		player->SetisDraw(false);
		mouse->ChangeState(new CWrittenCursol);
		return;
	}
}

//=============================================
//線形補間し途切れないように生成
//=============================================
void My::CWriteCursol_Normal::GenerateInterpolatedPos(CGameMouseCursor* mouse, D3DXVECTOR3& trail_pos)
{
	D3DXVECTOR3 start_pos = GetStartPos();
	//対象の位置への方向情報
	D3DXVECTOR3 point = { start_pos.x - trail_pos.x,start_pos.y - trail_pos.y,start_pos.z - trail_pos.z };

	float length = sqrtf(point.x * point.x + point.z * point.z);

	if (length >= WIRTE_FIXED::CREATE_DISTANCE)
	{
		//必要な補間の点の数を算出
		int steps = (int)(length / WIRTE_FIXED::CREATE_DISTANCE);

		for (int i = 0; i < steps; ++i)
		{
			//開始の点の次の点から割合算出
			float t = (i + 1) / (float)(steps);

			//線形補間
			D3DXVECTOR3 interp_pos;
			D3DXVec3Lerp(&interp_pos, &start_pos, &trail_pos, t);

			//ポイントを生成
			CMouseTrailPoint* pPoint = CMouseTrailPoint::Create(interp_pos);
			if (pPoint != nullptr)
			{
				mouse->SetTrailPoint(pPoint);

				////生成までかかったフレーム数保持
				//SetCreat.push_back(m_pCreateCnt->GetCnt());
				//m_pCreateCnt->SetCnt(0);
			}
		}
		//開始位置を今の位置に変更
		start_pos = trail_pos;

		SetStartPos(start_pos);
	}
}

const D3DXVECTOR3 My::CWriteCursol_Special::TRAIL_CREATE_MIN_POS = { -5.0f,0.0f,-5.0f };	//生成する最小位置
const D3DXVECTOR3 My::CWriteCursol_Special::TRAIL_CREATE_MAX_POS = { 5.0f,0.0f,5.0f };	//生成する最大位置

//=============================================
//コンストラクタ
//=============================================
My::CWriteCursol_Special::CWriteCursol_Special()
{
	SetAmont(SPECIAL_AMONT);
	m_pTrail.clear();
}

//=============================================
//デストラクタ
//=============================================
My::CWriteCursol_Special::~CWriteCursol_Special()
{
	for (auto& itr : m_pTrail)
	{
		if (itr == nullptr)
		{
			continue;
		}
		itr->Uninit();
		itr = nullptr;
	}
	m_pTrail.clear();
}

//=============================================
//書く処理
//=============================================
void My::CWriteCursol_Special::Write(CGameMouseCursor* mouse)
{
	CWriteCursol::Write(mouse);
	for (auto& itr : m_pTrail)
	{
		if (itr == nullptr)
		{
			continue;
		}
		itr->SetStop(false);
	}
}

//=============================================
//カーソルの軌跡生成
//=============================================
void My::CWriteCursol_Special::CreateTrailPos(CGameMouseCursor* mouse)
{
	D3DXVECTOR3 trail_pos = VEC3_RESET_ZERO;
	D3DXVECTOR3 mouse_pos = mouse->GetPos();

	CField* pField = CGameManager::GetInstance()->GetField();
	trail_pos = ConvertToWorldPoint(GET_CAMERA(GET_CAMERA_IDX), mouse_pos, pField->GetPos());
	
	CPaper* pPaper = CGameManager::GetInstance()->GetPaper();

	D3DXVECTOR2 paper_size = pPaper->GetSize();
	D3DXVECTOR3 paper_pos = pPaper->GetPos();

	if (mouse_pos.x > paper_pos.x + paper_size.x || mouse_pos.x < paper_pos.x - paper_size.x
		|| mouse_pos.y > paper_pos.y + paper_size.y || mouse_pos.y < paper_pos.y - paper_size.y)
	{//紙の外での処理
		if (GET_INPUT_MOUSE->GetRelease(0))
		{
			CGameManager::GetInstance()->ChangeState(new CSpecialAttack);

			mouse->ChangeState(new CNormalCursol);
		}
		return;
	}

	int current_amont = GetAmont();

	if (GET_INPUT_MOUSE->GetPress(0))
	{
		//押されている時間計測
		GetCreateCnt()->CountMeasure();

		D3DXVECTOR3 start_pos = GetStartPos();

		if (current_amont == SPECIAL_AMONT)
		{//最初に押された際に始点を保存
			start_pos = trail_pos;

			SetStartPos(start_pos);
		}
		if (current_amont > 0)
		{
			if (GET_INPUT_MOUSE->GetMouseMove().x == 0.0f
				&& GET_INPUT_MOUSE->GetMouseMove().y == 0.0f)
			{
				return;
			}

			--current_amont;

			SetAmont(current_amont);

			//軌跡生成ポイントを計算し生成
			GenerateInterpolatedPos(mouse, trail_pos);
		}
	}

	if (((GET_INPUT_MOUSE->GetRelease(0) || current_amont / (SPECIAL_AMONT / mouse->SPLIT) <= 0))&& m_pTrail.size() > INT_ZERO)
	{//マウスを離すか、インクの上限に到達したときで何か描いていたら
		CGameManager::GetInstance()->ChangeState(new CSpecialAttack);

		mouse->ChangeState(new CNormalCursol);
		return;
	}
}

//=============================================
//線形補間し途切れないように生成
//=============================================
void My::CWriteCursol_Special::GenerateInterpolatedPos(CGameMouseCursor* mouse, D3DXVECTOR3& trail_pos)
{
	for (int j = 0; j < TRAIL_CREATE_NUM * 0.5f; ++j)
	{
		float x = 0.0f;
		float z = 0.0f;
		x = Rundom(TRAIL_CREATE_MIN_POS.x, TRAIL_CREATE_MAX_POS.x);
		z = Rundom(TRAIL_CREATE_MIN_POS.z, TRAIL_CREATE_MAX_POS.z);
		CMouseTrail* trail = CMouseTrail::Create({ trail_pos.x + x,trail_pos.y,trail_pos.z + z }, new CMouseTrail_Special);
		m_pTrail.push_back(trail);
	}
}

//=============================================
// コンストラクタ
//=============================================
My::CPauseCursol::CPauseCursol()
{
}

//=============================================
// デストラクタ
//=============================================
My::CPauseCursol::~CPauseCursol()
{
}

//=============================================
// ポーズ処理
//=============================================
void My::CPauseCursol::Pause(CGameMouseCursor* mouse)
{
	//TODO: ポーズのUIとの判定をここに
}

//=============================================
// コンストラクタ
//=============================================
My::CWrittenCursol::CWrittenCursol():m_pTrailCreateCnt(nullptr)				//カウント初期化
{
	//ヒットUI削除
	CGamePlayer* player = CGameManager::GetInstance()->GetPlayer();
	for (int i = 0; i < player->GetBoardHolderSize(); ++i)
	{
		CBoardHolder* board_holder = player->GetBoardHolder(i);
		if (board_holder->GetHitUI() == nullptr)
		{
			continue;
		}

		board_holder->GetHitUI()->Uninit();
		board_holder->SetHitUI(nullptr);
	}

	//コンボUI削除
	CCombo* pCombo = player->GetComboUI();
	if (pCombo != nullptr)
	{
		pCombo->SetisDelete(true);
	}
	player->SetComboUI(pCombo);
}

//=============================================
// デストラクタ
//=============================================
My::CWrittenCursol::~CWrittenCursol()
{
	if (m_pTrailCreateCnt != nullptr)
	{
		delete m_pTrailCreateCnt;
		m_pTrailCreateCnt = nullptr;
	}
}

//=============================================
// 描き終えた処理
//=============================================
void My::CWrittenCursol::Written(CGameMouseCursor* mouse)
{
	if (m_pTrailCreateCnt == nullptr)
	{
		m_pTrailCreateCnt = new CCount;
	}

#if 0
	//それぞれにかかった時間ごとに生成 TODO:Wirteから値を参照
	m_pCreateCnt->SetFrame(m_CreateFrame.at(m_create_num));
#else
	//それぞれにかかった時間ごとに生成 TODO; 0にするんじゃなくてタイムスケールでスピード変更
	m_pTrailCreateCnt->SetFrame(0);
#endif

	bool is_Create = m_pTrailCreateCnt->CountUp();
	if (is_Create)
	{
		CMouseTrailPoint* point = mouse->GetTrailPoint(0);

		if (point != nullptr)
		{
			bool retflag;

			//到達したらfalseが返ってくる
			PlayerSetPos(point, retflag);
			if (retflag)
			{
				return;
			}
			point->CreateTrail();

		}

		mouse->EraseTrailPoint(0);

		m_pTrailCreateCnt->SetCnt(0);
	}

	if (mouse->GetTrailPointSize() <= 0)
	{
		CGamePlayer* player = CGameManager::GetInstance()->GetPlayer();
		player->SetisDraw(true);
		if (player->GetBoardHolderSize() > 0)
		{
			player->ChangeState(new CAttackState);
			return;
		}
		SET_CAMERA_IDX(CGame::GAME_CAMERA);

		//コンボ設定
		CCombo* pCombo = player->GetComboUI();

		if (pCombo != nullptr)
		{
			pCombo->SetNumCombo(INT_ZERO);
			pCombo->SetisDelete(true);
		}
		player->SetComboUI(pCombo);

		mouse->ChangeState(new CNormalCursol);
	}
}

//=============================================
//プレイヤーを軌跡の場所に
//=============================================
void My::CWrittenCursol::PlayerSetPos(CMouseTrailPoint* point, bool& retflag)
{
	if (CSoundBGM_000::m_nvolume > 0)
	{
		CSoundBGM_000::m_nvolume -= 5;
		CSoundBGM_000::volume(CSoundBGM_000::m_nvolume);
	}

	retflag = true;
	CGamePlayer* player = CGameManager::GetInstance()->GetPlayer();

	//プレイヤーの位置への方向情報
	D3DXVECTOR3 PointVector = point->GetPos() - player->GetPos();
	// 目的地との距離を計算
	float point_distance = sqrtf(PointVector.x * PointVector.x + PointVector.z * PointVector.z);

	if (player->GetBoardHolderSize() > 0)
	{
		CBoardHolder* holder = player->GetBoardHolder(0);

		D3DXVECTOR3 colision_size = { WIRTE_FIXED::NORMAL_COLISION_SIZE.x + 0.5f,WIRTE_FIXED::NORMAL_COLISION_SIZE.y,WIRTE_FIXED::NORMAL_COLISION_SIZE.z + 0.5f };

		// 対角線の長さを求めてから半径にする
		float radius = 0.5f * sqrtf(colision_size.x * colision_size.x + colision_size.z * colision_size.z);

		CColision::CIRCLE circle = GET_COLISION->CheckColisionCircle(player->GetPos(), radius, holder->GetPos());

		if (circle.colision)
		{
			//プレイヤーの描画を許可
			//player->SetisDraw(true);
			//player->SetMove(VEC3_RESET_ZERO);
			player->ChangeState(new CAttackState);
			return;
		}
	}

	if (typeid(*player->GetState()) != typeid(CAttackState))
	{
		//プレイヤーの描画を止める
		player->SetisDraw(false);
		//対象物との角度計算
		float angle = atan2f(PointVector.x, PointVector.z);

		D3DXVECTOR3 move = player->GetMove();

		//閾値とスピードは調整
		bool isReached = isTargetReached(30.0f, player->GetSpeed() * 5.0f, angle, point_distance, move);

		player->SetMove(move);

		D3DXVECTOR3 rot = player->GetRot();
		rot.y = angle + D3DX_PI;
		player->SetRot(rot);

		if (!isReached)
		{
			return;
		}

		retflag = false;
	}
}
