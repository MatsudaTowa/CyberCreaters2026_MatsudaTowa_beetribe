//=============================================
//
//ウルト範囲処理[ult_range.h]
//Author Matsuda Towa
//
//=============================================
#include "main.h"
#include "objectX.h"
#include "ult_effect.h"

#ifndef _ULT_RANGE_H_ //これが定義されてないとき

#define _ULT_RANGE_H_

//=============================================
// ウルトの範囲クラス
//=============================================
class CUltRange
{
public:
	/**
	 * @brief コンストラクタ
	 */
	CUltRange();
	/**
	 * @brief デストラクタ
	 */
	~CUltRange();
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
	 * @brief 生成
	 * @param [in]位置
	 * @return ウルトの範囲ポインタ
	 */
	static CUltRange* Create(D3DXVECTOR3 pos);

	/**
	 * @brief 持続時間取得
	 * @return 持続時間
	 */
	inline int& GetLife()
	{
		return m_nLife;
	}
private:
	static const int LIFE = 10;
	static const int MAX_DAMAGE =10;
	static constexpr float RADIUS = 20.0f;
	D3DXVECTOR3 m_pos;
	int m_nLife;

	CUltEffect* m_pUltEffect;
};

#endif