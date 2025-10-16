//=============================================
//
//ポーズのUI_リトライ[pause_select_retry.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _PAUSE_SELECT_RETRY_H_ //これが定義されてないとき

#define _PAUSE_SELECT_RETRY_H_
#include "main.h"
#include "pause_select.h"

//=============================================
//ポーズ選択UI(retry)クラス
//=============================================
class CPauseSelectRetry : public CPauseSelect
{
public:
	/**
	 * @brief コンストラクタ
	 * @param [in]プライオリティ
	 */
	CPauseSelectRetry(int nPriority = PRIORITY);

	/**
	 * @brief デストラクタ
	 */
	~CPauseSelectRetry()override;
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
	static const std::string TEXTURE_NAME;	//テクスチャの名前
};
#endif