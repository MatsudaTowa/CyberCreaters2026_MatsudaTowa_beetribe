//=============================================
//
//マウスカーソル[mouse_cursor.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _MOUSE_CURSOR_H_ //これが定義されてないとき

#define _MOUSE_CURSOR_H_
#include "main.h"
#include "object2D.h"
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
	class CMouseCursor : public CObject2D
	{
	public:
		static const std::string TEX_PATH;	//ファイルパス

		static const int PRIORITY = 29;  //!<描画順

		/**
		 * @brief コンストラクタ
		 * @param プライオリティ
		 */
		CMouseCursor(int nPriority = PRIORITY);

		/**
		 * @brief デストラクタ
		 */
		~CMouseCursor()override;

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
		 * @brief 生成
		 * @param [in]マウスカーソルのポインタ
		 * @return マウスカーソルのポインタ
		 */
		static CMouseCursor* Create(CMouseCursor* mouse_cursor);

		/**
		 * @brief 過去に位置取得
		 * @return 過去の位置
		 */		
		inline D3DXVECTOR3 GetOldPos()
		{
			return m_oldpos;
		}
	private:
		D3DXVECTOR3 m_oldpos;									//!<過去の位置
	};
}

#endif