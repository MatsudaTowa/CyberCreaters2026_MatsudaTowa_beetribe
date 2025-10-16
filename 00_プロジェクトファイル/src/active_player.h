//=============================================
//
//動かすプレイヤー(チュートリアルやゲームなど)[active_player.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _ACTIVE_PLAYER_H_ //これが定義されてないとき

#define _ACTIVE_PLAYER_H_
#include "main.h"
#include "model_parts.h"
#include "player.h"
#include "reticle.h"
#include"ammo_UI.h"
#include"life_UI.h"
#include "ult_UI.h"
#include "player_behavior.h"
#include "enemy.h"
#include "hit_camera_effect.h"
#include "gun_icon.h"
#include "player_state.h"
#include "ult.h"
#include "gauge.h"

//=============================================
// 前方宣言
//=============================================
class CPlayerState;
class CPlayerAvoidance;
class CAmmo_UI;
class CUlt_UI;
class CUlt;
class CSmoke_UI;
class CBlink_UI;
class CReload_UI;

/**
* @brief 動くプレイヤークラス
* @copydoc CPlayer
*/
class CActivePlayer :public CPlayer
{
public:
	static const int PLAYER_LIFE = 150; //体力
	static const int PLAYER_STAMINA = 100; //スタミナ
	static const int AVOIDANCE_COST = 30; //回避アクションのスタミナコスト

	/**
	 * @brief コンストラクタ
	 * @param [in]プライオリティ
	 */
	CActivePlayer(int nPriority = PLAYER_PRIORITY);
	/**
	 * @brief デストラクタ
	 */
	~CActivePlayer();
	/**
	 * @brief 初期化
	 * @return 成功したか
	 */
	HRESULT Init() override;
	/**
	 * @brief 終了
	 */
	void Uninit()override;
	/**
	 * @brief 更新
	 */
	void Update()override;
	/**
	 * @brief 描画
	 */
	void Draw()override;

	/**
	 * @brief リロード
	 */
	void Reload()override;

	/**
	 * @brief ダメージ
	 */
	void Damage(int nDamage);
	/**
	 * @brief 方向のリセット
	 */
	void ResetRot();
	/**
	 * @brief 敵とのヒット判定
	 */
	void ColisionEnemy();

	/**
	 * @brief 敵の判定チェック
	 * @param [in]敵の情報
	 * @param [in]位置情報
	 * @param [in]最小の位置
	 * @param [in]最大の位置
	 */
	void CheckColisionEnemy(CEnemy* pEnemy, const D3DXVECTOR3 pos, const D3DXVECTOR3 Minpos, const D3DXVECTOR3 Maxpos);
	/**
	 * @brief プレイヤー入力処理
	 */
	void Input();
	/**
	 * @brief プレイヤーのステート切り替え
	 * @param [in]次のステート
	 */
	void ChangePlayerState(CPlayerState* state);

	/**
	 * @brief レティクルの設定
	 * @param [in]レティクルポインタ
	 */
	inline void SetReticle(CReticle* reticle)
	{
		m_Reticle = reticle;
	}

	/**
	 * @brief ウルトの設定
	 * @param [in]ウルトのストラテジーポインタ
	 */
	inline void SetUlt(CUlt* ult)
	{
		m_pUlt = ult;
	}

	/**
	 * @brief 回避の設定
	 * @param [in]回避のストラテジーポインタ
	 */
	inline void SetAvoidance(CPlayerAvoidance* avoidance)
	{
		m_pAvoidance = avoidance;
	}

	/**
	 * @brief 死亡回数の設定
	 * @param [in]死亡回数
	 */
	inline void SetDeathCnt(int DeathCnt)
	{
		m_DeathCnt = DeathCnt;
	}

	/**
	 * @brief スタミナの設定
	 * @param [in]スタミナの値
	 */
	inline void SetStamina(int Stamina)
	{
		m_Stamina = Stamina;
	}

	/**
	 * @brief スモークが使えるかの設定
	 * @param [in]スモークが使えるかどうか
	 */
	inline void SetIsSmoke(bool isSmoke)
	{
		m_isSmoke = isSmoke;
	}

	/**
	 * @brief 吹っ飛ばされるかの設定
	 * @param [in]吹っ飛ばされているかどうか
	 */
	inline void SetBlown(bool isBlown)
	{
		m_isBlown = isBlown;
	}

	/**
	 * @brief ブリンクのカウントの設定
	 * @param [in]ブリンクのカウント
	 */
	inline void SetBlinkCnt(int BlinkCnt)
	{
		m_BlinkCnt = BlinkCnt;
	}

	/**
	 * @brief エネミーと判定をとるかの設定
	 * @param [in]判定するか
	 */
	inline void SetEnemyColision(bool isColision)
	{
		m_isEnemyColision = isColision;
	}

	/**
	 * @brief レティクルの取得
	 * @return レティクルポインタ
	 */
	inline CReticle* GetReticle()
	{
		return m_Reticle;
	}

	/**
	 * @brief ウルトのストラテジーの取得
	 * @return ウルトのストラテジーポインタ
	 */
	inline CUlt* GetUlt()
	{
		return m_pUlt;
	}

	/**
	 * @brief 回避のストラテジーの取得
	 * @return 回避のストラテジーポインタ
	 */
	inline CPlayerAvoidance* GetAvoidance()
	{
		return m_pAvoidance;
	}

	/**
	 * @brief 死亡回数の取得
	 * @return 死亡回数
	 */
	inline int& GetDeathCnt()
	{
		return m_DeathCnt;
	}

	/**
	 * @brief スタミナの取得
	 * @return スタミナ数
	 */
	inline int& GetStamina()
	{
		return m_Stamina;
	}

	/**
	 * @brief ブリンクの回数の取得
	 * @return ブリンクの回数
	 */
	inline int& GetBlinkCnt()
	{
		return m_BlinkCnt;
	}

	/**
	 * @brief スモークが使えるか取得
	 * @return スモークが使えるかどうか
	 */
	inline bool& GetIsSmoke()
	{
		return m_isSmoke;
	}

	/**
	 * @brief 吹っ飛ばされてるか取得
	 * @return スモークが使えるかどうか
	 */
	inline bool& GetBlown()
	{
		return m_isBlown;
	}

	/**
	 * @brief 敵と判定を取るか取得
	 * @return 敵との判定を取るか
	 */
	inline bool& GetEnemyColision()
	{
		return m_isEnemyColision;
	}
private:

	static const D3DXVECTOR3 PLAYER_SPAWN_POS; //スポーン位置
	static const D3DXVECTOR3 PLAYER_SPAWN_ROT; //スポーン方向

	static const int IGNORE_COLLISION_FRAME = 150; //当たり判定無視フレーム
	static const int SMOKE_RECAST_FRAME = 900; //スモーク復活フレーム
	static const int STAN_FRAME = 120; //スタンフレーム数
	static const int STAMINA_RECOVERY = 1; //スタミナ回復数値
	static const int STAMINA_RECOVERY_FRAME = 5; //スタミナがSTAMINA_RECOVERY分回復するまでのフレーム数
	static const int DAMAGE_FRAME = 30; //ダメージフレーム

	static constexpr float DEADZONE_Y = -100.0f; //これを過ぎたらプレイヤー破棄
	static constexpr float RETICLE_CORRECTION_VALUE = 16.0f; //レティクルのY座標補正
	static constexpr float SMOKE_CORRECTION_VALUE = 50.0f; //スモークを射出する際の補正値
	static constexpr float SMOKE_SHOT_SPEED = 20.0f; //スモークを射出するスピード

	static const D3DXVECTOR3 SHADOW_SIZE; //影のサイズ
	static const D3DXVECTOR3 GUN_UI_POS;//銃のUIの位置
	static const D3DXVECTOR2 GUN_UI_SIZE;//銃のUIのサイズ

	/**
	 * @brief 敵と判定どうするか(判定を取るなら当たり判定、判定取らないならカウントを進める)
	 */
	void CanDetectEnemyCollision();

	/**
	 * @brief UIを生成
	 */
	void CreateUI();

	/**
	 * @brief UIを設定
	 */
	void SetUI();

	/**
	 * @brief リスポーン処理
	 */
	void ReSpawn();

	/**
	 * @brief デバッグ表示
	 */
	void DebugPos();

	CAmmo_UI* m_pAmmoUI;	//残弾UI

	CLife_UI* m_pLifeUI;	//体力UI

	CUlt_UI* m_pUltUI;		//ウルトUI

	CSmoke_UI* m_pSmokeUI;	//スモークUI

	CBlink_UI* m_pBlinkUI;	//ブリンクUI

	CReload_UI* m_pReloadUI;	//リロードUI

	CGunIcon* m_pGunIcon;	//銃のアイコン

	CHitCameraEffect* m_pHitCameraEffect;	//ヒット時のカメラエフェクト

	CPlayerState* m_pPlayerState;	//プレイヤーの状態

	CReticle* m_Reticle;	//レティクルポインタ

	CUlt* m_pUlt;			//ウルトポインタ

	CPlayerAvoidance* m_pAvoidance;	//回避行動

	int m_IgnoreColisionCnt;	//敵との当たり判定無効カウント

	int m_SmokeRecastCnt;		//スモークのクールタイムカウント

	int m_DeathCnt; //死亡数

	int m_Stamina; //スタミナ

	int m_BlinkCnt; //ブリンク回数

	int m_StaminaRecoveryCnt; //スタミナ回復カウント

	bool m_isEnemyColision; //エネミーとの判定をとるか

	bool m_isSmoke; //スモークを使ったか

	bool m_isBlown; //ふっとばされてるか
};
#endif