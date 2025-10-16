//=============================================
//
//攻撃管理クラス[attack_manager.h]
//Author Matsuda Towa
//
//=============================================
#include"main.h"
#include "Billboard.h"

#ifndef _ATTACK_MANAGER_H_ //これが定義されてないとき

#define _ATTACK_MANAGER_H_

//=============================================
//攻撃管理クラス
//=============================================
class CAttack_Manager : public CBillboard
{
public:
	/**
	 * @brief コンストラクタ
	 * @param [in]プライオリティ
	 */
	CAttack_Manager(int nPriority);
	/**
	 * @brief デストラクタ
	 */
	~CAttack_Manager()override;
	/**
	 * @brief 初期化
	 * @return 成功してるか
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
	 * @brief 敵とのヒット処理
	 * @return ヒットしてるか
	 */
	bool HitEnemy();
	/**
	 * @brief プレイヤーとのヒット処理
	 * @return ヒットしてるか
	 */
	bool HitPlayer();
	/**
	 * @brief ブロックとのヒット処理
	 * @return ヒットしてるか
	 */
	bool HitBlock();
	/**
	 * @brief 床とのヒット処理
	 * @return ヒットしてるか
	 */
	bool HitGround();

	/**
	 * @brief 体力の設定
	 * @param [in]体力
	 */
	inline void SetLife(int nLife)
	{
		m_nLife = nLife;
	}

	/**
	 * @brief ダメージの設定
	 * @param [in]ダメージの値
	 */
	inline void SetDamage(int nDamage)
	{
		m_nDamage = nDamage;
	}

	/**
	 * @brief 体力の取得
	 * @return 体力の値
	 */
	inline int GetLife()
	{
		return m_nLife;
	}

	/**
	 * @brief ダメージの取得
	 * @return ダメージの値
	 */
	inline int GetDamage()
	{
		return m_nDamage;
	}
private:
	int m_nLife; //寿命
	int m_nDamage; //ダメージ
	int m_nNumkill; //何体倒したか
};
#endif