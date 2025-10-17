//=============================================
//
//ポーズをとじるUI[close_pause_UI.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _CLOSE_PAUSE_UI_H_ //これが定義されてないとき

#define _CLOSE_PAUSE_UI_H_
#include "main.h"
#include "object2D.h"

//=============================================
//ポーズをとじるUIクラス
//=============================================
class CClosePauseUI : public CObject2D
{
public:
	static const int PRIORITY = 29;  //描画順

	/**
	 * @brief コンストラクタ
	 * @param [in]プライオリティ
	 */
	CClosePauseUI(int nPriority = PRIORITY);
	/**
	 * @brief デストラクタ
	 */
	~CClosePauseUI()override;
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
	 * @return ポーズを閉じるUIポインタ
	 */
	static CClosePauseUI* Create(D3DXVECTOR3 pos, D3DXVECTOR2 size);
private:
	static const std::string TEXTURE_NAME;	//テクスチャの名前
};
#endif