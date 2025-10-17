//=============================================
//
//プレイヤー[game_player.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _GAME_PLAYER_H_ //これが定義されてないとき

#define _GAME_PLAYER_H_
#include "main.h"
#include "player.h"
#include "board_holder.h"
#include "game_player_state.h"
#include "player_move_point.h"
#include "combo.h"

/** @brief My 名前空間 */
namespace My
{
	/**
	 * @brief ゲームプレイヤークラス
	 * @copydoc CPlayer
	 */
	class CGamePlayer :public CPlayer
	{
	public:
		static const D3DXVECTOR3 PLAYER_SPAWN_POS;	//!<スポーン位置
		static const D3DXVECTOR3 PLAYER_SPAWN_ROT;	//!<スポーン方向

		/**
		 * @brief コンストラクタ
		 * @param プライオリティ
		 */
		CGamePlayer(int nPriority = PLAYER_PRIORITY);

		/**
		 * @brief デストラクタ
		 */
		~CGamePlayer() override;

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
		 * @brief BGMが切れた時の処理
		 */
		void Play_Sound_BGM_000();

		/**
		 * @brief ステート変更
		 * @param [in]次のステート
		 */
		void ChangeState(CGamePlayerState* state);

		/**
		 * @brief コンボのUI設定
		 * @param [in]コンボのポインタ
		 */
		inline void SetComboUI(CCombo* combo)
		{
			m_pCombo = combo;
		}

		/**
		 * @brief 板持ちを設定
		 * @param [in]板持ちのポインタ
		 */
		inline void SetBoardHolder(CBoardHolder* holder)
		{
			m_pBoardHolder.push_back(holder);
		}

		/**
		 * @brief 板持ちを設定
		 * @param [in]移動ポイント
		 */
		inline void SetMovePoint(D3DXVECTOR3 pos)
		{
			CMovePoint* point = CMovePoint::Create(pos,new CPlayerMovePoint);
			m_pMovePoint.push_back(point);
		}

		/**
		 * @brief 一番最初の板持ちを削除
		 */
		inline void EraseBoardHolder()
		{
			m_pBoardHolder.erase(m_pBoardHolder.begin());
		}	

		/**
		 * @brief 指定された移動ポイントを削除
		 * @param [in]番号
		 */
		inline void EraseMovePoint(unsigned int idx)
		{
			if (idx >= m_pMovePoint.size())
			{
				return;
			}
			CMovePoint* point = m_pMovePoint[idx];
			point->Uninit();

			m_pMovePoint.erase(m_pMovePoint.begin()+idx);
		}

		/**
		 * @brief 全ての移動ポイントを削除
		 */
		inline void ClearMovePoint()
		{
			for (auto& itr : m_pMovePoint)
			{
				if (itr == nullptr) { continue; }
				itr->Uninit();
				itr = nullptr;
			}
			m_pMovePoint.clear();
		}

		/**
		 * @brief 板持ちを取得
		 * @param [in]番号
		 * @return 板持ちのポインタ
		 */
		inline CBoardHolder* GetBoardHolder(unsigned int idx)
		{
			if (idx >= m_pBoardHolder.size())
			{
				return nullptr;
			}
			return m_pBoardHolder[idx];
		}

		/**
		 * @brief 板持ちを取得
		 * @return 板持ちの格納数
		 */
		inline int GetBoardHolderSize()
		{
			return m_pBoardHolder.size();
		}

		/**
		 * @brief 指定された移動ポイントを削除
		 * @param [in]番号
		 * @return 移動ポイント
		 */
		inline CMovePoint* GetMovePoint(unsigned int idx)
		{
			if (idx >= m_pMovePoint.size())
			{
				return nullptr;
			}
			return m_pMovePoint[idx];
		}
		
		/**
		 * @brief ステート取得
		 * @return ステートポインタ
		 */
		inline CGamePlayerState* GetState()
		{
			return m_pState;
		}

		/**
		 * @brief コンボUI取得
		 * @return コンボUI
		 */
		inline CCombo* GetComboUI()
		{
			return m_pCombo;
		}
private:
		static const D3DXVECTOR3 SHADOW_SIZE;	 //!<影のサイズ

		/**
		 * @brief 入力処理
		 */
		void Input();

		/**
		 * @brief プレイヤーのデバッグ表示
		 */
		void Debug()override;

		CGamePlayerState* m_pState;						//!プレイヤーのステート
		std::vector<CMovePoint*> m_pMovePoint;			//!移動ポイント
		std::vector<CBoardHolder*> m_pBoardHolder;		//!板持ち格納ポインタ

		CCombo* m_pCombo;									//コンボUI
	};
}
#endif