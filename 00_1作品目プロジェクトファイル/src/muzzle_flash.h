//=============================================
// 
//マズルフラッシュ[muzzle_flash.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _MUZZLE_FLASH_H_ //これが定義されてないとき

#define _MUZZLE_FLASH_H_
#include "main.h"
#include "billboard.h"

//=============================================
// マズルフラッシュクラス
//=============================================
class CMuzzleFlash : public CBillboard
{
public:
	static const int PRIORITY = 10; //描画順
	static const int LIFE = 10; //ライフ
	static const D3DXVECTOR3 SIZE; //サイズ

	/**
	 * @brief コンストラクタ
	 * @param [in]プライオリティ
	 */
	CMuzzleFlash(int nPriority = PRIORITY);
	/**
	 * @brief デストラクタ
	 */
	~CMuzzleFlash() override;
	/**
	 * @brief 初期化
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
	 * @return マズルフラッシュのポインタ
	 */
	static CMuzzleFlash* Create(D3DXVECTOR3 pos);
private:
	static const std::string TEXTURE_NAME;	//テクスチャの名前

	int m_nLife;
};
#endif