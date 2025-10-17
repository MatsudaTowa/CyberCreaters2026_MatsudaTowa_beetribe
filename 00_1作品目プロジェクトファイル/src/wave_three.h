//=============================================
//
//3ウェーブ処理[wave_three.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _WAVE_THREE_H_ //これが定義されてないとき

#define _WAVE_THREE_H_
#include "main.h"
#include "block.h"
#include "enemy.h"
#include"wave.h"

//=============================================
//  3ウェーブクラス定義
//=============================================
class CWave_Three :public CWave
{
public:
	static const std::string WAVE_3_ENEMY_FILE;	//ウェーブ3のエネミーのファイル
	static const std::string WAVE_3_BLOCK_FILE;	//ウェーブ3のブロックのファイル
	static const std::string WAVE_3_WALL_FILE;	//ウェーブ3の壁のファイル
	/**
	 * @brief コンストラクタ
	 */
	CWave_Three();
	/**
	 * @brief デストラクタ
	 */
	~CWave_Three()override;
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

