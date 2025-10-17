//=============================================
//
//ゲームマウスカーソル[game_mouse_cursor.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _GAME_MOUSE_CURSOR_H_ //これが定義されてないとき

#define _GAME_MOUSE_CURSOR_H_
#include "main.h"
#include "mouse_cursor.h"
#include "count.h"
#include "mouse_trail_point.h"
#include "mouse_cursor_state.h"

/** @brief My 名前空間 */
namespace My
{
	/**
	 * @brief マウスカーソルクラス
	 * @copydoc CObject2D
	 */
	class CGameMouseCursor : public CMouseCursor
	{
	public:
		static const std::string WRITE_TEX_PATH;						//描いてる時のテクスチャ
		static const int SPLIT = 6;	//テクスチャ分割数

		/**
		 * @brief コンストラクタ
		 * @param プライオリティ
		 */
		CGameMouseCursor(int nPriority = PRIORITY);

		/**
		 * @brief デストラクタ
		 */
		~CGameMouseCursor()override;

		/**
		 * @brief 初期化
		 * @return 成功したか
		 */
		HRESULT Init()override;

		/**
		 * @brief 終了
		 */
		void Uninit()override;

		/**
		 * @brief 更新
		 */
		void Update()override;

		/**
		 * @brief 描画
		 */
		void Draw()override;

		/**
		 * @brief ステート変更
		 * @param [in]次のステート
		 */
		void ChangeState(CMouseCursorState* state);

		/**
		 * @brief 軌跡のポイントを設定
		 * @param [in]軌跡のポインタ
		 */
		inline void SetTrailPoint(CMouseTrailPoint* point)
		{
			m_pMouse_Trail_Point.push_back(point);
		}

		/**
		 * @brief 軌跡のポイントを削除
		 */
		inline void EraseTrailPoint()
		{
			m_pMouse_Trail_Point.erase(m_pMouse_Trail_Point.begin());
		}

		/**
		 * @brief 軌跡のポイントのサイズ取得
		 * @return サイズ数
		 */
		inline int GetTrailPointSize()
		{
			return m_pMouse_Trail_Point.size();
		}

		/**
		 * @brief 状態取得取得
		 * @return 状態
		 */
		inline CMouseCursorState* GetState()
		{
			return m_pState;
		}

		/**
		 * @brief 軌跡のポイント取得
		 * @param [in]番号
		 * @return 軌跡のポイント
		 */
		inline CMouseTrailPoint* GetTrailPoint(unsigned int idx)
		{
			if (idx >= m_pMouse_Trail_Point.size())
			{
				return nullptr;
			}
			return m_pMouse_Trail_Point[idx];
		}

		/**
		 * @brief 指定された軌跡のポイントを削除
		 * @param [in]番号
		 */
		inline void EraseTrailPoint(unsigned int idx)
		{
			if (idx >= m_pMouse_Trail_Point.size())
			{
				return;
			}
			CMouseTrailPoint* point = m_pMouse_Trail_Point[idx];
			point->Uninit();

			m_pMouse_Trail_Point.erase(m_pMouse_Trail_Point.begin() + idx);
		}

		/**
		 * @brief 全ての軌跡のポイントを削除
		 */
		inline void ClearTrailPoint()
		{
			for (auto& itr : m_pMouse_Trail_Point)
			{
				if (itr == nullptr) { continue; }
				itr->Uninit();
				itr = nullptr;
			}
			m_pMouse_Trail_Point.clear();
		}

		/**
		 * @brief 
		 * @param [in]idx
		 */
		void SetTexIdx(int idx)
		{
			if (idx > SPLIT)
			{
				return;
			}
			m_tex_idx = idx;

			m_min_tex_x = (1.0f / (float)SPLIT) * (m_tex_idx - 1);
			m_max_tex_x = (1.0f / (float)SPLIT) * m_tex_idx;
		}
	private:
		std::vector<CMouseTrailPoint*> m_pMouse_Trail_Point;	//!<軌跡を表示するポイント
		CMouseCursorState* m_pState;
		float m_min_tex_x;
		float m_max_tex_x;

		int m_tex_idx;

		/**
		 * @brief テクスチャ座標設定
		 */
		void SetTexPos();
		/**
		 * @brief デバッグ表示
		 */
		void DebugDraw();
	};
}

#endif