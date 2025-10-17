//=============================================
//
//マウスの軌跡_通常[mouse_trail_normal.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _MOUSE_TRAIL_NORMAL_H_ //これが定義されてないとき

#define _MOUSE_TRAIL_NORMAL_H_
#include "mouse_trail.h"

/** @brief My 名前空間 */
namespace My
{
	/**
	 * @brief マウスの軌跡_通常クラス
	 * @copydoc CMouseTrail
	 */
	class CMouseTrail_Normal : public CMouseTrail
	{
	public:
		/**
		 * @brief コンストラクタ
		 * @param プライオリティ
		 */
		CMouseTrail_Normal(int nPriority = PRIORITY);

		/**
		 * @brief デストラクタ
		 */
		~CMouseTrail_Normal()override;

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
	private:
		CCount* m_pCnt;
	};
}

#endif