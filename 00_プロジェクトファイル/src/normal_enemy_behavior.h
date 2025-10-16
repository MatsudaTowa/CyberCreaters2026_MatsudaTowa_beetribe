//=============================================
//
//ノーマルエネミーのストラテジーパターン[normal_enemy_behavior.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _NORMAL_ENEMY_BEHAVIOR_
#define _NORMAL_ENEMY_BEHAVIOR_
#include "enemy_behavior.h"
#include "enemy.h"

//=============================================
//敵の移動のストラテジー
//=============================================
class CNormalMove : public CEnemyMove
{
public:
	static const int MAX_JUMPCNT = 2; //ジャンプ回数
	/**
	 * @brief コンストラクタ
	 */
	CNormalMove();
	/**
	 * @brief デストラクタ
	 */
	~CNormalMove() override;
	/**
	 * @brief 移動
	 * @param [in]キャラクターポインタ
	 */
	void Move(CCharacter* character)override;
private:
	/**
	 * @brief 留まる
	 * @param [in]キャラクターポインタ
	 */
	void Stay(CCharacter* character);
	/**
	 * @brief Xの移動先
	 * @param [in]キャラクターポインタ
	 */
	void NextMove_X(CCharacter* character);
	static const int TRANSITION_FRAME = 60;
	static const int MOVE_FRAME = 60; //移動フレーム
	static const int STAY_FRAME = 60; //正面を見て止まる時間
	static const int RIGHT_PARCENT = 50; //0以上50未満なら右に
	static const int LEFT_PARCENT = 100; //50以上100未満なら左に
	static const int PROBABILITY_SCALE = 5;	//確率調整値

	int m_TransitionCnt;
	int m_nRight;//左に行く確率
	int m_nLeft; //右に行く確率
	int m_nStateChangeCnt; //ステート変更カウント
	int m_nStayCnt; //ステイ状態カウント
	bool m_bRandom; //どっちに行くか決める
	bool m_bDamage;
};

//=============================================
//敵の攻撃のストラテジー
//=============================================
class CNormalAttack : public CEnemyGunAttack
{
public:
	/**
	 * @brief コンストラクタ
	 */
	CNormalAttack();
	/**
	 * @brief デストラクタ
	 */
	~CNormalAttack() override;
	/**
	 * @brief 銃の攻撃
	 * @param [in]どっちの弾か
	 * @param [in]キャラクターポインタ
	 */
	void GunAttack(CBullet::BULLET_ALLEGIANCE Allegiance, CCharacter* character) override;
private:
	static const int LOST_FRAME = 180;
	int m_nLostCnt;
};

#endif // !_ENEMY_BEHAVIOR_
