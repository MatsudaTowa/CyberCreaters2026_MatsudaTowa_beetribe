//=============================================
//
//ウェーブごとの結果[wave_result.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _WAVE_RESULT_H_ //これが定義されてないとき

#define _WAVE_RESULT_H_
#include "main.h"
#include "block.h"
#include "enemy.h"
#include"wave.h"
#include "wave_score.h"
#include"wave_result_screen.h"

//=============================================
//  ウェーブリザルトクラス定義
//=============================================
class CWave_Result:public CWave
{
public:
	/**
	 * @brief コンストラクタ
	 */
	CWave_Result();
	/**
	 * @brief デストラクタ
	 */
	~CWave_Result() override;
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
	/**
	 * @brief 次のウェーブ設定
	 * @param [in]ウェーブ
	 */
	void SetNextWave(CWave::WAVE wave);
	/**
	 * @brief スコア読み込み
	 * @param [in]スコア保存ファイルネーム
	 */
	void LoadScore(const std::string& pFileName);

	/**
	 * @brief 生成
	 * @param [in]ウェーブ
	 */
	inline void Create(CWave::WAVE wave)
	{
		SetNextWave(wave);
	}
private:
	int m_nScore;
	CWave_Result_Screen* m_pScreen;
};

#endif

