//=============================================
//
//マスク処理[mask.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _MASK_H_ //これが定義されてないとき

#define _MASK_H_
#include "main.h"
#include "object2D.h"

//=============================================
//マスククラス
//=============================================
class CMask : public CObject2D
{
public:
	static const int MASK_PRIORITY = 14;  //描画順
	static const int REFARENCE_VALUE = 2;  //描画参照値

	/**
	 * @brief コンストラクタ
	 * @param [in]プライオリティ
	 */
	CMask(int nPriority = MASK_PRIORITY);
	/**
	 * @brief デストラクタ
	 */
	~CMask()override;
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
	 * @return マスクポインタ
	 */
	static CMask* Create(CMask* mask);
private:
};
#endif