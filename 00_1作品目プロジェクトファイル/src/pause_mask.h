//=============================================
//
//ポーズマスク処理[pausel_mask.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _PAUSE_MASK_H_ //これが定義されてないとき

#define _PAUSE_MASK_H_
#include "main.h"
#include "mask.h"

//=============================================
//ポーズマスククラス
//=============================================
class CPauseMask : public CMask
{
public:
	static const int MASK_PRIORITY = 28;
	/**
	 * @brief コンストラクタ
	 * @param [in]プライオリティ
	 */
	CPauseMask(int nPriority = MASK_PRIORITY);
	/**
	 * @brief デストラクタ
	 */
	~CPauseMask()override;
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