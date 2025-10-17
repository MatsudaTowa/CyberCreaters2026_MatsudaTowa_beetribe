//=============================================
//
//アタックポイント[hit_UI_stun.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _HIT_UI_STUN_H_ //これが定義されてないとき

#define _HIT_UI_STUN_H_
#include "main.h"
#include "hit_UI.h"

/** @brief My 名前空間 */
namespace My
{
	/**
	 * @brief ヒットUI(スタン)クラス
	 * @copydoc CObject2D
	 */
	class CHit_UI_Stun : public CHit_UI
	{
	public:
		/**
		 * @brief コンストラクタ
		 * @param プライオリティ
		 */
		CHit_UI_Stun(int nPriority = PRIORITY);

		/**
		 * @brief デストラクタ
		 */
		~CHit_UI_Stun()override;

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