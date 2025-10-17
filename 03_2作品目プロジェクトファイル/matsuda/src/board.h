//=============================================
//
//板「board.h」
// Author松田永久
//
//=============================================
#ifndef _BOARD_H_ //これが定義されてないとき

#define _BOARD_H_
#include "main.h"
#include "objectX.h"
#include "model.h"

/** @brief My 名前空間 */
namespace My
{
	/**
	 * @brief 板クラス
	 * @copydoc CObjectX : TODO:仮でX
	 */
	class CBoard : public CModel_Parts
	{
	public:

		enum BOARD_TYPE
		{
			BOARD_NORMAL = 0,
			BOARD_HARD,
			BOARD_DANGER,
			BOARD_MAX,
		};

		static const int PRIORITY = 11; //!<描画順

		/**
		 * @brief コンストラクタ
		 */
		CBoard(int nPriority = PRIORITY);

		/**
		 * @brief デストラクタ
		 */
		~CBoard()override;

		/**
		 * @brief 描画
		 */
		void Draw()override;


		/**
		 * @brief 描画
		 */
		void Draw(D3DXCOLOR col)override;

		/**
		 * @brief 生成
		 * @param [in]位置
		 * @param [in]確保する板のポインタ
		 * @return ボードのポインタ
		 */
		static CBoard* Create(D3DXVECTOR3 pos, CBoard* board);
	private:
		bool m_isDirection;
	};
}

#endif