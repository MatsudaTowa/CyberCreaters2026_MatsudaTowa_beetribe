//=============================================
//
//ビルボード[billboard.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _BILLBOARD_H_ //これが定義されてないとき

#define _BILLBOARD_H_
#include "main.h"
#include "object3D.h"

//=============================================
//ビルボードクラス
//=============================================
class CBillboard : public CObject3D
{
public:
	/**
	 * @brief コンストラクタ
	 * @param [in]プライオリティ
	 */
	CBillboard(int nPriority);
	/**
	 * @brief デストラクタ
	 */
	~CBillboard()override;
	/**
	 * @brief 描画
	 */
	void Draw()override;
};
#endif