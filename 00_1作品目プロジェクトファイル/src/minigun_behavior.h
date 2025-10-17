//=============================================
//
//ミニガンのストラテジーパターン[minigun_behavior.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _MINIGUN_BEHAVIOR_
#define _MINIGUN_BEHAVIOR_
#include "gun_behavior.h"
#include "gun.h"

//=============================================
//ミニガンの弾発射ストラテジー
//=============================================
class CMiniGunShot : public CShot
{
public:
	/**
	 * @brief コンストラクタ
	 */
	CMiniGunShot();
	/**
	 * @brief デストラクタ
	 */
	~CMiniGunShot() override;
};

//=============================================
//リロードストラテジー
//=============================================
class CMiniGunReload : public CReload
{
public:
	/**
	 * @brief コンストラクタ
	 */
	CMiniGunReload();
	/**
	 * @brief デストラクタ
	 */
	~CMiniGunReload() override;
	/**
	 * @brief リロード
	 * @param [in]銃のポインタ
	 * @return リロードが終わったか
	 */
	bool Reload(CGun* gun) override;
private:
};
#endif