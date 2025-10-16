//=============================================
//
//死亡アイコン[death_icon.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _DEATH_ICON_H_ //これが定義されてないとき

#define _DEATH_ICON_H_
#include "main.h"
#include "object2D.h"

//=============================================
//死亡アイコンクラス
//=============================================
class CDeathIcon : public CObject2D
{
public:
	static const int PRIORITY = 27;  //描画順

	/**
	 * @brief コンストラクタ
	 * @param [in]プライオリティ
	 */
	CDeathIcon(int nPriority = PRIORITY);
	/**
	 * @brief デストラクタ
	 */
	~CDeathIcon()override;
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
	 * @param [in]サイズ
	 * @param [in]色
	 * @return 死亡アイコンのポインタ
	 */
	static CDeathIcon* Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXCOLOR col);
private:
	static const std::string TEXTURE_NAME;	//テクスチャの名前
};
#endif
