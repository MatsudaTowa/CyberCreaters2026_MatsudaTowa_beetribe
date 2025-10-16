//=============================================
//
//ダッシュ時にキャラクターの前方に出すエフェクト[dash_effect.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _DASH_EFFECT_H_ //これが定義されてないとき

#define _DASH_EFFECT_H_
#include "main.h"
#include "objectX.h"

//=============================================
//タックルエフェクトクラス
//=============================================
class CDashEffect : public CObjectX
{
public:
	static const int PRIORITY = 11; //描画順

	/**
	 * @brief コンストラクタ
	 * @param [in]プライオリティ
	 */
	CDashEffect(int nPriority = PRIORITY);
	/**
	 * @brief デストラクタ
	 */
	~CDashEffect()override;
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
	 * @param [in]方向
	 * @return エフェクトポインタ
	 */
	static CDashEffect* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
private:
	static const char* MODEL_NAME;	//モデルの名前
	static const D3DXVECTOR3 SCALE;
	static const D3DXCOLOR COLOR;

};
#endif