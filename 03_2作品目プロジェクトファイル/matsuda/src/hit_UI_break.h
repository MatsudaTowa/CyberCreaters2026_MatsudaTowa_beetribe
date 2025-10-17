//=============================================
//
//アタックポイント[hit_UI_break.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _HIT_UI_BREAK_H_ //これが定義されてないとき

#define _HIT_UI_BREAK_H_
#include "main.h"
#include "hit_UI.h"

/** @brief My 名前空間 */
namespace My
{
	/**
	 * @brief ヒットUI(割れ)クラス
	 * @copydoc CObject2D
	 */
	class CHit_UI_Break : public CHit_UI
	{
	public:
		/**
		 * @brief コンストラクタ
		 * @param プライオリティ
		 */
		CHit_UI_Break(int nPriority = PRIORITY);

		/**
		 * @brief デストラクタ
		 */
		~CHit_UI_Break()override;

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