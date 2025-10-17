//=============================================
//
//当たり判定管理[colision.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _COLISION_H_ //これが定義されてないとき

#define _COLISION_H_

//=============================================
//当たり判定クラス
//=============================================
class CColision
{
public:
	enum COLISION
	{
		COLISON_NONE = 0, //何にも当たってない
		COLISON_X, //X方向に当たってる
		COLISON_Z, //X方向に当たってる
		COLISON_UNDER_Y, //Y方向(下)に当たってる
		COLISON_TOP_Y, //X方向(上)当たってる
		COLISION_CIRCLE,
	};

	struct CIRCLE
	{
		COLISION colision; //どう当たったか
		float CenterDistance; //中心点との距離
	};
	/**
	 * @brief コンストラクタ
	 */
	CColision();
	/**
	 * @brief デストラクタ
	 */
	~CColision();
	/**
	 * @brief ポリゴン同士の判定_X
	 * @param [in]当たる側の過去の位置
	 * @param [in]当たる側の位置
	 * @param [in]当たる側のサイズ
	 * @param [in]当たられる側の位置
	 * @param [in]当たられる側のサイズ
	 * @return どの方向に当たったか
	 */
	COLISION CheckColision_X(D3DXVECTOR3 Aoldpos, D3DXVECTOR3 Apos, D3DXVECTOR3 Asize, D3DXVECTOR3 Bpos, D3DXVECTOR3 Bsize);

	/**
	 * @brief モデル同士当たり判定_X
	 * @param [in]当たる側の過去の位置
	 * @param [in]当たる側の位置
	 * @param [in]当たる側の最小座標
	 * @param [in]当たる側の最大座標
	 * @param [in]当たられる側の位置
	 * @param [in]当たられる側の最小座標
	 * @param [in]当たられる側の最大座標
	 * @return どの方向に当たったか
	 */
	COLISION CheckColision_X(D3DXVECTOR3 Aoldpos, D3DXVECTOR3 Apos, D3DXVECTOR3 AMinpos, D3DXVECTOR3 AMaxPos,
		D3DXVECTOR3 Bpos, D3DXVECTOR3 BMinpos, D3DXVECTOR3 BMaxpos);

	/**
	 * @brief ポリゴン同士の判定_Y
	 * @param [in]当たる側の過去の位置
	 * @param [in]当たる側の位置
	 * @param [in]当たる側のサイズ
	 * @param [in]当たられる側の位置
	 * @param [in]当たられる側のサイズ
	 * @return どの方向に当たったか
	 */
	COLISION CheckColision_Y(D3DXVECTOR3 Aoldpos, D3DXVECTOR3 Apos, D3DXVECTOR3 Asize, D3DXVECTOR3 Bpos, D3DXVECTOR3 Bsize);
	/**
	 * @brief モデルとポリゴンの判定_Y
	 * @param [in]当たる側の過去の位置
	 * @param [in]当たる側の位置
	 * @param [in]当たる側の最小座標
	 * @param [in]当たる側の最大座標
	 * @param [in]当たられる側の位置
	 * @param [in]当たられる側のサイズ
	 * @return どの方向に当たったか
	 */
	COLISION CheckColision_Y(D3DXVECTOR3 Aoldpos, D3DXVECTOR3 Apos, D3DXVECTOR3 AMinpos, D3DXVECTOR3 AMaxpos, D3DXVECTOR3 Bpos, D3DXVECTOR3 Bsize);
	/**
	 * @brief モデル同士当たり判定_Y
	 * @param [in]当たる側の過去の位置
	 * @param [in]当たる側の位置
	 * @param [in]当たる側の最小座標
	 * @param [in]当たる側の最大座標
	 * @param [in]当たられる側の位置
	 * @param [in]当たられる側の最小座標
	 * @param [in]当たられる側の最大座標
	 * @return どの方向に当たったか
	 */
	COLISION CheckColision_Y(D3DXVECTOR3 Aoldpos, D3DXVECTOR3 Apos, D3DXVECTOR3 AMinpos, D3DXVECTOR3 AMaxPos,
		D3DXVECTOR3 Bpos, D3DXVECTOR3 BMinpos, D3DXVECTOR3 BMaxpos);

	/**
	 * @brief ポリゴン同士の判定_Z
	 * @param [in]当たる側の過去の位置
	 * @param [in]当たる側の位置
	 * @param [in]当たる側のサイズ
	 * @param [in]当たられる側の位置
	 * @param [in]当たられる側のサイズ
	 * @return どの方向に当たったか
	 */
	COLISION CheckColision_Z(D3DXVECTOR3 Aoldpos, D3DXVECTOR3 Apos, D3DXVECTOR3 Asize, D3DXVECTOR3 Bpos, D3DXVECTOR3 Bsize);
	/**
	 * @brief モデルとポリゴンの判定_Z
	 * @param [in]当たる側の過去の位置
	 * @param [in]当たる側の位置
	 * @param [in]当たる側の最小座標
	 * @param [in]当たる側の最大座標
	 * @param [in]当たられる側の位置
	 * @param [in]当たられる側のサイズ
	 * @return どの方向に当たったか
	 */
	COLISION CheckColision_Z(D3DXVECTOR3 Aoldpos, D3DXVECTOR3 Apos, D3DXVECTOR3 AMinpos, D3DXVECTOR3 AMaxpos, D3DXVECTOR3 Bpos, D3DXVECTOR3 Bsize);
	/**
	 * @brief モデル同士当たり判定_Z
	 * @param [in]当たる側の過去の位置
	 * @param [in]当たる側の位置
	 * @param [in]当たる側の最小座標
	 * @param [in]当たる側の最大座標
	 * @param [in]当たられる側の位置
	 * @param [in]当たられる側の最小座標
	 * @param [in]当たられる側の最大座標
	 * @return どの方向に当たったか
	 */
	COLISION CheckColision_Z(D3DXVECTOR3 Aoldpos, D3DXVECTOR3 Apos, D3DXVECTOR3 AMinpos, D3DXVECTOR3 AMaxPos,
		D3DXVECTOR3 Bpos, D3DXVECTOR3 BMinpos, D3DXVECTOR3 BMaxpos);

	/**
	 * @brief モデル同士の判定_球
	 * @param [in]当たる側の位置
	 * @param [in]当たる側の最小座標
	 * @param [in]当たる側の最大座標
	 * @param [in]当たられる側の位置
	 * @param [in]当たられる側の最小座標
	 * @param [in]当たられる側の最大座標
	 * @return どの方向に当たったか
	 */
	COLISION CheckColisionSphere(D3DXVECTOR3 Apos, D3DXVECTOR3 AMinpos, D3DXVECTOR3 AMaxpos, D3DXVECTOR3 Bpos, D3DXVECTOR3 BMinpos, D3DXVECTOR3 BMaxpos);

	/**
	 * @brief 円の判定
	 * @param [in]当たる側の位置
	 * @param [in]半径
	 * @param [in]当たられる側の位置
	 * @return 円のヒット情報
	 */
	CIRCLE CheckColisionCircle(D3DXVECTOR3 Apos, float Radius, D3DXVECTOR3 Bpos);

	/**
	 * @brief ポリゴンとモデル当たり判定チェック関数_球
	 * @param [in]当たる側の位置
	 * @param [in]当たる側のサイズ
	 * @param [in]当たられる側の位置
	 * @param [in]当たられる側の最小座標
	 * @param [in]当たられる側の最大座標
	 * @return どの方向に当たったか
	 */
	COLISION CheckPolygonModelColisionSphere(D3DXVECTOR3 Apos, D3DXVECTOR3 ASize, D3DXVECTOR3 Bpos, D3DXVECTOR3 BMinpos, D3DXVECTOR3 BMaxpos);
	/**
	 * @brief ポリゴンとモデルの当たり判定_X
	 * @param [in]当たる側の位置
	 * @param [in]当たる側のサイズ
	 * @param [in]当たられる側の位置
	 * @param [in]当たられる側の最小座標
	 * @param [in]当たられる側の最大座標
	 * @return どの方向に当たったか
	 */
	COLISION CheckPolygonModelColision_X(D3DXVECTOR3 Apos, D3DXVECTOR3 ASize, D3DXVECTOR3 Bpos, D3DXVECTOR3 BMinpos, D3DXVECTOR3 BMaxpos);
	/**
	 * @brief ポリゴンとモデルの当たり判定_Z
	 * @param [in]当たる側の位置
	 * @param [in]当たる側のサイズ
	 * @param [in]当たられる側の位置
	 * @param [in]当たられる側の最小座標
	 * @param [in]当たられる側の最大座標
	 * @return どの方向に当たったか
	 */
	COLISION CheckPolygonModelColision_Z(D3DXVECTOR3 Apos, D3DXVECTOR3 ASize, D3DXVECTOR3 Bpos, D3DXVECTOR3 BMinpos, D3DXVECTOR3 BMaxpos);
	/**
	 * @brief ポリゴンとモデルの当たり判定_埋まってるか
	 * @param [in]当たる側の位置
	 * @param [in]当たる側のサイズ
	 * @param [in]当たられる側の位置
	 * @param [in]当たられる側の最小座標
	 * @param [in]当たられる側の最大座標
	 * @return どの方向に当たったか
	 */
	COLISION CheckPolygonFillColision(D3DXVECTOR3 Apos, D3DXVECTOR3 ASize, D3DXVECTOR3 Bpos, D3DXVECTOR3 BMinpos, D3DXVECTOR3 BMaxpos);

	/**
	 * @brief ポリゴンとモデル貫通判定チェック関数_x
	 * @param [in]当たる側の過去の位置
	 * @param [in]当たる側の位置
	 * @param [in]当たられる側の位置
	 * @param [in]当たられる側の最小座標
	 * @param [in]当たられる側の最大座標
	 * @return どの方向に当たったか
	 */
	COLISION CheckPolygonModelPenetration_X(D3DXVECTOR3 Aoldpos, D3DXVECTOR3 Apos, D3DXVECTOR3 Bpos, D3DXVECTOR3 BMinpos, D3DXVECTOR3 BMaxpos);

	/**
	 * @brief ポリゴンとモデル貫通判定チェック関数_z
	 * @param [in]当たる側の過去の位置
	 * @param [in]当たる側の位置
	 * @param [in]当たられる側の位置
	 * @param [in]当たられる側の最小座標
	 * @param [in]当たられる側の最大座標
	 * @return どの方向に当たったか
	 */
	COLISION CheckPolygonModelPenetration_Z(D3DXVECTOR3 Aoldpos, D3DXVECTOR3 Apos, D3DXVECTOR3 Bpos, D3DXVECTOR3 BMinpos, D3DXVECTOR3 BMaxpos);

	/**
	 * @brief 2Dポリゴン当たり判定チェック関数
	 * @param [in]当たる側の現在の位置
	 * @param [in]当たる側のサイズ
	 * @param [in]当たられる側の位置
	 * @param [in]当たられる側のサイズ
	 * @return 当たっているか
	 */
	bool Check2DPolygonColision(D3DXVECTOR3 Apos, D3DXVECTOR2 ASize, D3DXVECTOR3 Bpos, D3DXVECTOR2 BSize);
};
#endif