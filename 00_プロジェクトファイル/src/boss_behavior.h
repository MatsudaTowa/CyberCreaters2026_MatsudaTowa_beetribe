//=============================================
//
//ボスのストラテジーパターン[boss_behavior.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _BOSS_BEHAVIOR_
#define _BOSS_BEHAVIOR_
#include "enemy_behavior.h"
#include "boss_enemy.h"
#include "move_point.h"
#include "enemy_reaction_UI.h"

//=============================================
//前方宣言
//=============================================
class CBossEnemy;

//=============================================
//敵の徘徊のストラテジー
//=============================================
class CBossWandering
{
public:
	/**
	 * @brief コンストラクタ
	 */
	CBossWandering();
	/**
	 * @brief デストラクタ
	 */
	~CBossWandering();
	/**
	 * @brief 徘徊処理
	 * @param [in]ボスのポインタ
	 */
	void Wandering(CBossEnemy* boss);

	/**
	 * @brief デバッグ表示
	 */
	void DrawDebug(); 
private:
	static const int STOP_FRAME = 30;	//止まってるフレーム数

	static constexpr float THRESHOLD = 0.5f; // 距離が定数以下なら到達とする（必要に応じて調整）
	/**
	 * @brief 止まってる時間計測
	 */
	void StopCnt();
	/**
	 * @brief 次の移動ポイント抽選
	 * @param [in]移動ポイント
	 */
	void PickNextMovePoint(CMovePoint* pMovePoint);

	int m_MoveIdx; //移動先の番号
	int m_StopCnt; //止まってるカウント
	bool m_isMove; //動くかどうか
};

//=============================================
//敵の追従のストラテジー
//=============================================
class CBossChase
{
public:
	/**
	 * @briefコンストラクタ
	 */
	CBossChase();
	/**
	 * @brief デストラクタ
	 */
	~CBossChase();
	/**
	 * @brief 追いかけ処理
	 * @param [in]ボスのポインタ
	 * @param [in]追いかけ対象のオブジェクト
	 */
	void Chase(CBossEnemy* boss, CObject* obj);
	/**
	 * @brief デバッグ表示
	 */
	void DrawDebug();
private:
	static constexpr float THRESHOLD = 200.0f; // 距離が定数以下なら到達とする（必要に応じて調整）
	/**
	 * @brief プレイヤーに向かって動く
	 * @param [in]距離
	 * @param [in]到達閾値
	 * @param [in]Vector
	 * @param boss
	 */
	void MovetoPlayer(float distance, const float threshold, D3DXVECTOR3 Vector, CBossEnemy* boss);

	BOOL m_bTargetPlayer;		//レイが当たってたらtrueにしプレイヤーを追いかける
};

//=============================================
//混乱のストラテジー
//=============================================
class CBossConfusion
{
public:
	/**
	 * @brief コンストラクタ
	 */
	CBossConfusion();
	/**
	 * @brief デストラクタ
	 */
	~CBossConfusion();
	/**
	 * @brief 混乱処理
	 * @param [in]ボスのポインタ
	 * @param [in]方向の開始位置
	 */
	void Confusion(CBossEnemy* boss, float StartRot_y);

	CCharacter::RayHitInfo PerformRaycast_Player(D3DXVECTOR3 vector,CBossEnemy* boss);
private:
	static constexpr float LOOK_RANGE = 1.6f; //見渡す範囲
	static constexpr float ROT_MOVE = 0.01f; //見渡す移動値
	static constexpr float CORRECTION_VALUE_Y = 20.0f; //レイを飛ばすYの補正値
	static constexpr int NUM_TURN = 2; //見渡す回数
	/**
	 * @brief 方向の移動
	 * @param [in][out]方向
	 * @param [in]到達位置
	 * @param [in]ボスのポイント
	 */
	void MoveRot(D3DXVECTOR3& rot, float Rot_Answer_y, CBossEnemy* boss);
	int m_TurnCnt; //何回見渡したか
	bool m_isRight; //見渡す(true:右 false:左)
};

//=============================================
//敵の銃の攻撃のストラテジー
//=============================================
class CBossGunAttack : public CEnemyGunAttack
{
public:
	/**
	 * @brief コンストラクタ
	 */
	CBossGunAttack();
	/**
	 * @brief デストラクタ
	 */
	~CBossGunAttack() override;

	/**
	 * @brief 銃の攻撃
	 * @param [in]どっちの弾か
	 * @param [in]キャラクターのポインタ
	 */
	void GunAttack(CBullet::BULLET_ALLEGIANCE Allegiance, CCharacter* character) override;

private:
	static const int SHOT_STATE_FRAME = 90; //射撃フレーム
	static constexpr float CORRECTION_Y = 5.0f; //yの補正値

	int m_nStateChangeCnt;//ステート変更カウント
};

//=============================================
//突進攻撃のストラテジー
//=============================================
class CBossTackle
{
public:
	static const int TACKLE_DAMAGE = 30;
	/**
	 * @brief コンストラクタ
	 */
	CBossTackle();
	/**
	 * @brief デストラクタ
	 */
	~CBossTackle();
	/**
	 * @brief タックル
	 * @param [in]ボスのポインタ
	 */
	void Tackle(CBossEnemy* boss);

private:
	static const int STAY_FLAME = 180; //突進までの待機時間
	static const int CORRECTION_FLAME = 15; //エフェクトと合わせるとずれるのでフレームを補正
	static const int TACKLE_FLAME = 60; //タックル時間
	static constexpr float CORRECTION_VALUE_Y = 50.0f; //タックルエフェクトを生成する際のYの補正値

	/**
	 * @brief プレイヤーのほうを向かせる
	 * @param [in]キャラクターポインタ
	 */
	void LookAtPlayer(CCharacter* character);
	int m_StayCnt;				//とどまるカウント
	int m_TackleCnt;			//タックル継続カウント
	bool m_isTackle;			//タックルするかどうか
	float m_effect_reduction;	//エフェクトのサイズ縮小
};

//=============================================
//探索のストラテジー
//=============================================
class CBossSearch
{
public:
	/**
	 * @brief コンストラクタ
	 */
	CBossSearch();
	/**
	 * @brief デストラクタ
	 */
	~CBossSearch();
	/**
	 * @brief 探索
	 * @param [in]ボスポインタ
	 * @param [in]目標の位置
	 */
	void Search(CBossEnemy* boss,D3DXVECTOR3 TargetPos);
private:
	static constexpr float THRESHOLD = 0.5f; // 距離が定数以下なら到達とする（必要に応じて調整）

};

//=============================================
//暴走のストラテジー
//=============================================
class CBossRampage
{
public:
	/**
	 * @brief コンストラクタ
	 */
	CBossRampage();
	/**
	 * @brief デストラクタ
	 */
	~CBossRampage();
	/**
	 * @brief 暴走
	 * @param [in]ボスポインタ
	 */
	void Rampage(CBossEnemy* boss);
private:
	static const int NUM_TARGETPOINT = 4; //外周のポイント数
	static const int NUM_RAPS = 3; //何周するか
	static constexpr float THRESHOLD = 5.5f; // 距離が定数以下なら到達とする（必要に応じて調整）
	static const int OUTER_CIRCUMFERENCE[NUM_TARGETPOINT]; //外周の番号
	int m_MoveIdx; //移動先の番号
	int m_LapCnt; //何周したかのカウント
};
#endif // !_ENEMY_BEHAVIOR_
