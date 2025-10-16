//=============================================
//
//ultが溜まったときにアイコンから出すエフェクト[ult_icon_effect.h]
//Author Matsuda Towa
//
//=============================================
#include "main.h"
#include "Object2D_anim.h"

#ifndef _ULT_ICON_EFFECT_H_ //これが定義されてないとき

#define _ULT_ICON_EFFECT_H_

//=============================================
// ULTのアイコンエフェクトクラス
//=============================================
class CUltIconEffect : public CObject2D_Anim
{
public:
	static const std::string TEXTURE_NAME;	//テクスチャの名前
	static const int PRIORITY = 20; //描画順
	static const int TEX_SPLIT_X = 4; //テクスチャの分割数
	static const int TEX_SPLIT_Y = 1; //テクスチャの分割数
	static const int ANIMATION_FRAME = 10; //アニメーションフレーム数

	/**
	 * @brief コンストラクタ
	 * @param [in]プライオリティ
	 */
	CUltIconEffect(int nPriority = PRIORITY);
	/**
	 * @brief デストラクタ
	 */
	~CUltIconEffect()override;
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
	 * @return ウルトが溜まった時のエフェクトポインタ
	 */
	static CUltIconEffect* Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXCOLOR col);
private:
};
#endif