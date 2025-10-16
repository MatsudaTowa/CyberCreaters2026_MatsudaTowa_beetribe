//=============================================
//
//銃のストラテジーパターン[gun_behavior.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _GUN_BEHAVIOR_
#define _GUN_BEHAVIOR_
#include "gun.h"
#include "muzzle_flash.h"

//=============================================
//前方宣言
//=============================================
class CGun;

//=============================================
//弾発射ストラテジー
//=============================================
class CShot
{
public:
	/**
	 * @brief コンストラクタ
	 */
	CShot();
	/**
	 * @brief デストラクタ
	 */
	virtual ~CShot();
	/**
	 * @brief 発射
	 * @param [in]位置
	 * @param [in]移動量
	 * @param [in]サイズ
	 * @param [in]ダメージ
	 * @param [in]どっちの弾か
	 * @param [in]銃のポインタ
	 */
	virtual void Shot(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, int nDamage, CBullet::BULLET_ALLEGIANCE Allegiance,CGun*gun);
private:
	static const int LIFE = 900;	//寿命 
};

//=============================================
//リロードストラテジー
//=============================================
class CReload
{
public:
	/**
	 * @brief コンストラクタ
	 */
	CReload();
	/**
	 * @brief デストラクタ
	 */
	virtual ~CReload();
	/**
	 * @brief リロード
	 * @param [in]銃のポインタ
	 * @return リロードが終わったか
	 */
	virtual bool Reload(CGun* gun) = 0;

	/**
	 * @brief リロードカウント取得
	 * @return リロードカウント
	 */
	inline int& GetReloadCnt() 
	{
		return m_nReloadCnt;
	}

	/**
	 * @brief リロードカウント設定
	 * @param [in]リロードカウント
	 */
	inline void SetReloadCnt(int nCnt)
	{
		m_nReloadCnt = nCnt;
	}
private:
	int m_nReloadCnt;
};

#endif
