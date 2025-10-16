//=============================================
//
//プレイヤーのストラテジーパターン[player_behavior.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _PLAYER_BEHAVIOR_
#define _PLAYER_BEHAVIOR_
#include "character_behavior.h"
#include "player.h"

//=============================================
//プレイヤーの移動のストラテジー
//=============================================
class CPlayerMove : public CMove
{
public:
	static const int MAX_JUMPCNT = 2; //ジャンプ回数

	/**
	 * @brief コンストラクタ
	 */
	CPlayerMove();
	/**
	 * @brief デストラクタ
	 */
	~CPlayerMove() override;
	/**
	 * @brief 移動
	 * @param [in]キャラクタポインタ
	 */
	void Move(CCharacter* character)override;
};

//=============================================
//プレイヤーの攻撃のストラテジー
//=============================================
class CPlayerAttack : public CGunAttack
{
public:
	/**
	 * @brief コンストラクタ
	 */
	CPlayerAttack();
	/**
	 * @brief デストラクタ
	 */
	~CPlayerAttack() override;
	/**
	 * @brief 銃の攻撃
	 * @param [in]どっちの弾か
	 * @param [in]キャラクターポインタ
	 */
	void GunAttack(CBullet::BULLET_ALLEGIANCE Allegiance, CCharacter* character) override;
private:
	//射撃時の移動減算の値
	static constexpr float MOVE_SUBTRACTION = 0.85f;
	static constexpr float CORRECTION_Y = 5.0f; //yの補正値
	static constexpr float RECOIL = 0.002f;		//反動の値
	/**
	 * @brief 弾発射
	 * @param [in]キャラクターポインタ
	 * @param [in]カメラポインタ
	 * @param [in]どっちの弾か
	 * @param [in]レートカウント
	 */
	void ShotBullet(CCharacter* character, CCamera* pCamera, const CBullet::BULLET_ALLEGIANCE& Allegiance,int& nRateCnt);
};

//=============================================
//プレイヤーの回避のストラテジー
//=============================================
class CPlayerAvoidance
{
public:
	/**
	 * @brief コンストラクタ
	 */
	CPlayerAvoidance();
	/**
	 * @brief デストラクタ
	 */
	~CPlayerAvoidance();
	/**
	 * @brief 回避
	 * @param [in]キャラクターポインタ
	 */
	void Avoidance(CCharacter* character);
private:
	static constexpr float PLAYER_AVOIDANCE_SPEED = 30.0f; //ブリンクのスピード

};
#endif // !_ENEMY_BEHAVIOR_
