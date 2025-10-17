//=============================================
//
//マウスの軌跡[mouse_trail.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _MOUSE_TRAIL_H_ //これが定義されてないとき

#define _MOUSE_TRAIL_H_
#include "main.h"
#include "billboard.h"
#include "count.h"

/** @brief My 名前空間 */
namespace My
{
	/**
	 * @brief マウスの軌跡クラス
	 * @copydoc CObject3D
	 */
	class CMouseTrail : public CBillboard
	{
	public:
		static const int PRIORITY = 10;		//!<描画順
		static const D3DXVECTOR3 POLY_SIZE;	//!<ポリゴンサイズ
		static const D3DXCOLOR COLOR;		//!色

		/**
		 * @brief コンストラクタ
		 * @param プライオリティ
		 */		
		CMouseTrail(int nPriority = PRIORITY);

		/**
		 * @brief デストラクタ
		 */
		~CMouseTrail()override;

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
		 * @param [in]確保する軌跡のポインタ
		 * @return マウスの軌跡のポインタ
		 */
		static CMouseTrail* Create(D3DXVECTOR3 pos,CMouseTrail* trail);
	private:
	};
}

#endif