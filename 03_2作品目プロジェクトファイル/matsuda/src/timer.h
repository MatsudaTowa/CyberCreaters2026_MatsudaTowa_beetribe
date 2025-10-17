//=============================================
//
//タイマー処理「timer.h」
// Author松田永久
//
//=============================================
#ifndef _TIMER_H_ //これが定義されてないとき
#define _TIMER_H_
#include "main.h"
#include "object2D.h"
#include "number.h"
#include "count.h"

/** @brief My 名前空間 */
namespace My
{
	/** @brief タイマークラス */
	class CTimer
	{
	public:
		/**
		 * @brief コンストラクタ
		 */
		CTimer();

		/**
		 * @brief デストラクタ
		 */
		~CTimer();

		/**
		 * @brief 初期化
		 * @return 成功したか
		 */
		HRESULT Init();

		/**
		 * @brief 終了
		 */
		void Uninit();

		/**
		 * @brief 更新
		 */
		void Update();

		/**
		 * @brief タイマーを減らす処理
		 */
		void DecreaseTime();

		/**
		 * @brief タイマー秒数取得
		 * @return 現在の時間
		 */
		inline int GetCurrentTimer()
		{
			return m_nCurrentTime;
		}

		/**
		 * @brief タイマー秒数設定
		 * @param [in]現在の時間
		 */
		inline void SetCurrentTimer(int time)
		{
			m_nCurrentTime = time;
		}
	private:
		/**
		 * @brief タイマー情報設定
		 */
		void SetTimer();
		/**
		 * @brief 桁削除
		 * @param [in]テクスチャU座標
		 * @param [in]桁数
		 */
		void EraseDigit(std::vector<int> pos_texU, int& num_digit);
		CCount* m_pCnt;							//何フレーム経ったかカウントする変数
		int m_nCurrentTime;						//今の時間
		D3DXVECTOR3 m_pos;						//位置
		std::vector<CNumber_2D*> m_pNumber;		//数字
	};
}

#endif // DEBUG