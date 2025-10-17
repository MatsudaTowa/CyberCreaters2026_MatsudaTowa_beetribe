//=============================================
//
//2ウェーブ処理[wave_two.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _WAVE_TWO_H_ //これが定義されてないとき

#define _WAVE_TWO_H_
#include "main.h"
#include "block.h"
#include "enemy.h"
#include"wave.h"

//=============================================
//  2ウェーブクラス定義
//=============================================
class CWave_Two :public CWave
{
public:
	static const std::string WAVE_2_ENEMY_FILE;	//ウェーブ2のエネミーのファイル
	static const std::string WAVE_2_BLOCK_FILE;	//ウェーブ2のブロックのファイル
	static const std::string WAVE_2_WALL_FILE;	//ウェーブ2の壁のファイル
	/**
	 * @brief コンストラクタ
	 */
	CWave_Two();
	/**
	 * @brief デストラクタ
	 */
	~CWave_Two()override;
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
};

#endif

