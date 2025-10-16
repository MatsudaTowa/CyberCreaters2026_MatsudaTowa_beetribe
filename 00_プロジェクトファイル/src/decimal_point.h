//=============================================
//
//小数点[decimal_point.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _DECIMAL_POINT_H_ //これが定義されてないとき

#define _DECIMAL_POINT_H_
#include "main.h"
#include "object2D.h"

//=============================================
//小数点クラス
//=============================================
class CDecimalPoint : public CObject2D
{
public:
	static const int PRIORITY = 29;  //描画順

	/**
	 * @brief コンストラクタ
	 * @param [in]プライオリティ
	 */
	CDecimalPoint(int nPriority = PRIORITY);
	/**
	 * @brief デストラクタ
	 */
	~CDecimalPoint()override;
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
	 * @return 小数点ポインタ
	 */
	static CDecimalPoint* Create(D3DXVECTOR3 pos,D3DXVECTOR2 size,D3DXCOLOR col);
private:
};
#endif