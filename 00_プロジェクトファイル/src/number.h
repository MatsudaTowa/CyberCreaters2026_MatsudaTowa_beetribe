//=============================================
//
//数字管理「number.h」
// Author松田永久
//
//=============================================
#ifndef _NUMBER_H_ //これが定義されてないとき
#define _NUMBER_H_
#include "main.h"
#include "object2D.h"
#include "billboard.h"

//=============================================
//ナンバークラス2D
//=============================================
class CNumber_2D:public CObject2D
{
public:
	static const int NUMBER_PRIORITY = 21;  //描画順
	/**
	 * @brief コンストラクタ
	 * @param [in]プライオリティ
	 */
	CNumber_2D(int nPriority = NUMBER_PRIORITY);
	/**
	 * @brief デストラクタ
	 */
	~CNumber_2D()override;
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
	 * @param [in]確保するナンバーのポインタ
	 * @return ナンバー2D
	 */
	static CNumber_2D* Create(D3DXVECTOR3 pos ,D3DXVECTOR2 size,CNumber_2D* number);

	/**
	 * @brief 数字の設定
	 * @param [in]数字の最小座標
	 * @param [in]数字の最大座標
	 * @param [in]色
	 */
	void SetNumber(float fNumPos1,float fNumPos2,D3DXCOLOR col);
	/**
	 * @brief 数字の頂点生成
	 */
	void NumberVtx();

private:
	static const std::string TEXTURE_NAME;	//テクスチャの名前

	D3DXVECTOR2 m_mintex; //テクスチャの最小座標
	D3DXVECTOR2 m_maxtex; //テクスチャの最大座標
	D3DXCOLOR m_col; //カラー
};

//=============================================
//ナンバークラス3D
//=============================================
class CNumber_3D :public CBillboard
{
public:
	static const int NUMBER_PRIORITY = 20;  //描画順
	/**
	 * @brief コンストラクタ
	 * @param [in]プライオリティ
	 */
	CNumber_3D(int nPriority = NUMBER_PRIORITY);
	/**
	 * @brief デストラクタ
	 */
	~CNumber_3D()override;
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
	 * @return ナンバー3Dのポインタ
	 */
	static CNumber_3D* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);

	/**
	 * @brief 数字の設定
	 * @param [in]数字の最小座標
	 * @param [in]数字の最大座標
	 * @param [in]色
	 */
	void SetNumber(float fNumPos1, float fNumPos2, D3DXCOLOR col);
	/**
	 * @brief 数字の頂点生成
	 */
	void NumberVtx();

private:
	static const std::string TEXTURE_NAME;	//テクスチャの名前

	D3DXVECTOR2 m_mintex; //テクスチャの最小座標
	D3DXVECTOR2 m_maxtex; //テクスチャの最大座標
	D3DXCOLOR m_col; //カラー
};

#endif // DEBUG