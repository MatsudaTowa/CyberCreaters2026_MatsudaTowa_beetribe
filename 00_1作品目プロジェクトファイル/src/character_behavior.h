//=============================================
//
//キャラクターのストラテジーパターン[character_behavior.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _CHARACTER_BEHAVIOR_H_ //これが定義されてないとき

#define _CHARACTER_BEHAVIOR_H_
#include "main.h"
#include "manager.h"
#include "character.h"

//=============================================
//前方宣言
//=============================================
class CCharacter;

//=============================================
//移動ストラテジー
//=============================================
class CMove
{
public:
	/**
	 * @brief コンストラクタ
	 */
	CMove() {};
	/**
	 * @brief デストラクタ
	 */
	virtual ~CMove() {};
	/**
	 * @brief 移動
	 * @param [in]キャラクターポインタ
	 */
	virtual void Move([[maybe_unused]] CCharacter*character) = 0;
protected:
};

//=============================================
//スタンのストラテジー
//=============================================
class CStan
{
public:
	/**
	 * @brief コンストラクタ
	 */
	CStan() {};
	/**
	 * @brief デストラクタ
	 */
	virtual ~CStan() {};
	/**
	 * @brief スタン
	 * @param [in]キャラクターポインタ
	 */
	virtual void Stan([[maybe_unused]] CCharacter* character) {};
private:
};

//=============================================
//混乱のストラテジー
//=============================================
class CConfusion
{
public:
	/**
	 * @brief コンストラクタ
	 */
	CConfusion() {};
	/**
	 * @brief デストラクタ
	 */
	virtual ~CConfusion() {};
	/**
	 * @brief 混乱
	 * @param [in]キャラクターポインタ
	 * @param [in]回転開始位置
	 */
	virtual void Confusion([[maybe_unused]] CCharacter* character, [[maybe_unused]] float StartRot_y) {};
private:
};

//=============================================
//攻撃ストラテジー
//=============================================
class CGunAttack
{
public:
	/**
	 * @brief コンストラクタ
	 */
	CGunAttack() {};
	/**
	 * @brief デストラクタ
	 */
	virtual ~CGunAttack() {};
	/**
	 * @brief 銃の攻撃
	 * @param [in]どっちの弾か
	 * @param [in]キャラクターポインタ
	 */
	virtual void GunAttack([[maybe_unused]] CBullet::BULLET_ALLEGIANCE Allegiance, [[maybe_unused]] CCharacter* character) = 0;
};
#endif
