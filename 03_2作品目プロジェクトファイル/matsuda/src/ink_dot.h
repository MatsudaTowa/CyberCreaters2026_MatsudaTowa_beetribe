//=============================================
//
//墨の点[ink_dot.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _INK_DOT_H_ //これが定義されてないとき

#define _INK_DOT_H_
#include "main.h"
#include "object3D.h"

/** @brief My 名前空間 */
namespace My
{
	/**
	 * @brief 墨の飛び散りクラス
	 * @copydoc CObject3D
	 */
	class CInkDot : public CObject3D
	{
	public:

		static const int PRIORITY = 21; //!<描画順

		/**
		 * @brief コンストラクタ
		 * @param [in]プライオリティ
		 */
		CInkDot(int nPriority = PRIORITY);

		/**
		 * @brief デストラクタ
		 */
		~CInkDot()override;

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
		 * @brief インクの跡生成
		 * @param [in]生成位置
		 * @return インクの跡のポインタ
		 */
		static CInkDot* Create(D3DXVECTOR3 pos);
	private:
	};
}

#endif