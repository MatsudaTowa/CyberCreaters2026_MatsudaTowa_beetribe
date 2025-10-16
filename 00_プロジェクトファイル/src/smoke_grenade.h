//=============================================
//
//スモークグレネード処理[somoke_grenade.h]
//Author Matsuda Towa
//
//=============================================
#include "main.h"
#include "objectX.h"
#include "smoke.h"

#ifndef _SMOKE_GRENADE_H_ //これが定義されてないとき

#define _SMOKE_GRENADE_H_

//=============================================
// スモークグレネードクラス
//=============================================
class CSmokeGrenade : public CObjectX
{
public:
	static const int SMOKE_PRIORITY = 24; //描画順

	/**
	 * @brief コンストラクタ
	 * @param [in]プライオリティ
	 */
	CSmokeGrenade(int nPriority = SMOKE_PRIORITY);
	/**
	 * @brief デストラクタ
	 */
	~CSmokeGrenade()override;
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
	 * @brief 描画
	 */
	void Draw()override;

	/**
	 * @brief 生成
	 * @param [in]位置
	 * @param [in]移動量
	 * @param [in]方向
	 * @return スモークグレネードのポインタ
	 */
	static CSmokeGrenade* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot);

private:
	static const char* MODEL_NAME;	//モデルの名前
	static const int CREATE_SMOKE_NUM = 100; //生成するスモークの数
	/**
	 * @brief 地面と接触したか
	 */
	void HitField();
	D3DXVECTOR3 m_oldpos;
	D3DXVECTOR3 m_move;
	bool m_bBoot; //グレネードが起動したか
	int m_NumCreate; //何個生成したかカウントする変数
};

#endif