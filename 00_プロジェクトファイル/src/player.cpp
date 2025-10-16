//=============================================
//
//プレイヤー[player.cpp]
//Author Matsuda Towa
//
//=============================================
#include "player.h"
#include "manager.h"
#include "input.h"
#include "block.h"
#include "field.h"
#include "camera.h"
#include "game.h"
#include "smoke_grenade.h"
#include "camera_state.h"

//スポーン位置
const D3DXVECTOR3 CPlayer::PLAYER_SPAWN_POS = { 0.0f, 0.5f, -400.0f };

//スポーン方向
const D3DXVECTOR3 CPlayer::PLAYER_SPAWN_ROT = { 0.0f, 3.14f, 0.0f};

//影のサイズ
const D3DXVECTOR3 CPlayer::SHADOW_SIZE = { 20.0f, 0.0, 20.0f };

//=============================================
//コンストラクタ
//=============================================
CPlayer::CPlayer(int nPriority) :CCharacter(nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CPlayer::~CPlayer()
{
}

//=============================================
//初期化
//=============================================
HRESULT CPlayer::Init()
{
	CCharacter::Init();

	SetPos(PLAYER_SPAWN_POS); //pos設定
	SetRot(PLAYER_SPAWN_ROT); //rot設定

	//カメラ情報取得
	CCamera* pCamera = CManager::GetInstance()->GetCamera();

	//移動量初期化
	D3DXVECTOR3 move = VEC3_RESET_ZERO;

	pCamera->SetRot(VEC3_RESET_ZERO);

	//ムーブ値代入
	SetMove(move);

	//初期モーション設定
	SetMotion(MOTION_NEUTRAL);

	//影のサイズ設定
	SetShadowSize(SHADOW_SIZE);

	return S_OK;
}

//=============================================
//終了
//=============================================
void CPlayer::Uninit()
{
	//親クラスの終了処理を呼ぶ
	CCharacter::Uninit();
}

//=============================================
//更新
//=============================================
void CPlayer::Update()
{
	CCharacter::Update();

	for (int nCnt = 0; nCnt < GetNumParts(); nCnt++)
	{
		m_apModel[nCnt]->SetOldPos(m_apModel[nCnt]->GetPos());
	}

	Motion(); //モーション処理
	//CCharacter::HitBlock(NUM_PARTS);
}

//=============================================
//描画
//=============================================
void CPlayer::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	// デバイスのポインタ
	// ステンシルテストを有効にする
	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);
	// 比較参照値を設定する
	pDevice->SetRenderState(D3DRS_STENCILREF, 1);
	// ステンシルマスクを指定する
	pDevice->SetRenderState(D3DRS_STENCILMASK, 255);
	// ステンシル比較関数を指定する
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
	// ステンシル結果に対しての反映設定
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);	// Zテスト・ステンシルテスト成功
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);		// Zテスト・ステンシルテスト失敗
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);		// Zテスト失敗・ステンシルテスト成功

	//親クラスのモーション用の描画を呼ぶ
	MotionDraw();
	// ステンシルテストを無効にする
	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
	//プレイヤーのデバッグ表示
	DebugPos();
}

//=============================================
//生成
//=============================================
CPlayer* CPlayer::Create(CPlayer* player)
{
	CPlayer* pPlayer = player;

	// nullならnullを返す
	if (pPlayer == nullptr) { return nullptr; }

		//パーツ読み込み
	pPlayer->Load_Parts("data\\motion_soldier.bin");

	pPlayer->Init(); //初期化処理

	pPlayer->SetType(OBJECT_TYPE_PLAYER); //タイプ設定

	return pPlayer;
}

//=============================================
//プレイヤーのデバッグ表示
//=============================================
void CPlayer::DebugPos()
{
#ifdef _DEBUG
	LPD3DXFONT pFont = CManager::GetInstance()->GetRenderer()->GetFont();
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	sprintf(&aStr[0], "\n\n[player]\npos:%.1f,%.1f,%.1f\nrot:%.1f,%.1f,%.1f\nmove:%.1f,%.1f,%.1f"
		, GetPos().x, GetPos().y, GetPos().z, GetRot().x, GetRot().y, GetRot().z, GetMove().x, GetMove().y, GetMove().z);
	//テキストの描画
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 0, 0, 255));
#endif // _DEBUG
}
