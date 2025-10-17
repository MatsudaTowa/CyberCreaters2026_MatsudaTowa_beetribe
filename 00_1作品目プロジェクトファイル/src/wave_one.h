//=============================================
//
//1ウェーブ処理[wave_one.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _WAVE_ONE_H_ //これが定義されてないとき

#define _WAVE_ONE_H_
#include "main.h"
#include "block.h"
#include "enemy.h"
#include"wave.h"

//=============================================
//  1ウェーブクラス定義
//=============================================
class CWave_One :public CWave
{
public:
	/**
	 * @brief コンストラクタ
	 */
	CWave_One();
	/**
	 * @brief デストラクタ
	 */
	~CWave_One()override;
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
private:
	static const std::string WAVE_1_ENEMY_FILE;	//ウェーブ1のエネミーのファイル
	static const std::string WAVE_1_BLOCK_FILE;	//ウェーブ1のブロックのファイル
	static const std::string WAVE_1_WALL_FILE;	//ウェーブ1の壁のファイル
};

#endif

