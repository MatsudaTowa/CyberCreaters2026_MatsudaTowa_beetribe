//=============================================
//
//通常の敵の処理[normal_enemy.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _NORMAL_ENEMY_H_ //これが定義されてないとき

#define _NORMAL_ENEMY_H_
#include "main.h"
#include "model_parts.h"
#include "enemy.h"
#include "enemy_behavior.h"

//=============================================
//通常のエネミークラス
//=============================================
class CNormalEnemy :public CEnemy
{
public:
	static const int MAX_KEY = 20; //キー最大数
	static const int NUM_MOTION = 3;
	static const int ENEMY_PRIORITY = 8; //描画順
	static const int DEFAULT_LIFE = 80; //ライフ

	//モーションの種類の列挙
	enum Motion_Type
	{
		MOTION_NEUTRAL = 0,
		MOTION_MOVE,
		MOTION_ATTACK,
		MOTION_STAN,
		MOTION_MAX,
	};
	/**
	 * @brief コンストラクタ
	 * @param [in]プライオリティ
	 */
	CNormalEnemy(int nPriority = ENEMY_PRIORITY);
	/**
	 * @brief デストラクタ
	 */
	~CNormalEnemy() override;
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
	 * @brief ウルトのヒット判定
	 * @param [in]ウルトの位置
	 * @param [in]ダメージ
	 */
	void MediumUltHit(D3DXVECTOR3 UltPos, int nDamage)override;
private:

	//エネミーの移動関連
	static const D3DXVECTOR3 SHADOW_SIZE; //影のサイズ

	Motion_Type m_Motion; //モーションの種類
};

#endif