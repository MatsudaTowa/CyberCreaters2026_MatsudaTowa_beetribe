//=============================================
//
//エネミーのストラテジーパターン[enemy_behavior.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _ENEMY_BEHAVIOR_
#define _ENEMY_BEHAVIOR_
#include "character_behavior.h"
#include "enemy.h"
#include "enemy_reaction_UI.h"

//=============================================
//敵の移動のストラテジー
//=============================================
class CEnemyMove : public CMove
{
public:
	static const int MAX_JUMPCNT = 2; //ジャンプ回数

	/**
	 * @brief コンストラクタ
	 */
	CEnemyMove();
	/**
	 * @brief デストラクタ
	 */
	~CEnemyMove() override;
	/**
	 * @brief 移動処理
	 * @param [in]キャラクターポインタ
	 */
	void Move(CCharacter* character)override;
	/**
	 * @brief 移動方向設定
	 * @param [in]移動方向
	 */
	void SetMoveVec(D3DXVECTOR3 move_vec)
	{
		m_move_vec = move_vec;
	}
private:
	D3DXVECTOR3 m_move_vec;
};

//=============================================
//敵のスタンのストラテジー
//=============================================
class CEnemyStan : public CStan
{
public:
	/**
	 * @brief コンストラクタ
	 */
	CEnemyStan();
	/**
	 * @brief デストラクタ
	 */
	~CEnemyStan() override;
	/**
	 * @brief スタン
	 * @param [in]キャラクターポインタ
	 */
	void Stan(CCharacter* character)override;
private:
};

//=============================================
//敵の混乱のストラテジー
//=============================================
class CEnemyConfusion : public CConfusion
{
public:
	/**
	 * @brief コンストラクタ
	 */
	CEnemyConfusion();
	/**
	 * @brief デストラクタ
	 */
	~CEnemyConfusion() override;
	/**
	 * @brief 混乱
	 * @param [in]キャラクターポインタ
	 * @param [in]回転開始位置
	 */
	void Confusion(CCharacter* character, float StartRot_y)override;
	/**
	 * @brief 回転処理
	 * @param [in]方向
	 * @param [in]最終到達点
	 * @param [in]キャラクターポインタ
	 */
	void MoveRot(D3DXVECTOR3& rot, float Rot_Answer_y, CCharacter* character);
private:
	static constexpr float CORRECTION_VALUE = 40.0f; //リアクションのUIを生成する際のYの補正値
	static const D3DXVECTOR3 SIZE; //リアクションのUIのサイズ
	static constexpr float ROT_MOVE = 0.02f; //見渡す移動値
	static constexpr float CORRECTION_VALUE_Y = 20.0f; //レイを飛ばすYの補正値

	static constexpr float LOOK_RANGE = 1.57f; //見渡す範囲
	static constexpr int NUM_TURN = 2; //見渡す回数

	CEnemy_Reaction_UI* m_pReaction;
	int m_TurnCnt; //何回見渡したか
	bool m_isRight; //見渡す(true:右 false:左)
};

//=============================================
//敵の攻撃のストラテジー
//=============================================
class CEnemyGunAttack : public CGunAttack
{
public:
	/**
	 * @brief コンストラクタ
	 */
	CEnemyGunAttack();
	/**
	 * @brief デストラクタ
	 */
	~CEnemyGunAttack() override;
	/**
	 * @brief 銃の攻撃
	 * @param [in]どっちの弾か
	 * @param [in]キャラクタポインタ
	 */
	void GunAttack(CBullet::BULLET_ALLEGIANCE Allegiance,CCharacter* character) override;
	/**
	 * @brief プレイヤーのほうを向かせる
	 * @param [in]キャラクタポインタ
	 */
	void LookAtPlayer(CCharacter* character);

private:
	static constexpr float CORRECTION_Y = 5.0f; //yの補正値
};
#endif // !_ENEMY_BEHAVIOR_
