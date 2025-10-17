//=============================================
//
//必殺技時に書く紙[paper.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _PAPER_H_ //これが定義されてないとき

#define _PAPER_H_
#include "main.h"
#include "object2D.h"

/** @brief My 名前空間 */
namespace My
{
	/**
	 * @brief 紙クラス
	 * @copydoc CObject2D
	 */
	class CPaper : public CObject2D
	{
	public:
		static const int PRIORITY = 27;  //!<描画順

		/**
		 * @brief コンストラクタ
		 * @param [in]プライオリティ
		 */
		CPaper(int nPriority = PRIORITY);

		/**
		 * @brief デストラクタ
		 */
		~CPaper()override;

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
		 * @brief 紙の生成
		 * @param [in]生成位置
		 * @return 紙のポインタ
		 */
		static CPaper* Create(D3DXVECTOR3 pos);
	private:
	};
}

#endif