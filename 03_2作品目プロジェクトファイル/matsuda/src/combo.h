//=============================================
//
//コンボ表示処理「combo.h」
// Author松田永久
//
//=============================================
#ifndef _COMBO_H_ //これが定義されてないとき
#define _COMBO_H_
#include "main.h"
#include "object2D.h"
#include "number.h"
#include "count.h"

/** @brief My 名前空間 */
namespace My
{
	/** @brief コンボクラス */
	class CCombo:public CObject2D
	{
	public:
		static const int PRIORITY = 28;
		CCombo(int nPriority = PRIORITY);
		~CCombo() override;
		HRESULT Init() override;
		void Uninit() override;
		void Update() override;
		void SubAlpha();
		void Draw() override;

		/**
		 * @brief コンボ数設定
		 * @param [in]コンボ数設定
		 */
		inline void SetNumCombo(int combo)
		{
			m_combo = combo;
		}

		/**
		 * @brief コンボ数取得
		 * @return コンボ数
		 */
		inline int GetNumCombo()
		{
			return m_combo;
		}

		/**
		 * @brief 生成
		 * @param [in]位置
		 * @return コンボのポインタ
		 */
		static CCombo* Create(D3DXVECTOR3 pos);

	private:
		/**
		 * @brief コンボ設定
		 */
		void SetCombo();
		/**
		 * @brief 桁追加
		 * @param [in]U座標
		 * @param [in]桁数
		 */
		void AddDigit(std::vector<int>& pos_texU, int& num_digit);
		CCount* m_pCnt;							//何フレーム経ったかカウントする変数
		D3DXVECTOR3 m_num_pos;					//数字の位置
		int m_combo;							//コンボ数
		std::vector<CNumber_2D*> m_pNumber;		//数字
	};
}

#endif // DEBUG