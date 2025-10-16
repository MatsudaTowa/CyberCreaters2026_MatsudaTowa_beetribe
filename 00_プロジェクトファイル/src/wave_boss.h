//=============================================
//
//ボスウェーブ処理[wave_boss.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _WAVE_BOSS_H_ //これが定義されてないとき

#define _WAVE_BOSS_H_
#include "main.h"
#include "block.h"
#include "enemy.h"
#include"wave.h"
#include "move_point.h"

//=============================================
//  ボスウェーブクラス定義
//=============================================
class CWave_Boss :public CWave
{
public:
	static const int NUM_POINT = 12;

	/**
	 * @brief コンストラクタ
	 */
	CWave_Boss();
	/**
	 * @brief デストラクタ
	 */
	~CWave_Boss()override;
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
	 * @brief 移動先取得
	 * @param [in]番号
	 * @return 移動先ポインタ
	 */
	static CMovePoint* GetMovePoint(int Idx);
private:
	static const std::string WAVE_BOSS_ENEMY_FILE;	//ウェーブボスのエネミーのファイル
	static const std::string WAVE_BOSS_BLOCK_FILE;	//ウェーブボスのブロックのファイル
	static const std::string WAVE_BOSS_WALL_FILE;	//ウェーブボスの壁のファイル
	static const std::string WAVE_BOSS_POINT_FILE;	//ウェーブボスポイントのファイル

	/**
	 * @brief 移動先読み込み
	 * @param [in]ファイルネーム
	 */
	void LoadPoint(const std::string* pFileName);
	static CMovePoint* m_pMovePoint[NUM_POINT];
};

#endif

