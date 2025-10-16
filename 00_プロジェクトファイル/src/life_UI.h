//=============================================
//
//体力表示「life_UI.h」
// Author松田永久
//
//=============================================
#ifndef _LIFE_UI_H_ //これが定義されてないとき
#define _LIFE_UI_H_
#include "main.h"
#include "object2D.h"
#include "number.h"
#include "player_UI_box.h"
#include "gauge.h"

//=============================================
//体力表示クラス
//=============================================
class CLife_UI
{
public:
	static const int NUM_DIGIT = 3;  //桁数
	static constexpr float DIGIT_SHIFT = 18.0f;  //桁ごとに座標をずらす
	/**
	 * @brief コンストラクタ
	 */
	CLife_UI();
	/**
	 * @brief デストラクタ
	 */
	~CLife_UI();
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
	 * @brief ライフUI設定
	 * @param [in]ライフ
	 */
	void SetLife_UI(int nLife);

	/**
	 * @brief 数字設定
	 * @param [in]ライフ
	 */
	void SetNumber(int nLife);

private:
	static const D3DXVECTOR3 BOX_POS; //枠の位置
	static const D3DXVECTOR2 BOX_SIZE; //枠のサイズ

	static const D3DXVECTOR3 GAUGE_POS; //ゲージの位置
	static const D3DXVECTOR2 GAUGE_SIZE; //ゲージのサイズ

	static const D3DXVECTOR3 NUM_POS; //数字の位置
	static const D3DXVECTOR2 NUM_SIZE; //数字のサイズ
	CNumber_2D* m_pNumber[NUM_DIGIT];
	CPlayerUIBox* m_pUIBox;
	CGauge_2D*m_pGauge;
	D3DXVECTOR3 m_NumPos;
	int m_nLife; //体力の値

};

#endif // DEBUG