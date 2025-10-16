//=============================================
//
//ヒット時のカメラエフェクト「hit_camera_effect.h」
// Author松田永久
//
//=============================================
#ifndef _HIT_CAMERA_EFFECT_H_ //これが定義されてないとき
#define _HIT_CAMERA_EFFECT_H_
#include "main.h"
#include "object2D.h"

//=============================================
//ヒット時のカメラエフェクトクラス
//=============================================
class CHitCameraEffect:public CObject2D
{
public:
	static const int PRIORITY = 27; //描画順

	enum HIT_EFFECT_STAGE
	{
		MILD, //軽度
		MODERATE, //中
		SEVERE, //重症
	};

	/**
	 * @brief コンストラクタ
	 * @param [in]プライオリティ
	 */
	CHitCameraEffect(int nPriority = PRIORITY);
	/**
	 * @brief デストラクタ
	 */
	~CHitCameraEffect() override;
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
	 * @param [in]ダメージの量
	 * @return カメラのヒットエフェクト
	 */
	static CHitCameraEffect* Create(D3DXVECTOR3 pos, HIT_EFFECT_STAGE stage);

	/**
	 * @brief アルファ値減少
	 */
	void SubAlpha();

	/**
	 * @brief アルファ値取得
	 * @return アルファ値
	 */
	inline float& GetAlpha()
	{
		return m_alpha;
	}
private:
	static const std::string TEXTURE_NAME_SEVERE;	//重症テクスチャの名前
	static const D3DXCOLOR COLOR;					//初期色
	static constexpr float SUB_ALPHA = 0.01f;		//アルファ値減算

	float m_alpha; //アルファ値
};

#endif // _HIT_CAMERA_EFFECT_H_