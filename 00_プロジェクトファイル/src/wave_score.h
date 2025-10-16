//=============================================
//
//ウェーブスコア処理「wave_scorer.h」
// Author松田永久
//
//=============================================
#ifndef _WAVE_SCORE_H_ //これが定義されてないとき
#define _WAVE_SCORE_H_
#include "main.h"
#include "object2D.h"
#include "score.h"

//=============================================
//スコアクラス
//=============================================
class CWaveScore : public CScore
{
public:
	static constexpr float DIGIT_SHIFT = 70.0f;
	/**
	 * @brief コンストラクタ
	 */
	CWaveScore();
	/** デストラクタ */
	~CWaveScore() override;
	/**
	 * @brief 初期化
	 * @return 成功したか
	 */
	HRESULT Init() override;
	/**
	 * @brief 終了
	 */
	void Uninit() override;
	/**
	 * @brief 更新
	 */
	void Update() override;
private:

	static const D3DXVECTOR3 NUM_POS; //数字の位置
	static const D3DXVECTOR2 NUM_SIZE; //数字のサイズ
};

#endif // DEBUG
