//=============================================
// 
//敵が徘徊する際に向かうポイント[move_point.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _MOVE_POINT_ //これが定義されてないとき

#define _MOVE_POINT_
#include "main.h"
#include "billboard.h"

//=============================================
// 探索ポイントクラス
//=============================================
class CMovePoint : public CBillboard
{
public:
	static const int POINT_PRIORITY = 8; //描画順

	/**
	 * @brief コンストラクタ
	 * @param [in]プライオリティ
	 */
	CMovePoint(int nPriority = POINT_PRIORITY);
	/**
	 * @brief デストラクタ
	 */
	~CMovePoint() override;
	/**
	 * @brief 初期か
	 * @return 成功したか
	 */
	HRESULT Init() override;
	/**
	 * @brief 終了
	 */
	void Uninit() override;
	/**
	 * @brief 更新
	 */
	void Update() override;
	/**
	 * @brief 描画
	 */
	void Draw() override;
	/**
	 * @brief 生成
	 * @param [in]位置
	 * @return 移動ポイントのポインタ
	 */
	static CMovePoint* Create(D3DXVECTOR3 pos);

	/**
	 * @brief 数取得
	 * @return ポイントの数
	 */
	static int& GetNumPoint()
	{
		return m_NumPoint;
	};
private:
	static constexpr float POINT_SIZE = 10.0f; //サイズ

	static int m_NumPoint; //何個あるか
};
#endif