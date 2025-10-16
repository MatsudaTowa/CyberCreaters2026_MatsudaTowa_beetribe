//=============================================
//
//敵を妨害するスモーク処理[tactical_somoke.h]
//Author Matsuda Towa
//
//=============================================
#include "main.h"
#include "smoke.h"

#ifndef _TACTICAL_SMOKE_H_ //これが定義されてないとき

#define _TACTICAL_SMOKE_H_

//=============================================
// 敵を妨害するスモーククラス
//=============================================
class CTacticalSmoke : public CSmoke
{
public:
	/**
	 * @brief コンストラクタ
	 * @param [in]プライオリティ
	 */
	CTacticalSmoke(int nPriority = SMOKE_PRIORITY);
	/**
	 * @brief デストラクタ
	 */
	~CTacticalSmoke()override;
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
private:
	static constexpr float MOVE_X_MAX = 1.5f; //スモークの移動量の最大値_X
	static constexpr float MOVE_X_MIN = -1.5f; //スモークの移動量の最小値_X

	static constexpr float MOVE_Y_MAX = 0.4f; //スモークの移動量の最大値_Y
	static constexpr float MOVE_Y_MIN = 0.0f; //スモークの移動量の最小値_Y

	static constexpr float MOVE_Z_MAX = 0.1f; //スモークの移動量の最大値_Z
	static constexpr float MOVE_Z_MIN = 0.0f; //スモークの移動量の最小値_Z

	static constexpr float X_DECREASE = 0.01f; //Xの移動量減少定数

	static const D3DXVECTOR3 SIZE; //スモークのサイズ
};

#endif