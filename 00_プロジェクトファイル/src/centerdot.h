//=============================================
//
//センタードット[centerdot.h]
//Author Matsuda Towa
//
//=============================================
#include "main.h"
#include "billboard.h"

#ifndef _CENTERDOT_H_ //これが定義されてないとき

#define _CENTERDOT_H_

//=============================================
//センタードットクラス
//=============================================
class CCenterDot : public CBillboard
{
public:
	static const int RETICLE_PRIORITY = 19; //描画順
	/**
	 * @brief コンストラクタ
	 * @param [in]プライオリティ
	 */
	CCenterDot(int nPriority = RETICLE_PRIORITY);
	/**
	 * @brief デストラクタ
	 */
	~CCenterDot()override;
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
	 * @return センタードットのポインタ
	 */
	static CCenterDot* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col);
private:
	static const std::string CENTERDOT_TEXTURE_NAME;	//テクスチャの名前
};

#endif