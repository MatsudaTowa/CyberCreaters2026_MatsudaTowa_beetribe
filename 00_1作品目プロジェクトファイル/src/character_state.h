//=============================================
//
//キャラクターのステートパターン[character_state.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _CHARACTER_STATE_H_
#define _CHARACTER_STATE_H_

#include "character.h"

//=============================================
//前方宣言
//=============================================
class CCharacter;

//=============================================
//キャラクターのステートクラス
//=============================================
class CCharacterState
{
public:
	/**
	 * @brief 最初に呼ばれる関数
	 * @param [in]キャラクターポインタ
	 */
	virtual void Start([[maybe_unused]] CCharacter* character) {};
	/**
	 * @brief ショット
	 * @param [in]どっちの弾か
	 * @param [in]キャラクターポインタ
	 */
	virtual void Shot([[maybe_unused]] CBullet::BULLET_ALLEGIANCE Allegiance, [[maybe_unused]] CCharacter* character) {};
	/**
	 * @brief スタン処理
	 * @param [in]キャラクターポインタ
	 */
	virtual void Stan([[maybe_unused]] CCharacter* character) {};
	/**
	 * @brief 混乱
	 * @param [in]キャラクターポインタ
	 */
	virtual void Confusion([[maybe_unused]] CCharacter* character) {};
	/**
	 * @brief 移動
	 * @param [in]キャラクターポインタ
	 */
	virtual void Move([[maybe_unused]] CCharacter* character) {};
};

//=============================================
//キャラクターの撃ってる状態
//=============================================
class CShotState : public CCharacterState
{
public:
	/**
	 * @brief ショット
	 * @param [in]どっちの弾か
	 * @param [in]キャラクターポインタ
	 */
	virtual void Shot(CBullet::BULLET_ALLEGIANCE Allegiance, CCharacter* character)override;
};

//=============================================
//キャラクターのスタン状態
//=============================================
class CStanState : public CCharacterState
{
public:
	/**
	 * @brief 最初に呼ばれる関数
	 * @param [in]キャラクターポインタ
	 */
	void Start([[maybe_unused]] CCharacter* character) override;
	/**
	 * @brief スタン
	 * @param [in]キャラクターポインタ
	 */
	virtual void Stan(CCharacter* character)override;
private:
	int m_StanCnt; //スタン計測カウント
};

//=============================================
//キャラクターの混乱状態
//=============================================
class CConfusionState : public CCharacterState
{
public:
	/**
	 * @brief 最初に呼ばれる関数
	 * @param [in]キャラクターポインタ
	 */
	void Start(CCharacter* character) override;
	/**
	 * @brief 混乱
	 * @param [in]キャラクターポインタ
	 */
	virtual void Confusion(CCharacter* character)override;
private:
	float m_StartRot;	//ロットの開始値
	bool m_isRight;		//見渡す(true:右 false:左)
};

//=============================================
//キャラクターの動いてる状態
//=============================================
class CMoveState : public CCharacterState
{
public:
	/**
	 * @brief 移動
	 * @param [in]キャラクターポインタ
	 */
	virtual void Move(CCharacter* character)override;
};

#endif // !_CHARACTER_STATE_H
