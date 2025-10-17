//=============================================
//
//残弾数表示「ammo_UI.h」
// Author松田永久
//
//=============================================
#ifndef _AMMO_UI_H_ //これが定義されてないとき
#define _AMMO_UI_H_
#include "main.h"
#include "object2D.h"
#include "number.h"
#include "player.h"
#include "player_UI_box.h"

//=============================================
//残弾数表示クラス
//=============================================
class CAmmo_UI
{
public:
	/**
	 * @brief コンストラクタ
	 * @param [in]プライオリティ
	 */
	CAmmo_UI();

	/**
	 * @brief デストラクタ
	 */
	~CAmmo_UI();

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
	 * @brief 現在の弾数UI
	 * @param [in]弾数
	 */
	void SetCurrentAmmo_UI(int nAmmo);

	/**
	 * @brief マガジンの弾数UI
	 * @param [in]弾数
	 */
	void SetDefaultAmmo_UI(int nAmmo);

private:
	static const int NUM_DIGIT = 2;  //桁数
	static constexpr float CURRENT_AMMO_DIGIT_SHIFT = 35.0f;  //桁ごとに座標をずらす
	static constexpr float DEFAULT_AMMO_DIGIT_SHIFT = 20.0f;  //桁ごとに座標をずらす

	static const D3DXVECTOR3 BOX_POS; //枠の位置
	static const D3DXVECTOR2 BOX_SIZE; //枠のサイズ

	static const D3DXVECTOR3 CURRENT_AMMO_POS; //現在の弾数の位置
	static const D3DXVECTOR2 CURRENT_AMMO_SIZE; //現在の弾数のサイズ

	static const D3DXVECTOR3 DEFAULT_AMMO_POS; //通常の弾数の位置
	static const D3DXVECTOR2 DEFAULT_AMMO_SIZE; //通常の弾数のサイズ

	int m_nDefaultAmmo; //残弾数の値
	D3DXVECTOR3 m_CurrentAmmoPos;
	D3DXVECTOR3 m_DefaultAmmoPos;
	CPlayerUIBox* m_pUIBox;
	CNumber_2D* m_pCurrentAmmo[NUM_DIGIT];
	CNumber_2D* m_pDefaultAmmo[NUM_DIGIT];
};

#endif // DEBUG