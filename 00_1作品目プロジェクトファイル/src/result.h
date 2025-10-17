//=============================================
//
//リザルト[result.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _RESULT_H_ //これが定義されてないとき

#define _RESULT_H_
#include "main.h"
#include "scene.h"
#include "score.h"
#include "manager.h"

//=============================================
// リザルトクラス
//=============================================
class CResult :public CScene
{
public:
	/**
	 * @brief コンストラクタ
	 */
	CResult();
	/**
	 * @brief デストラクタ
	 */
	~CResult() override;
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
	 * @brief 描画
	 */
	void Draw() override;
	/**
	 * @brief スコアロード
	 * @param [in]ファイルパス
	 * @return スコア
	 */
	int LoadScore(const std::string& FileName);

private:
	static const std::string WAVE_RESULT_FILE[CManager::NUM_RESULT_FILE];
	static const D3DXVECTOR3 SCORE_POS[CManager::NUM_RESULT_FILE + 1];
	static const D3DXVECTOR2 SCORE_SIZE[2];
	static const float DIGIT_SHIFT[2];
	CScore* m_pScore[CManager::NUM_RESULT_FILE + 1];
};
#endif