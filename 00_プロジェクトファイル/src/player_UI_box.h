//=============================================
//
//プレイヤーのUIの枠[player_UI_box.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _PLAYER_UI_BOX_H_ //これが定義されてないとき

#define _PLAYER_UI_BOX_H_
#include "main.h"
#include "object2D.h"

//=============================================
//プレイヤーのUIの枠クラス
//=============================================
class CPlayerUIBox : public CObject2D
{
public:
	static const int UI_BOX_PRIORITY = 20;  //描画順

	enum BOX_TYPE
	{
		BOX_TYPE_LIFE,
		BOX_TYPE_AMMO,
		BOX_TYPE_SCORE,
		BOX_TYPE_MAX,
	};
	/**
	 * @brief コンストラクタ
	 * @param [in]プライオリティ
	 */
	CPlayerUIBox(int nPriority = UI_BOX_PRIORITY);
	/**
	 * @brief デストラクタ
	 */
	~CPlayerUIBox()override;
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
	 * @brief 生成
	 * @param [in]位置
	 * @param [in]サイズ
	 * @param [in]色
	 * @param [in]タイプ
	 * @return プレイヤーのUIの枠
	 */
	static CPlayerUIBox* Create(D3DXVECTOR3 pos, D3DXVECTOR2 size,D3DXCOLOR col, BOX_TYPE type);
private:
};

//=============================================
//プレイヤーのUIの体力の枠クラス
//=============================================
class CLifeUIBox : public CPlayerUIBox
{
public:
	/**
	 * @brief コンストラクタ
	 * @param [in]プライオリティ
	 */
	CLifeUIBox(int nPriority = UI_BOX_PRIORITY);
	/**
	 * @brief デストラクタ
	 */
	~CLifeUIBox()override;
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
private:
	static const std::string TEXTURE_NAME;	//テクスチャの名前

};

//=============================================
//プレイヤーのUIの残弾の枠クラス
//=============================================
class CAmmoUIBox : public CPlayerUIBox
{
public:
	/**
	 * @brief コンストラクタ
	 * @param [in]プライオリティ
	 */
	CAmmoUIBox(int nPriority = UI_BOX_PRIORITY);
	/**
	 * @brief デストラクタ
	 */
	~CAmmoUIBox()override;
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
private:
	static const std::string TEXTURE_NAME;	//テクスチャの名前
};

//=============================================
//プレイヤーのUIのスコアの枠クラス
//=============================================
class CScoreUIBox : public CPlayerUIBox
{
public:
	/**
	 * @brief コンストラクタ
	 * @param [in]プライオリティ
	 */
	CScoreUIBox(int nPriority = UI_BOX_PRIORITY);
	/**
	 * @brief デストラクタ
	 */
	~CScoreUIBox()override;
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
private:
	static const std::string TEXTURE_NAME;	//テクスチャの名前
};
#endif