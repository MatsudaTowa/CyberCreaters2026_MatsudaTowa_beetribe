//=============================================
//
//スコア処理「score.h」
// Author松田永久
//
//=============================================
#ifndef _SCORE_H_ //これが定義されてないとき
#define _SCORE_H_
#include "main.h"
#include "object2D.h"
#include "number.h"
#include "count.h"

/** @brief My 名前空間 */
namespace My
{
	/** @brief スコアクラス */
	class CScore
	{
	public:
		static const int MAX_SCORE = 100;	//TODO: とりあえずこの数以上倒したら黒帯にします

		CScore();
		~CScore();
		HRESULT Init();
		void Uninit();
		void Update();

		/**
		 * @brief スコア取得
		 * @return 現在のスコア
		 */
		inline int GetCurrentScore()
		{
			return m_current_score;
		}

		/**
		 * @brief スコア設定
		 * @param [in]現在のスコア
		 */
		inline void SetCurrentScore(int score)
		{
			m_current_score = score;
		}
	private:
		int m_current_score;					//今のスコア
	};
}

#endif // DEBUG