//=============================================
//
//ゲームプレイヤーのステートパターン[game_player_state.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _GAME_PLAYER_STATE_H_
#define _GAME_PLAYER_STATE_H_

#include "character.h"
#include "board_holder.h"

/** @brief My 名前空間 */
namespace My
{
	//=============================================
	//前方宣言
	//=============================================
	class CGamePlayer;

	/** @brief プレイヤーのステートクラス */
	class CGamePlayerState
	{
	public:
		CGamePlayerState() {};
		virtual ~CGamePlayerState() {};
		/**
		* @brief ニュートラル処理(親では何もしない)
		* @param [in]ゲームプレイヤーポインタ
		*/
		virtual void Neutral([[maybe_unused]] CGamePlayer* player) {};

		/**
		* @brief 自由移動処理(親では何もしない)
		* @param [in]ゲームプレイヤーポインタ
		*/
		virtual void MovetoFree([[maybe_unused]] CGamePlayer* player) {};

		/**
		* @brief 攻撃処理(親では何もしない)
		* @param [in]ゲームプレイヤーポインタ
		*/
		virtual void Attack([[maybe_unused]] CGamePlayer* player) {};
	};

	/** @brief プレイヤーのニュートラルクラス */
	class CNeutralState :public CGamePlayerState
	{
	public:
		/**
		* @brief ニュートラル処理
		* @param [in]ゲームプレイヤーポインタ
		*/
		void Neutral(CGamePlayer* player) override;
	};

	/** @brief プレイヤーの自由移動クラス */
	class CMovetoFreeState :public CGamePlayerState
	{
	public:
		/**
		* @brief 自由移動処理
		* @param [in]ゲームプレイヤーポインタ
		*/
		void MovetoFree(CGamePlayer* player) override;
	private:
		static constexpr float THRESHOLD = 10.0f; // 距離が定数以下なら到達とする（必要に応じて調整）
	};

	/** @brief プレイヤーの攻撃クラス */
	class CAttackState :public CGamePlayerState
	{
	public:
		/**
		 * @brief コンストラクタ
		 */
		CAttackState();
		/**
		* @brief 攻撃処理
		* @param [in]ゲームプレイヤーポインタ
		*/
		void Attack(CGamePlayer* player) override;
	private:
		static const int DELAY_FLAME = 60;	//遷移までのフレーム数
		static const int PENALTY = 5;		//トラップを殴った時のタイム減少
		static const D3DXVECTOR3 COMBO_UI_POS; 	//コンボUIの位置
		/**
		 * @brief 板持ちのほうを見る
		 * @param [in]板持ちポインタ
		 * @param [in]プレイヤーポインタ
		 */
		void LookAtBoardHolder(My::CBoardHolder* board_holder, My::CGamePlayer* player);
	};
}
#endif // !_GAME_PLAYER_STATE_H_
