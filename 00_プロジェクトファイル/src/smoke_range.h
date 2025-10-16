//=============================================
//
//スモーク範囲処理[somoke_range.h]
//Author Matsuda Towa
//
//=============================================
#include "main.h"
#include "objectX.h"
#include "smoke.h"

#ifndef _SMOKE_RANGE_H_ //これが定義されてないとき

#define _SMOKE_RANGE_H_

//=============================================
// スモークの範囲クラス
//=============================================
class CSmokeRange : public CObjectX
{
public:
	static const int SMOKE_RANGE_PRIORITY = 15; //描画順

	/**
	 * @brief コンストラクタ
	 * @param [in]プライオリティ
	 */
	CSmokeRange(int nPriority = SMOKE_RANGE_PRIORITY);
	/**
	 * @brief デストラクタ
	 */
	~CSmokeRange()override;
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
	 * @return スモークの範囲のポインタ
	 */
	static CSmokeRange* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

private:
	static const char* MODEL_NAME;	//モデルの名前
	int m_nLife;
};

#endif