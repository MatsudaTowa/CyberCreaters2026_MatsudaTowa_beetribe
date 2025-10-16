//=============================================
//
//ボスのステートパターン[boss_state.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _BOSS_STATE_H_
#define _BOSS_STATE_H_

#include "character_state.h"
#include "boss_enemy.h"

//=============================================
//前方宣言
//=============================================
class CBossEnemy;

//=============================================
//ボスのステートクラス
//=============================================
class CBossState
{
public:
	/**
	 * @brief コンストラクタ
	 */
	CBossState() {};
	/**
	 * @brief デストラクタ
	 */
	virtual ~CBossState() {};
	/**
	 * @brief 最初に呼ばれる関数
	 * @param ボスのポインタ
	 */
	virtual void Start([[maybe_unused]] CBossEnemy* boss) {};
	/**
	 * @brief 最後に呼ばれる関数
	 * @param ボスのポインタ
	 */
	virtual void End([[maybe_unused]] CBossEnemy* boss) {};
	/**
	 * @brief 追跡
	 * @param ボスのポインタ
	 */
	virtual void Chase([[maybe_unused]] CBossEnemy* boss) {};
	/**
	 * @brief スタン
	 * @param ボスのポインタ
	 */
	virtual void Stan([[maybe_unused]] CBossEnemy* boss) {};
	/**
	 * @brief 徘徊
	 * @param ボスのポインタ
	 */
	virtual void Wandering([[maybe_unused]] CBossEnemy* boss) {};
	/**
	 * @brief 混乱
	 * @param ボスのポインタ
	 */
	virtual void Confusion([[maybe_unused]] CBossEnemy* boss) {};
	/**
	 * @brief タックル
	 * @param ボスのポインタ
	 */
	virtual void Tackle([[maybe_unused]] CBossEnemy* boss) {};
	/**
	 * @brief 探索
	 * @param ボスのポインタ
	 */
	virtual void Search([[maybe_unused]] CBossEnemy* boss) {};
	/**
	 * @brief 暴走
	 * @param ボスのポインタ
	 */
	virtual void Rampage([[maybe_unused]] CBossEnemy* boss) {};
	/**
	 * @brief デバッグ表示
	 */
	virtual void DrawDebug() {};
};

//=============================================
//エネミーの追跡状態
//=============================================
class CChaseState : public CBossState
{
public:
	/**
	 * @brief コンストラクタ
	 */
	CChaseState();
	/**
	 * @brief デストラクタ
	 */
	~CChaseState() override;
	/**
	 * @brief 追跡
	 * @param ボスのポインタ
	 */
	virtual void Chase(CBossEnemy* boss)override;
	/**
	 * @brief デバッグ表示
	 */
	virtual void DrawDebug()override;
private:
	static const int PLAY_TACKLE_FLAME = 300; //タックルを実行するまでのフレーム
	int m_PlayTackleCnt; //タックルまでの計測用
};

//=============================================
//エネミーのスタン状態
//=============================================
class CBossStanState :public CBossState
{
public:
	/**
	 * @brief 最初
	 * @param ボスのポインタ
	 */
	void Start([[maybe_unused]] CBossEnemy* boss) override;
	/**
	 * @brief 最後に呼ばれる関数
	 * @param ボスのポインタ
	 */
	void End([[maybe_unused]] CBossEnemy* boss) override;
	/**
	 * @brief スタン
	 * @param ボスのポインタ
	 */
	virtual void Stan(CBossEnemy* boss);
	/**
	 * @brief デバッグ表示
	 */
	virtual void DrawDebug()override;
private:
	static const int STAN_FRAME = 180; //スタン時間
	int m_StanCnt; //スタン計測カウント
};

//=============================================
//エネミーの徘徊状態
//=============================================
class CWanderingState : public CBossState
{
public:
	/**
	 * @brief コンストラクタ
	 */
	CWanderingState();
	/**
	 * @brief デストラクタ
	 */
	~CWanderingState() override;
	/**
	 * @brief 徘徊
	 * @param ボスのポインタ
	 */
	virtual void Wandering(CBossEnemy* boss)override;
	/**
	 * @brief デバッグ表示
	 */
	virtual void DrawDebug()override;
private:
	static const int TRANSITION_FRAME = 60;
	int m_TransitionCnt;		//ステートが移り変わる猶予カウント
	bool m_bDamage;				//ダメージ食らったか
	D3DXVECTOR3 m_TargetRot;	//目的の方向
};

//=============================================
//エネミーの混乱状態
//=============================================
class CConfusionBossState : public CBossState
{
public:
	/**
	 * @brief コンストラクタ
	 */
	CConfusionBossState();
	/**
	 * @brief デストラクタ
	 */
	~CConfusionBossState() override;
	/**
	 * @brief 最初
	 * @param ボスのポインタ
	 */
	void Start(CBossEnemy* boss) override;
	/**
	 * @brief 混乱
	 * @param ボスのポインタ
	 */
	virtual void Confusion(CBossEnemy* boss)override;
	/**
	 * @brief デバッグ表示
	 */
	virtual void DrawDebug()override;
private:
	static constexpr float CORRECTION_VALUE = 70.0f; //リアクションのUIを生成する際のYの補正値
	static const D3DXVECTOR3 SIZE; //リアクションのUIのサイズ

	float m_StartRot;
	bool m_isRight; //見渡す(true:右 false:左)
	CEnemy_Reaction_UI* m_pReaction;
};

//=============================================
//エネミーのタックル状態
//=============================================
class CTackleState : public CBossState
{
public:
	/**
	 * @brief コンストラクタ
	 */
	CTackleState();
	/**
	 * @brief デストラクタ
	 */
	~CTackleState() override;
	/**
	 * @brief 最初
	 * @param ボスのポインタ
	 */
	void Start([[maybe_unused]] CBossEnemy* boss) override;
	/**
	 * @brief 終了
	 * @param ボスのポインタ
	 */
	void End(CBossEnemy* boss) override;
	/**
	 * @brief タックル
	 * @param ボスのポインタ
	 */
	virtual void Tackle(CBossEnemy* boss)override;
	/**
	 * @brief デバッグ表示
	 */
	virtual void DrawDebug()override;
};

//=============================================
//エネミーのプレイヤーを探す状態
//=============================================
class CSearchState : public CBossState
{
public:
	/**
	 * @brief 最初
	 * @param ボスのポインタ
	 */
	void Start([[maybe_unused]] CBossEnemy* boss) override;
	/**
	 * @brief 探索
	 * @param ボスのポインタ
	 */
	virtual void Search(CBossEnemy* boss)override;
	/**
	 * @brief デバッグ表示
	 */
	virtual void DrawDebug()override;
private:
	D3DXVECTOR3 m_TargetPos;
};

//=============================================
//エネミーの暴走状態
//=============================================
class CRampageState : public CBossState
{
public:
	/**
	 * @brief 最初
	 * @param [in]ボスのポインタ
	 */
	void Start(CBossEnemy* boss) override;
	/**
	 * @brief 終了
	 * @param [in]ボスのポインタ
	 */
	void End(CBossEnemy* boss) override;
	/**
	 * @brief 暴走
	 * @param [in]ボスのポインタ
	 */
	virtual void Rampage(CBossEnemy* boss)override;
	/**
	 * @brief デバッグ表示/
	 */
	virtual void DrawDebug()override;
};
#endif