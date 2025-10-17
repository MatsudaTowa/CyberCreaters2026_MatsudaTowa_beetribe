//=============================================
//
//ヒットUI[hit_UI.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _HIT_UI_H_ //これが定義されてないとき

#define _HIT_UI_H_
#include "main.h"
#include "object2D.h"

/** @brief My 名前空間 */
namespace My
{
	/**
	 * @brief ヒット時のUIクラス
	 * @copydoc CObject2D
	 */
	class CHit_UI : public CObject2D
	{
	public:
		static const int PRIORITY = 25;  //!<描画順

		enum POINT_TYPE
		{
			BREAK = 0,
			STUN,
			MAX,
		};

		/**
		 * @brief コンストラクタ
		 * @param プライオリティ
		 */
		CHit_UI(int nPriority = PRIORITY);

		/**
		 * @brief デストラクタ
		 */
		~CHit_UI()override;

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
		 * @param [in]タイプ
		 * @return アタックポイントポインタ
		 */
		static CHit_UI* Create(D3DXVECTOR3 pos, int type);
	private:
	};
}

#endif