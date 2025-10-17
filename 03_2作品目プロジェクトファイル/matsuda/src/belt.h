//=============================================
//
//帯[belt.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _BELT_H_ //これが定義されてないとき

#define _BELT_H_
#include "main.h"
#include "objectX.h"

namespace My
{
	//=============================================
	//帯クラス
	//=============================================
	class CBelt : public CObjectX
	{
	public:
		static const int PRIORITY = 11; //描画順

		//帯の色
		enum LEVEL
		{
			WHITE = 0,
			YELLOW,
			ORANGE,
			BLUE,
			GREEN,
			PURPLE,
			BLOWN,
			BLACK,
			MAX
		};

		/**
		 * @brief コンストラクタ
		 * @param [in]プライオリティ
		 */
		CBelt(int nPriority = PRIORITY);
		/**
		 * @brief デストラクタ
		 */
		~CBelt()override;
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
		 * @param [in]方向
		 * @return 帯ポインタ
		 */
		static CBelt* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

		/**
		 * @brief レベル設定
		 * @param [in]レベル
		 */
		void SetLevel(LEVEL level)
		{
			m_level = level;
		}
		
		/**
		 * @brief レベル取得
		 * @return レベル
		 */
		LEVEL GetLevel()
		{
			return m_level;
		}
	private:
		/**
		 * @brief レベルに合わせて色変更
		 */
		void ColorLevel();
		LEVEL m_level;
	};
}

#endif