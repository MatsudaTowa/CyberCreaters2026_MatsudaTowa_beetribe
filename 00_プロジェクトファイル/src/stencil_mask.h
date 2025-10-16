//=============================================
//
//ステンシルマスク処理[stencil_mask.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _STENCIL_MASK_H_ //これが定義されてないとき

#define _STENCIL_MASK_H_
#include "main.h"
#include "mask.h"

//=============================================
//ステンシルマスククラス
//=============================================
class CStencilMask : public CMask
{
public:
	static const int REFARENCE_VALUE = 2;  //描画参照値

	/**
	 * @brief コンストラクタ
	 * @param [in]プライオリティ
	 */
	CStencilMask(int nPriority = MASK_PRIORITY);
	/**
	 * @brief デストラクタ
	 */
	~CStencilMask()override;
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
	static const D3DXCOLOR COLOR;
};
#endif