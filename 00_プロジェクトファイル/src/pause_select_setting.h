//=============================================
//
//ポーズのUI_セッティング[pause_select_setting.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _PAUSE_SELECT_SETTING_H_ //これが定義されてないとき

#define _PAUSE_SELECT_SETTING_H_
#include "main.h"
#include "pause_select.h"

//=============================================
//ポーズ選択UI(setting)クラス
//=============================================
class CPauseSelectSetting : public CPauseSelect
{
public:
	/**
	 * @brief コンストラクタ
	 * @param [in]プライオリティ
	 */
	CPauseSelectSetting(int nPriority = PRIORITY);

	/**
	 * @brief デストラクタ
	 */
	~CPauseSelectSetting()override;
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