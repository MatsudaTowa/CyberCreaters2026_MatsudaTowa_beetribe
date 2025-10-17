//=============================================
//
//ウェーブ処理[wave.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _WAVE_H_ //これが定義されてないとき

#define _WAVE_H_
#include "main.h"
#include "block.h"
#include "enemy.h"
#include "score.h"
#include"field.h"

//=============================================
//  ウェーブクラス定義
//=============================================
class CWave
{
public:
	static const int TXT_MAX = 2048; //敵を読み込む際の読み込める最大文字数
	//ウェーブ列挙
	enum WAVE
	{
		NONE = 0,
		ONE,
		TWO,
		THREE,
		BOSS,
		RESULT,
		MAX,
	};

	//読み込むときに必要なエネミーの構造体
	struct LOAD_ENEMY
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
		CEnemy::ENEMY_TYPE type;
	};

	//読み込むときに必要なブロックの構造体
	struct LOAD_BLOCK
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
		CBlock::BLOCKTYPE type;
	};

	//読み込むときに必要な壁の構造体
	struct LOAD_WALL
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 size;
		D3DXVECTOR3 rot;
	};

	//読み込むときに必要なポイントの構造体
	struct LOAD_POINT
	{
		D3DXVECTOR3 pos;
	};

	/**
	 * @brief コンストラクタ
	 */
	CWave();
	/**
	 * @brief デストラクタ
	 */
	virtual ~CWave();

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
	 * @brief 生成
	 * @param [in]ウェーブ
	 * @return ウェーブポインタ
	 */
	static CWave* Create(WAVE wave);
	/**
	 * @brief 生成
	 * @param [in]ウェーブ
	 * @param [in]次のウェーブ
	 * @param [in]リザルトファイルネーム
	 * @return ウェーブポインタ
	 */
	static CWave* Create(WAVE wave,WAVE next_wave,const char* ResultFile);
	/**
	 * @brief 現在のウェーブ取得
	 * @return 何ウェーブ目か
	 */
	static WAVE GetCurrentWave();
	/**
	 * @brief スコア取得
	 * @return スコア
	 */
	static CScore* GetScore();

	/**
	 * @brief ブロック読み込み
	 * @param [in]ファイルネーム
	 */
	void LoadBlock(const std::string& pFileName);

	/**
	 * @brief 壁読み込み
	 * @param [in]ファイルネーム
	 */
	void LoadWall(const std::string* pFileName);

	/**
	 * @brief 敵読み込み
	 * @param [in]ファイルネーム
	 */
	void LoadEnemy(const std::string* pFileName);

	/**
	 * @brief ウェーブのスコア設定
	 * @param [in]スコア
	 */
	inline void SetWaveScore(int nScore)
	{
		m_nTotalScore = nScore;
	}

	/**
	 * @brief スコア取得
	 * @return スコア
	 */
	inline int GetWaveScore()
	{
		return m_nTotalScore;
	}

	/**
	 * @brief ウェーブのリザルト処理
	 * @param [in]リザルトファイル
	 */
	inline void WaveResult(const std::string& pFileName)
	{
		m_pScore->ExportScore(pFileName);
		m_pScore->Reset();
	}
protected:
	static const D3DXVECTOR3 NORMAL_FIELD_SIZE; //通常ウェーブ床のサイズ
	static const D3DXVECTOR3 BOSS_FIELD_SIZE; //ボスウェーブ床のサイズ
	LOAD_ENEMY m_LoadEnemy; //読み込むときに必要なエネミーの情報
	LOAD_BLOCK m_LoadBlock; //読み込むときに必要なブロックの情報
	LOAD_WALL m_LoadWall; //読み込むときに必要な壁の情報
	LOAD_POINT m_LoadPoint; //読み込むときに必要なポイントの情報

	int m_nTotalScore; //スコア格納変数
	static CScore* m_pScore;
	static WAVE m_next; //次のウェーブ
	static const char* m_ResultFile; //リザルトファイル
	static WAVE m_CurrentWave; //現在のウェーブ
};

#endif