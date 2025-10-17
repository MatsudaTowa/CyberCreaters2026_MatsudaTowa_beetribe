//=============================================
//
//ウルトエフェクト「ult_effect.h」
// Author松田永久
//
//=============================================
#ifndef _ULT_EFFECT_H_ //これが定義されてないとき

#define _ULT_EFFECT_H_
#include "main.h"
#include "object3D.h"

//=============================================
//ウルトエフェクトクラス
//=============================================
class CUltEffect : public CObject3D
{
public:
	static const int PRIORITY = 12; //描画順

	/**
	 * @brief コンストラクタ
	 * @param [in]プライオリティ
	 */
	CUltEffect(int nPriority = PRIORITY);
	/**
	 * @brief デストラクタ
	 */
	~CUltEffect()override;
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
	 * @return ウルトのエフェクトポインタ
	 */
	static CUltEffect* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
private:
	static const std::string TEXTURE_NAME;	//テクスチャの名前
	static const D3DXCOLOR COLOR;	//色
};
#endif