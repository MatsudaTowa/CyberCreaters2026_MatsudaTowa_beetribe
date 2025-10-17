//=============================================
//
//ポーズのUI_コンティニュー[pause_select_continue.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _PAUSE_SELECT_CONTINUE_H_ //これが定義されてないとき

#define _PAUSE_SELECT_CONTINUE_H_
#include "main.h"
#include "pause_select.h"

//=============================================
//ポーズ選択UIクラス
//=============================================
class CPauseSelectContinue : public CPauseSelect
{
public:
	/**
	 * @brief コンストラクタ
	 * @param [in]プライオリティ
	 */
	CPauseSelectContinue(int nPriority = PRIORITY);

	/**
	 * @brief デストラクタ
	 */
	~CPauseSelectContinue()override;
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