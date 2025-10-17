//=============================================
//
//ゲームのステートパターン[game_state.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _GAME_STATE_H_
#define _GAME_STATE_H_

#include "paper.h"

/** @brief My 名前空間 */
namespace My
{
	//=============================================
	//前方宣言
	//=============================================
	class CGame;

	/** @brief ゲームのステートクラス */
	class CGameState
	{
	public:
		CGameState() {};
		virtual ~CGameState() {};
		/**
		* @brief 通常処理(親では何もしない)
		* @param [in]ゲームポインタ
		*/
		virtual void Normal([[maybe_unused]] CGame* game) {};

		/**
		* @brief ポーズ状態処理(親では何もしない)
		* @param [in]ゲームポインタ
		*/
		virtual void Pause([[maybe_unused]] CGame* game) {};

		/**
		* @brief プレイヤー攻撃時処理(親では何もしない)
		* @param [in]ゲームポインタ
		*/
		virtual void Attack([[maybe_unused]] CGame* game) {};

		/**
		* @brief 必殺技描く処理(親では何もしない)
		* @param [in]ゲームポインタ
		*/
		virtual void SpecialWrite([[maybe_unused]] CGame* game) {};

		/**
		* @brief 必殺技描く処理(親では何もしない)
		* @param [in]ゲームポインタ
		*/
		virtual void SpecialAttack([[maybe_unused]] CGame* game) {};
	};

	/** @brief 通常クラス */
	class CNormal :public CGameState
	{
	public:
		static const int SPECIAL_TIME = 30;	//必殺技状態に移る時間
		/**
		* @brief ニュートラル処理
		* @param [in]ゲームプレイヤーポインタ
		*/
		void Normal(CGame* game) override;
	private:
	};

	/** @brief 状態処理クラス */
	class CPause :public CGameState
	{
	public:
		~CPause()override;
		/**
		* @brief ポーズ状態処理
		* @param [in]ゲームポインタ
		*/
		void Pause(CGame* game) override;
	private:
		static constexpr float THRESHOLD = 10.0f; // 距離が定数以下なら到達とする（必要に応じて調整）
	};

	/** @brief 攻撃時処理クラス */
	class CAttack :public CGameState
	{
	public:
		~CAttack()override;
		/**
		* @brief 攻撃状態処理
		* @param [in]ゲームポインタ
		*/
		void Attack(CGame* game) override;
	private:
	};

	/** @brief 必殺技を描く処理クラス */
	class CSpecialWrite :public CGameState
	{
	public:
		/**
		 * @brief コンストラクタ
		 */
		CSpecialWrite();
		/**
		 * @brief デストラクタ
		 */
		~CSpecialWrite() override;
		/**
		* @brief 必殺技処理
		* @param [in]ゲームポインタ
		*/
		void SpecialWrite(CGame* game) override;
	private:
	};

	/** @brief 必殺技の攻撃処理クラス */
	class CSpecialAttack :public CGameState
	{
	public:
		/**
		 * @brief コンストラクタ
		 */
		CSpecialAttack();
		/**
		 * @brief デストラクタ
		 */
		~CSpecialAttack() override;
		/**
		* @brief 必殺技攻撃処理
		* @param [in]ゲームポインタ
		*/
		void SpecialAttack(CGame* game) override;
	private:
	};
}
#endif // !_GAME_PLAYER_STATE_H_
