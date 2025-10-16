//=============================================
//
//ゲージ管理[gauge.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _GAUGE_H_ //これが定義されてないとき

#define _GAUGE_H_
#include "main.h"
#include "object2D.h"
#include "object3D.h"
#include "billboard.h"

//=============================================
//2Dゲージクラス
//=============================================
class CGauge_2D : public CObject2D
{
public:
	enum GAUGE2D_TYPE
	{
		GAUGE_TYPE_LIFE,
		GAUGE_TYPE_SENS,
		GAUGE_TYPE_MAX,
	};
	static const int PRIORITY = 28;  //描画順
	/**
	 * @brief コンストラクタ
	 * @param [in]プライオリティ
	 */
	CGauge_2D(int nPriority = PRIORITY);
	/**
	 * @brief デストラクタ
	 */
	~CGauge_2D()override;
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
	 * @brief ゲージの設定
	 * @param [in]ゲージのサイズ
	 */
	void SetGauge(D3DXVECTOR2 size);
	/**
	 * @brief ゲージの生成
	 * @param [in]位置
	 * @param [in]サイズ
	 * @param [in]タイプ
	 * @param [in]色
	 * @return ゲージポインタ
	 */
	static CGauge_2D* Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, GAUGE2D_TYPE type, D3DXCOLOR col);
private:
	static const std::string TEXTURE_NAME;	//テクスチャの名前

	GAUGE2D_TYPE m_type;
};

//=============================================
//体力ゲージクラス
//=============================================
class CGauge_Life : public CGauge_2D
{
public:
	CGauge_Life(int nPriority = PRIORITY);
	~CGauge_Life()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
};

//=============================================
//スタミナゲージクラス
//=============================================
class CGauge_Sens : public CGauge_2D
{
public:
	static const int SENS_PRIORITY = 29;  //描画順
	CGauge_Sens(int nPriority = SENS_PRIORITY);
	~CGauge_Sens()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
};
#endif