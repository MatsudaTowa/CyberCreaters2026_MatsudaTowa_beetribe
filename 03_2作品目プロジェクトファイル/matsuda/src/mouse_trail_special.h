//=============================================
//
//マウスの軌跡_必殺技[mouse_trail_special.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _MOUSE_TRAIL_SPECIAL_H_ //これが定義されてないとき

#define _MOUSE_TRAIL_SPECIAL_H_
#include "mouse_trail.h"

/** @brief My 名前空間 */
namespace My
{
	/**
	 * @brief マウスの軌跡_通常クラス
	 * @copydoc CMouseTrail
	 */
	class CMouseTrail_Special : public CMouseTrail
	{
	public:
		static const int SPECIAL_PRIORITY = 28;
		/**
		 * @brief コンストラクタ
		 * @param プライオリティ
		 */
		CMouseTrail_Special(int nPriority = SPECIAL_PRIORITY);

		/**
		 * @brief デストラクタ
		 */
		~CMouseTrail_Special()override;

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
	};
}

#endif