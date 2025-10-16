//=============================================
//
//タックルチャージ中のエフェクト[tackle_charge.h]
//Author Matsuda Towa
//
//=============================================
#include "main.h"
#include "billboard.h"

#ifndef _TACKLE_CHARGE_H_ //これが定義されてないとき

#define _TACKLE_CHARGE_H_

//=============================================
// タックルチャージエフェクトクラス
//=============================================
class CTackleCharge : public CBillboard
{
public:
	static const int PRIORITY = 10; //描画順
	static const D3DXVECTOR3 SIZE; //サイズ
	/**
	 * @brief コンストラクタ
	 * @param [in]プライオリティ
	 */
	CTackleCharge(int nPriority = PRIORITY);
	/**
	 * @brief デストラクタ
	 */
	~CTackleCharge()override;
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
	 * @return タックルチャージ中エフェクトポインタ
	 */
	static CTackleCharge* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col);

private:
	static const std::string TEXTURE_NAME; //テクスチャの名前
};

#endif