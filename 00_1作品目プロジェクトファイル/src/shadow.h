//=============================================
//
//影「shadow.h」
// Author松田永久
//
//=============================================
#ifndef _SHADOW_H_ //これが定義されてないとき

#define _SHADOW_H_
#include "main.h"
#include "object3D.h"

//=============================================
//影クラス
//=============================================
class CShadow : public CObject3D
{
public:
	static const int SHADOW_PRIORITY = 9; //描画順

	/**
	 * @brief コンストラクタ
	 * @param [in]プライオリティ
	 */
	CShadow(int nPriority = SHADOW_PRIORITY);
	/**
	 * @brief デストラクタ
	 */
	~CShadow()override;
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
	 * @return 影のポインタ
	 */
	static CShadow* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
private:
	static const std::string TEXTURE_NAME;	//テクスチャの名前
};
#endif