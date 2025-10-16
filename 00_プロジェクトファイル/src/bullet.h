//=============================================
//
//弾[bullet.h]
//Author Matsuda Towa
//
//=============================================
#include "main.h"
#include "attack_manager.h"

#ifndef _BULLET_H_ //これが定義されてないとき

#define _BULLET_H_

//=============================================
//弾クラス
//=============================================
class CBullet : public CAttack_Manager
{
public:
	static const int BULLET_PRIORITY = 10; //描画順

	//敵か自分かの判断する列挙
	enum BULLET_ALLEGIANCE
	{
		BULLET_ALLEGIANCE_PLAYER = 0,
		BULLET_ALLEGIANCE_ENEMY,
		BULLET_ALLEGIANCE_MAX,
	};

	/**
	 * @brief コンストラクタ
	 * @param [in]プライオリティ
	 */
	CBullet(int nPriority = BULLET_PRIORITY);
	/**
	 * @brief デストラクタ
	 */
	~CBullet()override;
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
	 * @brief 弾の生成
	 * @param [in]位置
	 * @param [in]移動量
	 * @param [in]方向
	 * @param [in]サイズ
	 * @param [in]寿命
	 * @param [in]ダメージ数
	 * @param [in]敵のか味方のか
	 * @return 弾のポインタ
	 */
	static CBullet* Create(D3DXVECTOR3 pos,D3DXVECTOR3 move,D3DXVECTOR3 rot,
	D3DXVECTOR3 size,int nLife,int nDamage, BULLET_ALLEGIANCE Allegiance);

	/**
	 * @brief 移動量設定
	 * @param [in]移動量
	 */
	inline void SetMove(D3DXVECTOR3 move)
	{
		m_move = move;
	}
	/**
	 * @brief どっちの弾か設定
	 * @param [in]どっちの弾か
	 */
	inline void SetBulletAllegiance(BULLET_ALLEGIANCE Allegiance)
	{
		m_Allegiance = Allegiance;
	}
	/**
	 * @brief 移動量取得
	 * @return 移動量
	 */
	inline D3DXVECTOR3 GetMove()
	{
		return m_move;
	}
	/**
	 * @brief どっちの弾か取得
	 * @return どっちの弾か
	 */
	inline BULLET_ALLEGIANCE GetBulletAllegiance()
	{
		return m_Allegiance;
	}
private:
	static const std::string BULLET_TEXTURE_NAME;	//テクスチャの名前
	/**
	 * @brief 使用されてる時の処理
	 */
	void OnActive();
	/**
	 * @brief ヒットマーカー設定
	 */
	void SetHitMaker();
	/**
	 * @brief ブロックに当たったか
	 * @return 当たったか
	 */
	bool PenetrationBlock();
	BULLET_ALLEGIANCE m_Allegiance; //敵か自分かを判断する列挙型変数
	D3DXVECTOR3 m_move; //移動量
};

#endif