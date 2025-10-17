//=============================================
//
//プレイヤーのステートパターン[player_state.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _PLAYER_STATE_H_
#define _PLAYER_STATE_H_

#include "character.h"
#include "ult.h"

//=============================================
//前方宣言
//=============================================
class CActivePlayer;

//=============================================
//キャラクターのステートクラス
//=============================================
class CPlayerState
{
public:
	/**
	 * @brief 通常
	 * @param [in]動くプレイヤーポインタ
	 */
	virtual void Default([[maybe_unused]] CActivePlayer* player) {};
	/**
	 * @brief ウルト
	 * @param [in]動くプレイヤーポインタ
	 */
	virtual void Ult([[maybe_unused]] CActivePlayer* player) {};
	/**
	 * @brief 回避
	 * @param [in]動くプレイヤーポインタ
	 */
	virtual void Avoidance([[maybe_unused]] CActivePlayer* player) {};
	/**
	 * @brief 吹っ飛ばされ
	 * @param [in]動くプレイヤーポインタ
	 */
	virtual void Blown([[maybe_unused]] CActivePlayer* player) {};
};

//=============================================
//キャラクターの通常状態
//=============================================
class CDefaultState : public CPlayerState
{
public:
	/**
	 * @brief 通常
	 * @param [in]動くプレイヤーポインタ
	 */
	virtual void Default(CActivePlayer* player)override;
};

//=============================================
//キャラクターのウルト状態
//=============================================
class CUltState : public CPlayerState
{
public:
	/**
	 * @brief ウルト
	 * @param [in]動くプレイヤーポインタ
	 */
	virtual void Ult(CActivePlayer* player) override;
};

//=============================================
//キャラクターの回避状態
//=============================================
class CAvoidanceState : public CPlayerState
{
public:
	/**
	 * @brief 回避
	 * @param [in]動くプレイヤーポインタ
	 */
	virtual void Avoidance(CActivePlayer* player) override;
};

//=============================================
//キャラクターの吹っ飛ばされ状態
//=============================================
class CBlownState : public CPlayerState
{
public:
	/**
	 * @brief コンストラクタ
	 */
	CBlownState();
	/**
	 * @brief 吹っ飛ばされ
	 * @param [in]動くプレイヤーポインタ
	 */
	virtual void Blown(CActivePlayer* player) override;
private:
	int m_nStanCnt;
};

#endif // !_PLAYER_STATE_H
