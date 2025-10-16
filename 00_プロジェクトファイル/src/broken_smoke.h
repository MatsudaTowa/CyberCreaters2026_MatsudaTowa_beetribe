//=============================================
//
//ブロックから生成するスモーク処理[broken_somoke.h]
//Author Matsuda Towa
//
//=============================================
#include "main.h"
#include "smoke.h"

#ifndef _BROKEN_SMOKE_H_ //これが定義されてないとき

#define _BROKEN_SMOKE_H_

//=============================================
//ブロックから生成するスモーククラス
//=============================================
class CBrokenSmoke : public CSmoke
{
public:
	/**
	 * @brief コンストラクタ
	 * @param [in]プライオリティ
	 */
	CBrokenSmoke(int nPriority = SMOKE_PRIORITY);
	/**
	 * @brief デストラクタ
	 */
	~CBrokenSmoke()override;
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
	static constexpr float MOVE_X_MAX = 0.3f; //スモークの移動量の最大値_X
	static constexpr float MOVE_X_MIN = -0.3f; //スモークの移動量の最小値_X

	static constexpr float MOVE_Y_MAX = 0.7f; //スモークの移動量の最大値_Y
	static constexpr float MOVE_Y_MIN = 0.1f; //スモークの移動量の最小値_Y

	static constexpr float MOVE_Z_MAX = 0.1f; //スモークの移動量の最大値_Z
	static constexpr float MOVE_Z_MIN = 0.0f; //スモークの移動量の最小値_Z

	static const D3DXVECTOR3 SIZE;	//スモークのサイズ

	static const D3DXCOLOR COLOR;	//カラー
};

#endif