//=============================================
//
//ゲーム処理[game.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _GAME_H_ //これが定義されてないとき

#define _GAME_H_
#include "main.h"
#include "active_scene.h"
#include "player.h"
#include"block.h"
#include "wave.h"
#include "score.h"
#include"wave_result.h"
#include "game_state.h"

//=============================================
// ゲームクラス
//=============================================
class CGame:public CActiveScene
{
public:
	static const int DELAY_CNT = 30; //リザルトに飛ぶまでのディレイ
	static const int BLOCK_TXT_MAX = 2048; //敵を読み込む際の読み込める最大文字数
	static const int DELAY_FLAME = 60; //ディレイのフレーム数

	/**
	 * @brief コンストラクタ
	 */
	CGame();
	/**
	 * @brief デストラクタ
	 */
	~CGame() override;
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
	 * @brief 死亡ペナルティ計算
	 */
	void ApplyDeathPenalty();

	/**
	 * @brief ウェーブ取得
	 * @return ウェーブ
	 */
	static inline CWave* GetWave()
	{
		return m_pWave;
	}

	/**
	 * @brief 次のウェーブ取得
	 * @return 次のウェーブ
	 */
	inline CWave::WAVE GetNextWave()
	{
		return m_next_wave;
	}

	/**
	 * @brief 次のウェーブ設定
	 * @param [in]次のウェーブ
	 */
	inline void SetNextWave(CWave::WAVE next_wave)
	{
		m_next_wave = next_wave;
	}

	/**
	 * @brief リザルト遷移の余韻カウント取得
	 * @param リザルト遷移の余韻カウント
	 */
	inline int GetResultDelay()
	{
		return m_nResultDelay;
	}
	/**
	 * @brief リザルト遷移の余韻カウント設定
	 * @param [in]リザルト遷移の余韻カウント
	 */
	inline void SetResultDelay(int nResultDelay)
	{
		m_nResultDelay = nResultDelay;
	}
	/**
	 * @brief ウェーブ設定
	 * @param [in]wave
	 */
	static void SetWave(CWave::WAVE wave);

	/**
	 * @brief ウェーブ設定
	 * @param [in]ウェーブ
	 * @param [in]次のウェーブ
	 * @param [in]リザルトのスコアファイル
	 */
	static void SetWave(CWave::WAVE wave, CWave::WAVE next_wave, const char* ResultFile);

private:
	static const std::string BLOCK_FILE;	//エネミーのファイル

	static const int DEATH_PENALTY = -50; //死んだときのペナルティ

	int m_nResultDelay; //リザルトへのディレイ

	static CWave* m_pWave;

	CWave::WAVE m_next_wave;
};
#endif