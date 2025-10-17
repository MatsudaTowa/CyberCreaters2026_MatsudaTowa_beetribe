//=============================================
//
//アサルト銃のストラテジーパターン[assault_behavior.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _ASSAULT_BEHAVIOR_
#define _ASSAULT_BEHAVIOR_
#include "gun_behavior.h"
#include "gun.h"

//=============================================
//アサルト弾発射ストラテジー
//=============================================
class CAssaultShot : public CShot
{
public:
	/**
	 * @brief コンストラクタ
	 */
	CAssaultShot();
	/**
	 * @brief デストラクタ
	 */
	~CAssaultShot() override;
};

//=============================================
//リロードストラテジー
//=============================================
class CAssaultReload : public CReload
{
public:
	/**
	 * @brief コンストラクタ
	 */
	CAssaultReload();
	/**
	 * @brief デストラクタ
	 */
	~CAssaultReload() override;
	/**
	 * @brief リロード処理
	 * @param [in]銃のポインタ
	 * @return 撃てるかどうか
	 */
	bool Reload(CGun* gun) override;
private:
};
#endif