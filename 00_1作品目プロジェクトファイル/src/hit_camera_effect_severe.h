//=============================================
//
//ヒット時のカメラエフェクト(重傷時)「hit_camera_effect_severe.h」
// Author松田永久
//
//=============================================
#ifndef _HIT_CAMERA_EFFECT_SEVERE_H_ //これが定義されてないとき
#define _HIT_CAMERA_EFFECT_SEVERE_H_
#include "main.h"
#include "hit_camera_effect.h"

//=============================================
//ヒット時のカメラエフェクトクラス
//=============================================
class CHitCameraEffectSevere :public CHitCameraEffect
{
public:
	/**
	 * @brief コンストラクタ
	 * @param [in]プライオリティ
	 */
	CHitCameraEffectSevere(int nPriority = PRIORITY);
	/**
	 * @brief デストラクタ
	 */
	~CHitCameraEffectSevere() override;
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

private:
	static const std::string TEXTURE_NAME;	//軽度テクスチャの名前
};

#endif // _HIT_CAMERA_EFFECT_SEVERE_H_