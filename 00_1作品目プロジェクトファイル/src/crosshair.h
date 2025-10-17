//=============================================
//
//クロスヘア[crosshair.h]
//Author Matsuda Towa
//
//=============================================
#include "main.h"
#include "billboard.h"

#ifndef _CROSSHAIR_H_ //これが定義されてないとき

#define _CROSSHAIR_H_

//=============================================
//クロスヘアクラス
//=============================================
class CCrossHair : public CBillboard
{
public:
	static const int RETICLE_PRIORITY = 18; //描画順

	/**
	 * @brief コンストラクタ
	 * @param [in]プライオリティ
	 */
	CCrossHair(int nPriority = RETICLE_PRIORITY);
	/**
	 * @brief デストラクタ
	 */
	~CCrossHair()override;
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
	 * @param [in]サイズ
	 * @param [in]色
	 * @return クロスヘアポインタ
	 */
	static CCrossHair* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col);
private:
	static const std::string CROSSHAIR_TEXTURE_NAME;	//テクスチャの名前

	D3DXVECTOR3 m_move; //移動量
};

#endif