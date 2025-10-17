//=============================================
//
//プレイヤーが移動するポイント[player_move_point.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _PLAYER_MOVE_POINT_H_ //これが定義されてないとき

#define _PLAYER_MOVE_POINT_H_
#include "main.h"
#include "move_point.h"
#include "count.h"

/** @brief My 名前空間 */
namespace My
{
	/**
	 * @brief プレイヤーが移動するポイントクラス
	 * @copydoc CMovePoint
	 */
	class CPlayerMovePoint : public CMovePoint
	{
	public:
		static const int PRIORITY = 10;  //!<描画順

		/**
		 * @brief コンストラクタ
		 * @param プライオリティ
		 */
		CPlayerMovePoint(int nPriority = PRIORITY) :CMovePoint(nPriority){};

		/**
		 * @brief デストラクタ
		 */
		~CPlayerMovePoint()override {};

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