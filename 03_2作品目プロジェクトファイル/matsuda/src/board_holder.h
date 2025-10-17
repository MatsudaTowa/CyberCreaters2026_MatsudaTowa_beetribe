//=============================================
//
//板持ち人[board_holder.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _BOARD_HOLDER_H_ //これが定義されてないとき

#define _BOARD_HOLDER_H_
#include "main.h"
#include "character.h"
#include "hit_UI.h"
#include "board.h"

/** @brief My 名前空間 */
namespace My
{
	/**
	 * @brief 板持ちクラス
	 * @copydoc CCharacter
	 */
	class CBoardHolder :public CCharacter
	{
	public:
		static const int PRIORITY = 8;				//!<描画順

		/** @brief モーションの種類列挙*/
		enum Motion_Type
		{
			MOTION_NEUTRAL = 0,
			MOTION_MAX,
		};

		/** @brief 板の向き*/
		enum Board_Direction
		{
			LEFT = 0,
			RIGHT,
			MAX
		};

		/**
		 * @brief コンストラクタ
		 * @param プライオリティ
		 */
		CBoardHolder(int nPriority = PRIORITY);

		/**
		 * @brief デストラクタ
		 */
		~CBoardHolder() override;

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
		 * @brief 倒される
		 */
		void KnockDown();

		/**
		 * @brief 生成
		 * @param [in]座標
		 * @param [in]確保する板持ちのポインタ
		 * @return 生成された板持のポインタ
		 */
		static CBoardHolder* Create(D3DXVECTOR3 pos, CBoardHolder* pBoardHolder);

		/**
		 * @brief ヒットUI生成
		 */
		virtual void CreateHitUI();

		inline CHit_UI* GetHitUI() { return m_pHitUI; }
		inline void SetHitUI(CHit_UI* hit_ui) { m_pHitUI = hit_ui; }

		/**
		 * @brief 板取得
		 * @param [in]番号
		 * @return 板
		 */
		inline CBoard* GetBoard(unsigned int idx)
		{
			if (idx >= m_pBoard.size())
			{
				return nullptr;
			}
			return m_pBoard[idx]; 
		}

		/**
		 * @brief 指定された板を削除
		 * @param [in]番号
		 */
		inline void EraseBoard(unsigned int idx)
		{
			if (idx >= m_pBoard.size())
			{
				return;
			}
			CBoard* board = m_pBoard[idx];
			board->Unload();

			m_pBoard.erase(m_pBoard.begin() + idx);
		}

		/**
		 * @brief 追加
		 * @param [in]追加するポインタ
		 */
		inline void PushBoard(CBoard* board)
		{
			if (board == nullptr)
			{
				return;
			}
			m_pBoard.push_back(board);
		}

		/**
		 * @brief 板が割られた時の処理
		 */
		virtual void BreakBoard() = 0;
	private:
		/**
		 * @brief プレイヤーを見つめる
		 */
		void LookAtPlayer();
		std::vector<CBoard*> m_pBoard;	//!<板
		CCount* m_DelayDethCnt;	//死ぬまでの猶予カウント
		CHit_UI* m_pHitUI; //!<当たった時に表示するUI
	};

	/**
	 * @brief 板持ち情報クラス
	 * @copydoc CBoardHolder
	 */
	class CBoardHolderInfo : public CBoardHolder
	{
	public:
		/**
		 * @brief コンストラクタ
		 * @param プライオリティ
		 */
		CBoardHolderInfo(int nPriority = PRIORITY);

		/**
		 * @brief デストラクタ
		 */
		~CBoardHolderInfo() override;

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
		 * @brief 割られた時の処理
		 */
		void BreakBoard() override;
	private:
		static const D3DXVECTOR3 RIGHT_TURN;	//右の板の回転量
		static const D3DXVECTOR3 LEFT_TURN; 	//左の板の回転量
		static constexpr float OFFSET_X = -10.0f; //Xの補正値
	};

	/**
	 * @brief 瓦情報クラス
	 * @copydoc CBoardHolder
	 */
	class CKawaraInfo : public CBoardHolder
	{
	public:
		/**
		 * @brief コンストラクタ
		 * @param プライオリティ
		 */
		CKawaraInfo(int nPriority = PRIORITY);

		/**
		 * @brief デストラクタ
		 */
		~CKawaraInfo();

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
		 * @brief 割られた時の処理
		 */
		void BreakBoard() override {};
	private:
	};

	/**
	 * @brief 罠持ち情報クラス
	 * @copydoc CBoardHolder
	 */
	class CTrapHolderInfo : public CBoardHolder
	{
	public:
		/**
		 * @brief コンストラクタ
		 * @param プライオリティ
		 */
		CTrapHolderInfo(int nPriority = PRIORITY);

		/**
		 * @brief デストラクタ
		 */
		~CTrapHolderInfo() override;

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
		 * @brief 割られた時の処理
		 */
		void BreakBoard() override {};
	private:
		static constexpr float OFFSET_X = 8.0f; //Xの補正値

		/**
		 * @brief ヒットUI生成
		 */
		void CreateHitUI()override;
	};
}
#endif