//=============================================
//
//水しぶきエフェクト[flash_effect.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _SPLASH_EFFECT_H_ //これが定義されてないとき

#define _SPLASH_EFFECT_H_
#include "main.h"
#include "billboard.h"
#include "count.h"

/** @brief My 名前空間 */
namespace My
{
	/**
	 * @brief 水しぶき
	 * @copydoc CBillboard_Anim
	 */
	class CSplashEffect : public CBillboard
	{
	public:
		static const int PRIORITY = 21;		//!<描画順

		/**
		 * @brief コンストラクタ
		 * @param プライオリティ
		 */
		CSplashEffect(int nPriority = PRIORITY);

		/**
		 * @brief デストラクタ
		 */
		~CSplashEffect()override;

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
		 * @return エフェクトのポインタ
		 */
		static CSplashEffect* Create(D3DXVECTOR3 pos);
	private:
		D3DXVECTOR3 m_move;
		CCount* m_pCnt;
	};
}

#endif