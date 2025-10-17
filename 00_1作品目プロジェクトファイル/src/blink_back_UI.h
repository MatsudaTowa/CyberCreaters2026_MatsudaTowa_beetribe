//=============================================
//
//ブリンクの数字の背景[blink_back_UI.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _BLINK_BACK_UI_H_ //これが定義されてないとき

#define _BLINK_BACK_UI_H_
#include "main.h"
#include "object2D.h"

//=============================================
//ブリンクUIの背景クラス
//=============================================
class CBlinkBackUI : public CObject2D
{
public:
	static const int PRIORITY = 20;  //描画順
	/**
	 * @brief コンストラクタ
	 * @param [in]プライオリティ
	 */
	CBlinkBackUI(int nPriority = PRIORITY);
	/**
	 * @brief デストラクタ
	 */
	~CBlinkBackUI()override;
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
	 * @return ブリンクのUIの背景
	 */
	static CBlinkBackUI* Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXCOLOR col);
private:
	static const std::string TEXTURE_NAME;	//テクスチャの名前
};
#endif