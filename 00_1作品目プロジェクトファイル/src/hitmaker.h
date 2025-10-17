//=============================================
//
//ヒットマーカー[hitmaker.h]
//Author Matsuda Towa
//
//=============================================
#include "main.h"
#include "billboard.h"

#ifndef _HITMAKER_H_ //これが定義されてないとき

#define _HITMAKER_H_

//=============================================
//ヒットマーカークラス
//=============================================
class CHitMaker : public CBillboard
{
public:
	static const int RETICLE_PRIORITY = 18; //描画順

	/**
	 * @brief コンストラクタ
	 * @param [in]プライオリティ
	 */
	CHitMaker(int nPriority = RETICLE_PRIORITY);
	/**
	 * @brief デストラクタ
	 */
	~CHitMaker()override;
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
	 * @param [in]色
	 * @return ヒットマーカーのポインタ
	 */
	static CHitMaker* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col);
private:
	static const std::string HITMARKER_DOT_TEXTURE_NAME;	//テクスチャの名前

	static const int HITMARKER_LIFE = 30; //体力

	static constexpr float FADE_OUT = 0.05f; //アルファ値減少

	/**
	 * @brief 色設定
	 * @param [in]色
	 */
	void HitColor(D3DXCOLOR col);

	int m_nLife;
};

#endif