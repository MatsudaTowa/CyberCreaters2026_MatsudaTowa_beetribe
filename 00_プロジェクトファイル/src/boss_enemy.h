//=============================================
//
//ボスの敵の処理[boss_enemy.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _BOSS_ENEMY_H_ //これが定義されてないとき

#define _BOSS_ENEMY_H_
#include "main.h"
#include "model_parts.h"
#include "enemy.h"
#include "enemy_behavior.h"
#include "boss_behavior.h"
#include "boss_state.h"
#include "active_player.h"
#include "dash_effect.h"
#include "tackle_charge.h"

//=============================================
//前方宣言
//=============================================
class CBossChase;
class CBossWandering;
class CBossConfusion;
class CBossTackle;
class CBossSearch;
class CBossRampage;
class CBossState;

//=============================================
//ボスのエネミークラス
//=============================================
class CBossEnemy :public CEnemy
{
public:
	static const int MAX_KEY = 20; //キー最大数
	static const int NUM_MOTION = 3;
	static const int ENEMY_PRIORITY = 8; //描画順
	static const int DEFAULT_LIFE = 1500; //ライフ
	static const int LOW_HP = DEFAULT_LIFE / 3; //体力が低い
	static constexpr float FIND_PLAYER_DISTANCE = 300.0f; //この値までだったら追いかける
	static constexpr float LOST_PLAYER_DISTANCE = 100.0f; //この値以上だったら見失う

	//モーションの種類の列挙
	enum Motion_Type
	{
		MOTION_NEUTRAL = 0,
		MOTION_MOVE,
		MOTION_ATTACK,
		MOTION_STAN,
		MOTION_TACKLE,
		MOTION_MAX,
	};

	/**
	 * @brief コンストラクタ
	 * @param [in]プライオリティ
	 */
	CBossEnemy(int nPriority = ENEMY_PRIORITY);

	/**
	 * @brief デストラクタ
	 */
	~CBossEnemy() override;
	/**
	 * @brief 初期化
	 * @return 成功したか
	 */
	HRESULT Init() override;
	/**
	 * @brief 終了
	 */
	void Uninit() override;
	/**
	 * @brief 更新
	 */
	void Update() override;
	/**
	 * @brief 描画
	 */
	void Draw() override;
	/**
	 * @brief ステート変更
	 * @param ボスの次のステート
	 */
	void ChangeState(CBossState* state);
	/**
	 * @brief タックルの実行処理
	 */
	void TackleAction();
	/**
	 * @brief プレイヤーとの判定
	 */
	void ColisionPlayer();
	/**
	 * @brief プレイヤーとのヒット判定
	 * @param [in]プレイヤーのポインタ
	 * @param [in]パーツの数
	 * @param [in]位置
	 * @param [in]最大の頂点座標
	 * @param [in]最小の頂点座標
	 */
	void CheckColisionPlayer(CActivePlayer* pPlayer, const D3DXVECTOR3 pos, const D3DXVECTOR3 Minpos, const D3DXVECTOR3 Maxpos);
	/**
	 * @brief ウルトヒット処理
	 * @param [in]ウルトの座標
	 * @param [in]ダメージ数
	 */
	void MediumUltHit(D3DXVECTOR3 UltPos, int nDamage)override;
	/**
	 * @brief ブロックとのヒット判定(複数パーツ)
	 * @param [in]ダメージ数
	 */
	void HitBlock(int NumParts) override;
	/**
	 * @brief 当たってない判定に
	 */
	void ColisionReset();

	/**
	 * @brief 追跡のポインタ取得
	 * @return 追跡のストラテジーポインタ
	 */
	CBossChase* GetBossChase()
	{
		return m_pChase;
	}

	/**
	 * @brief 徘徊のポインタ取得
	 * @return 徘徊のストラテジーポインタ
	 */
	CBossWandering* GetBossWandering()
	{
		return m_pWandering;
	}

	/**
	 * @brief 混乱のポインタ取得
	 * @return 混乱のストラテジーポインタ
	 */
	CBossConfusion* GetBossConfusion()
	{
		return m_pConfusion;
	}

	/**
	 * @brief タックルのポインタ取得
	 * @return タックルのストラテジーポインタ
	 */
	CBossTackle* GetBossTackle()
	{
		return m_pTackle;
	}

	/**
	 * @brief 探索のポインタ取得
	 * @return 探索のストラテジーポインタ
	 */
	CBossSearch* GetBossSearch()
	{
		return m_pSearch;
	}

	/**
	 * @brief 暴走のポインタ取得
	 * @return 暴走のストラテジーポインタ
	 */
	CBossRampage* GetBossRampage()
	{
		return m_pRampage;
	}

	/**
	 * @brief ダッシュエフェクト取得
	 * @return ダッシュエフェクトポインタ
	 */
	CDashEffect* GetDashEffect()
	{
		return m_pTackleEffect;
	}

	/**
	 * @brief タックルチャージエフェクト取得
	 * @return タックルチャージエフェクトポインタ
	 */
	CTackleCharge* GetTackleCharge()
	{
		return m_pTackleCharge;
	}

	/**
	 * @brief ダッシュエフェクト設定
	 * @param [in]ダッシュエフェクトポインタ
	 */
	void SetDashEffect(CDashEffect* effect)
	{
		m_pTackleEffect = effect;
	}

	/**
	 * @brief タックルチャージエフェクト設定
	 * @param [in]タックルチャージエフェクトポインタ
	 */
	void SetTackleCharge(CTackleCharge* charge)
	{
		m_pTackleCharge = charge;
	}

	//当たった方向の列挙
	enum COLISION_AXIS
	{
		NONE,
		X,
		Z,
		MAX,
	};

	//当たった方向設定
	inline void SethitAxis(COLISION_AXIS axis)
	{
		m_HitAxis = axis;
	}

	//当たった方向取得
	inline COLISION_AXIS& GetAxis()
	{
		return m_HitAxis;
	}
private:
	static constexpr float CORRECTION_VALUE_Y = 100.0f; //タックルエフェクトを生成する際のYの補正値

	static constexpr float TACKLE_VALUE = 15.0f; //タックル時のスピード加算

	static constexpr float PLAYER_KNOCKBACK_SPEED = 15.0f; //タックルが当たった時にノックバックさせる際のXとZにかけるスピード

	static constexpr float PLAYER_KNOCKBACK_Y = 30.0f; //タックルが当たった時にノックバックさせる際のYに打ち上げる

	static const float DEFAULT_MOVE; //通常時の移動

	static const D3DXVECTOR3 SHADOW_SIZE; //影のサイズ

	/**
	 * @brief 各行動生成
	 */
	void CreateBossStrategy();

	/**
	 * @brief 各行動破棄
	 */
	void DeleteBossStrategy();

	/**
	 * @brief ステート実行
	 */
	void ProcessState();

	/**
	 * @brief デバッグ表示
	 */
	void DrawDebug();

	Motion_Type m_Motion; //モーションの種類

	CBossState* m_pBossState; //ボスのステートパターン

	COLISION_AXIS m_HitAxis; //どの方向から当たったか

	CBossChase* m_pChase; //追跡処理

	CBossWandering* m_pWandering; //徘徊処理

	CBossConfusion* m_pConfusion; //混乱

	CBossTackle* m_pTackle; //タックル処理

	CBossSearch* m_pSearch; //探索処理

	CBossRampage* m_pRampage; //暴走処理

	CDashEffect* m_pTackleEffect; //ダッシュエフェクト

	CTackleCharge* m_pTackleCharge; //タックルを行う前のエフェクト
};

#endif