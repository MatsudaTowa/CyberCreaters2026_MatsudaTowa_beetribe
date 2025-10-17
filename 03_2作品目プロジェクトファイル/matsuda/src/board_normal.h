//=============================================
//
//通常の板「board_normal.h」
// Author松田永久
//
//=============================================
#ifndef _BOARD_NORMAL_H_ //これが定義されてないとき

#define _BOARD_NORMAL_H_
#include "main.h"
#include "board.h"

/** @brief My 名前空間 */
namespace My
{
	/**
	 * @brief 通常の板クラス
	 * @copydoc CBoard
	 */
	class CBoardNormal : public CBoard
	{
	public:

		/**
		 * @brief コンストラクタ
		 * @param [in]プライオリティ
		 */
		CBoardNormal(int nPriority = PRIORITY);

		/**
		 * @brief デストラクタ
		 */
		~CBoardNormal()override;

		/**
		 * @brief 描画
		 */
		void Draw()override;
	private:
	};
}

#endif