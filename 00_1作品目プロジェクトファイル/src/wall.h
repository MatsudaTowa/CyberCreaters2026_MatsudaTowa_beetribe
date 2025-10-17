//=============================================
//
//壁の処理[wall.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _WALL_H_ //これが定義されてないとき

#define _WALL_H_
#include "main.h"
#include "object3D.h"

//=============================================
//壁クラス
//=============================================
class CWall : public CObject3D
{
public:
	static const int WALL_PRIORITY = 3; //描画順
	/**
	 * @brief コンストラクタ
	 * @param [in]プライオリティ
	 */
	CWall(int nPriority = WALL_PRIORITY);
	/**
	 * @brief デストラクタ
	 */
	~CWall()override;
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
	 * @param [in]方向
	 * @param [in]サイズ
	 * @return 壁のポインタ
	 */
	static CWall* Create(D3DXVECTOR3 pos,D3DXVECTOR3 rot, D3DXVECTOR3 size);
private:
	static const std::string TEXTURE_NAME;	//テクスチャの名前
};
#endif