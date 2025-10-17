//=============================================
//
//マウスの軌跡を設置するポイント[mouse_trail_point.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _MOUSE_TRAIL_POINT_H_ //これが定義されてないとき

#define _MOUSE_TRAIL_POINT_H_
#include "main.h"
#include "billboard.h"
#include "count.h"

/** @brief My 名前空間 */
namespace My
{
	/**
	 * @brief マウスの軌跡を設置するポイントクラス
	 * @copydoc CBillboard
	 */
	class CMouseTrailPoint : public CBillboard
	{
	public:
		static const int PRIORITY = 25;  //!<描画順

		/**
		 * @brief コンストラクタ
		 * @param プライオリティ
		 */
		CMouseTrailPoint(int nPriority = PRIORITY):CBillboard(nPriority) {};

		/**
		 * @brief デストラクタ
		 */
		~CMouseTrailPoint()override{};

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
		 * @return マウスの軌跡のポインタ
		 */
		static CMouseTrailPoint* Create(D3DXVECTOR3 pos);

		/**
		 * @brief 軌跡生成
		 * @param [in]位置
		 * @return マウスカーソルのワールド座標
		 */
		void CreateTrail();
	private:
	};
}

#endif