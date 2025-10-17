//=============================================
//
//スモークの表記[smoke_icon.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _SMOKE_ICON_H_ //これが定義されてないとき

#define _SMOKE_ICON_H_
#include "main.h"
#include "object2D.h"

//=============================================
//スモークの表記クラス
//=============================================
class CSmokeIcon : public CObject2D
{
public:
	static const int SMOKE_ICON_PRIORITY = 21;  //描画順

	/**
	 * @brief コンストラクタ
	 * @param [in]プライオリティ
	 */
	CSmokeIcon(int nPriority = SMOKE_ICON_PRIORITY);
	/**
	 * @brief デストラクタ
	 */
	~CSmokeIcon()override;
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
	 * @return 
	 */
	static CSmokeIcon* Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXCOLOR col);
private:
	static const std::string TEXTURE_NAME;	//テクスチャの名前
};
#endif