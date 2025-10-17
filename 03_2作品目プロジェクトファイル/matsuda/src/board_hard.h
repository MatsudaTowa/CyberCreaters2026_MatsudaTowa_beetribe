//=============================================
//
// 固い板「board_hard.h」
// Author松田永久
//
//=============================================
#ifndef _BOARD_HARD_H_ //これが定義されてないとき

#define _BOARD_HARD_H_
#include "main.h"
#include "board.h"

/** @brief My 名前空間 */
namespace My
{
	/**
	 * @brief 固い板クラス
	 * @copydoc CBoard
	 */
	class CBoardHard : public CBoard
	{
	public:

		/**
		 * @brief コンストラクタ
		 * @param [in]プライオリティ
		 */
		CBoardHard(int nPriority = PRIORITY);

		/**
		 * @brief デストラクタ
		 */
		~CBoardHard()override;

		/**
		 * @brief 描画
		 */
		void Draw()override;
	private:
	};
}

#endif