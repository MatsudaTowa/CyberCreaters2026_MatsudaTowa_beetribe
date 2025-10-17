//=============================================
//
//殴っちゃいけない板「board_danger.h」
// Author松田永久
//
//=============================================
#ifndef _BOARD_DANGER_H_ //これが定義されてないとき

#define _BOARD_DANGER_H_
#include "main.h"
#include "board.h"

/** @brief My 名前空間 */
namespace My
{
	/**
	 * @brief 殴っちゃいけない板クラス
	 * @copydoc CBoard
	 */
	class CBoardDanger : public CBoard
	{
	public:

		/**
		 * @brief コンストラクタ
		 * @param [in]プライオリティ
		 */
		CBoardDanger(int nPriority = PRIORITY);

		/**
		 * @brief デストラクタ
		 */
		~CBoardDanger()override;

		/**
		 * @brief 描画
		 */
		void Draw()override;
	private:
	};
}

#endif