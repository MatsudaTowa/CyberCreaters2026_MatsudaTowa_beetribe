//=============================================
//
//床[field.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _FIELD_H_ //これが定義されてないとき

#define _FIELD_H_
#include "main.h"
#include "object3D.h"

//=============================================
// 床クラス
//=============================================
class CField : public CObject3D
{
public:

	static const int FIELD_PRIORITY = 3; //描画順
	/**
	 * @brief コンストラクタ
	 * @param [in]プライオリティ
	 */
	CField(int nPriority = FIELD_PRIORITY);
	/**
	 * @brief デストラクタ
	 */
	~CField()override;
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
	 * @return 床のポインタ
	 */
	static CField* Create(D3DXVECTOR3 pos,D3DXVECTOR3 size);
private:
	static const std::string TEXTURE_NAME;	//テクスチャの名前
};
#endif