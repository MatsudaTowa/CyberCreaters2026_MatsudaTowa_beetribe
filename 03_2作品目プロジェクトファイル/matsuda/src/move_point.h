//=============================================
//
//移動するポイント[move_point.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _MOVE_POINT_H_ //これが定義されてないとき

#define _MOVE_POINT_H_
#include "main.h"
#include "billboard.h"

/** @brief My 名前空間 */
namespace My
{
	/**
	 * @brief 移動するポイントクラス
	 * @copydoc CBillboard
	 */
	class CMovePoint : public CBillboard
	{
	public:
		static const int PRIORITY = 10;  //!<描画順

		/**
		 * @brief コンストラクタ
		 * @param プライオリティ
		 */
		CMovePoint(int nPriority = PRIORITY) :CBillboard(nPriority) {};

		/**
		 * @brief デストラクタ
		 */
		~CMovePoint()override {};

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
		 * @param [in]位置
		 * @param [in]ポイント
		 * @return 移動するポイント
		 */
		static CMovePoint* Create(D3DXVECTOR3 pos,CMovePoint* point);
	private:
	};
}

#endif