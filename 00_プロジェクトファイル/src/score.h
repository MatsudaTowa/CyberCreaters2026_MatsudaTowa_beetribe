//=============================================
//
//スコア処理「scorer.h」
// Author松田永久
//
//=============================================
#ifndef _SCORE_H_ //これが定義されてないとき
#define _SCORE_H_
#include "main.h"
#include "object2D.h"
#include "number.h"
#include "player_UI_box.h"

//=============================================
//スコアクラス
//=============================================
class CScore
{
public:
	/**
	 * @brief コンストラクタ
	 */
	CScore();
	/**
	 * @brief デストラクタ
	 */
	virtual ~CScore();
	/**
	 * @brief 初期化
	 * @return 成功したか
	 */
	virtual HRESULT Init();
	/**
	 * @brief 終了
	 */
	virtual void Uninit();
	/**
	 * @brief 更新
	 */
	virtual void Update();
	/**
	 * @brief スコア加算
	 * @param [in]値
	 */
	void AddScore(int nValue);
	/**
	 * @brief スコア書き出し
	 * @param [in]ファイルネーム
	 */
	void ExportScore(const std::string& FileName);

	/**
	 * @brief スコアリセット
	 */
	void Reset();

	/**
	 * @brief スコア設定
	 * @param [in]スコア
	 */
	void SetScore();

	/**
	 * @brief スコア取得
	 * @return 現在のスコア
	 */
	inline int GetScore()
	{
		return m_nScore;
	}

	/**
	 * @brief 位置設定
	 * @param [in]位置
	 */
	inline void SetPos(D3DXVECTOR3 pos)
	{
		m_pos = pos;
	}

	/**
	 * @brief サイズ設定
	 * @param [in]サイズ
	 */
	inline void SetSize(D3DXVECTOR2 size)
	{
		m_size = size;
	}

	/**
	 * @brief 桁の位置ずらす値設定
	 * @param [in]桁の位置ずらす値
	 */
	inline void SetDigitShift(float shift)
	{
		m_DigitShift = shift;
	}

	/**
	 * @brief 表示座標取得
	 * @return 表示座標
	 */
	inline D3DXVECTOR3& GetPos()
	{
		return m_pos;
	}

	/**
	 * @brief サイズ取得
	 * @return サイズ
	 */
	inline D3DXVECTOR2& GetSize()
	{
		return m_size;
	}

	/**
	 * @brief 桁ずらす値取得
	 * @return 桁ずらす値
	 */
	inline float& GetDigitShift()
	{
		return m_DigitShift;
	}
private:
	static const int NUM_DIGIT = 6;  //桁数

	static const D3DXVECTOR3 NUM_POS; //数字の位置
	static const D3DXVECTOR2 NUM_SIZE; //数字のサイズ

	D3DXVECTOR3 m_pos;
	D3DXVECTOR2 m_size;
	CNumber_2D* m_pNumber[NUM_DIGIT];

	float m_DigitShift;
	int m_nScore; //スコアの値

};
#endif // DEBUG