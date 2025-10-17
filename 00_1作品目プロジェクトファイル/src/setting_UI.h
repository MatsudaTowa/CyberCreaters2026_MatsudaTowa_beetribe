//=============================================
//
//設定のUI「setting_UI.h」
// Author松田永久
//
//=============================================
#ifndef _SETTING_UI_H_ //これが定義されてないとき
#define _SETTING_UI_H_
#include "main.h"
#include "object2D.h"
#include "sens_number.h"
#include "gauge.h"
#include "pause_mask.h"
#include "decimal_point.h"
#include "sens_txt_UI.h"

//=============================================
//設定UIクラス
//=============================================
class CSetting_UI
{
public:
	static const int NUM_DIGIT = 3;  //桁数
	static constexpr float DIGIT_SHIFT = 33.0f;  //桁ごとに座標をずらす
	/**
	 * @brief コンストラクタ
	 */
	CSetting_UI();
	/**
	 * @brief デストラクタ
	 */
	~CSetting_UI();
	/**
	 * @brief 初期化
	 * @return 成功したか
	 */
	HRESULT Init();
	/**
	 * @brief 終了
	 */
	void Uninit();
	/**
	 * @brief 更新
	 */
	void Update();

	/**
	 * @brief 感度UI設定
	 * @param [in]感度
	 */
	void SetSens_UI(float sens);

	/**
	 * @brief 感度の数字設定
	 * @param [in]感度
	 */
	void SetNumber(float sens);

private:
	static const D3DXVECTOR3 GAUGE_POS; //ゲージの位置
	static const D3DXVECTOR2 GAUGE_SIZE; //ゲージのサイズ

	static const D3DXVECTOR3 NUM_POS; //数字の位置
	static const D3DXVECTOR2 NUM_SIZE; //数字のサイズ

	static const D3DXVECTOR3 DECIMAL_POINT_POS; //小数点の位置
	static const D3DXVECTOR2 DECIMAL_POINT__SIZE; //小数点のサイズ

	static const D3DXVECTOR3 TXT_POS;	//文字の位置
	static const D3DXVECTOR2 TXT_SIZE;	//文字のサイズ
	CMask* m_pMask;
	CDecimalPoint* m_pDecimalPoint;
	CNumber_2D* m_pNumber[NUM_DIGIT];
	CGauge_2D* m_pGauge;
	CSensTxtUI* m_pTxtUI;
	D3DXVECTOR3 m_NumPos;
};

#endif // DEBUG