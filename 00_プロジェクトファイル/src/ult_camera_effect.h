//=============================================
//
//ウルト時のカメラエフェクト「ult_camera_effect.h」
// Author松田永久
//
//=============================================
#ifndef _ULT_CAMERA_EFFECT_H_ //これが定義されてないとき
#define _ULT_CAMERA_EFFECT_H_
#include "main.h"
#include "object2D.h"

//=============================================
//ウルト時のカメラエフェクトクラス
//=============================================
class CUltCameraEffect :public CObject2D
{
public:
	static const int PRIORITY = 25; //描画順

	/**
	 * @brief コンストラクタ
	 * @param [in]プライオリティ
	 */
	CUltCameraEffect(int nPriority = PRIORITY);
	/**
	 * @brief デストラクタ
	 */
	~CUltCameraEffect() override;
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
	 * @return ウルトのカメラエフェクトポインタ
	 */
	static CUltCameraEffect* Create(D3DXVECTOR3 pos);

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
	static const std::string TEXTURE_NAME;			//テクスチャの名前
	static const D3DXCOLOR COLOR;					//初期色
	static constexpr float SUB_ALPHA = 0.01f;		//アルファ値減算

	float m_alpha; //アルファ値
};

#endif // _ULT_CAMERA_EFFECT_H_