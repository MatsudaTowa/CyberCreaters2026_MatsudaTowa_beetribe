//=============================================
//
//銃[gun.h]
//Author Matsuda Towa
//
//=============================================
#include "main.h"
#include "bullet.h"
#include "gun_behavior.h"

#ifndef _GUN_H_ //これが定義されてないとき

#define _GUN_H_

//=============================================
//前方宣言
//=============================================
class CShot;
class CReload;

//=============================================
//銃の基底クラス
//=============================================
class CGun
{
public:
	static const int DEFAULT_HG_MAG_SIZE = 20; //デフォルトのハンドガンのマガジンサイズ
	static const int DEFAULT_SG_MAG_SIZE = 6; //デフォルトのショットガンのマガジンサイズ

	static const int DEFAULT_HG_RELOAD_FRAME = 20; //デフォルトのハンドガンのリロードフレーム数
	static const int DEFAULT_SG_RELOAD_FRAME = 30; //デフォルトのハンドガンのリロードフレーム数

	/**
	 * @brief コンストラクタ
	 */
	CGun();
	/**
	 * @brief デストラクタ
	 */
	virtual ~CGun();
	/**
	 * @brief 初期化
	 * @return 成功したか
	 */
	virtual HRESULT Init() = 0;
	/**
	 * @brief 終了
	 */
	virtual void Uninit() = 0;
	/**
	 * @brief リロード
	 * @return リロードし終わったか
	 */
	virtual bool Reload();
	/**
	 * @brief サイズ設定
	 * @param [in]サイズ
	 */
	inline void SetSize(D3DXVECTOR3 size)
	{
		m_Size = size;
	}

	/**
	 * @brief レート計測カウント設定
	 * @param [in]レートカウント
	 */
	inline void SetRateCnt(int nRateCnt)
	{
		m_nRateCnt = nRateCnt;
	}

	/**
	 * @brief 弾数設定
	 * @param [in]弾数
	 */	inline void SetAmmo(int Ammo)
	{
		m_Ammo = Ammo;
	}

	/**
	 * @brief ダメージ設定
	 * @param [in]ダメージ
	 */
	inline void SetDamage(int Damage)
	{
		m_nDamage = Damage;
	}

	/**
	 * @brief リロードフレーム設定
	 * @param [in]リロードフレーム
	 */
	inline void SetReloadFrame(int ReloadFrame)
	{
		m_ReloadFrame = ReloadFrame;
	}
	/**
	 * @brief 発射レート設定
	 * @param [in]発射レート
	 */
	inline void SetFireRate(int FireRate)
	{
		m_FireRate = FireRate;
	}

	/**
	 * @brief 弾速設定
	 * @param [in]弾速
	 */
	inline void SetBulletSpeed(float BulletSpeed)
	{
		m_BulletSpeed = BulletSpeed;
	}
	
	/**
	 * @brief サイズ取得
	 * @return サイズ
	 */
	inline D3DXVECTOR3& GetSize()
	{
		return m_Size;
	}

	/**
	 * @brief レートカウント取得
	 * @return レートカウント
	 */
	inline int& GetRateCnt()
	{
		return m_nRateCnt;
	}

	/**
	 * @brief 弾数取得
	 * @return 弾数
	 */
	inline int& GetAmmo()
	{
		return m_Ammo;
	}

	/**
	 * @brief ダメージ取得
	 * @return ダメージ
	 */
	inline int& GetDamage()
	{
		return m_nDamage;
	}

	/**
	 * @brief リロードフレーム取得
	 * @return リロードフレーム
	 */
	inline int& GetReloadFrame()
	{
		return m_ReloadFrame;
	}

	/**
	 * @brief 発射レート取得
	 * @return 発射レート
	 */
	inline int& GetFireRate()
	{
		return m_FireRate;
	}

	/**
	 * @brief 弾速取得
	 * @return 弾速
	 */
	inline float& GetBulletSpeed()
	{
		return m_BulletSpeed;
	}

	CShot* m_pShot; //弾発射処理
	CReload* m_pReload; //リロード処理

private:
	D3DXVECTOR3 m_Size; //サイズ

	int m_nRateCnt;//レートカウント
	int m_Ammo; //マガジン内の弾数
	int m_nDamage; //ダメージ
	int m_ReloadFrame; //リロードフレーム
	int m_FireRate; //発射レート
	float m_BulletSpeed; //弾速

};

//=============================================
//アサルトライフクラス
//=============================================
class CAssultRifle :public CGun
{
public:
	static const int DEFAULT_AR_MAG_SIZE = 28; //デフォルトのアサルトのマガジンサイズ
	static const int DEFAULT_AR_FIRE_RATE = 13; //デフォルトのアサルトの発射レート
	static constexpr float DEFAULT_AR_BULLET_SPEED = 100.0f; //デフォルトのアサルトの弾のスピード
	static const D3DXVECTOR3 DEFAULT_AR_SIZE; //デフォルトのアサルトサイズ
	static const int DEFAULT_AR_RELOAD_FRAME = 120; //デフォルトのアサルトのリロードフレーム数
	static const int DEFAULT_AR_DAMAGE = 10; //デフォルトのアサルトのダメージ

	/**
	 * @brief コンストラクタ
	 */
	CAssultRifle();
	/**
	 * @brief デストラクタ
	 */
	~CAssultRifle() override;
	/**
	 * @brief 初期化
	 * @return 成功したか
	 */
	HRESULT Init() override;
	/**
	 * @brief 終了
	 */
	void Uninit() override;
private:
};

//=============================================
//ミニガンクラス
//=============================================
class CMiniGun :public CGun
{
public:
	static const int DEFAULT_MINIGUN_MAG_SIZE = 120; //デフォルトのミニガンのマガジンサイズ
	static const int DEFAULT_MINIGUN_RELOAD_FRAME = 120; //デフォルトのミニガンのリロードフレーム数
	static const int DEFAULT_MINIGUN_FIRE_RATE = 2; //デフォルトのミニガンの発射レート
	static const int DEFAULT_MINIGUN_DAMAGE = 3; //デフォルトのミニガンのダメージ
	static constexpr float DEFAULT_MINIGUN_BULLET_SPEED = 100.0f; //デフォルトのミニガンの弾のスピード
	static const D3DXVECTOR3 DEFAULT_MINIGUN_SIZE; //デフォルトのミニガンのサイズ

	/**
	 * @brief コンストラクタ
	 */
	CMiniGun();
	/**
	 * @brief デストラクタ
	 */
	~CMiniGun() override;
	/**
	 * @brief 初期化
	 * @return 成功したか
	 */
	HRESULT Init() override;
	/**
	 * @brief 終了
	 */
	void Uninit() override;
private:
};
#endif