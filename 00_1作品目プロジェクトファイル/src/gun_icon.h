//=============================================
//
//銃の表記[gun_icon.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _GUN_ICON_H_ //これが定義されてないとき

#define _GUN_ICON_H_
#include "main.h"
#include "object2D.h"

//=============================================
//銃の表記クラス
//=============================================
class CGunIcon : public CObject2D
{
public:
	static const int GUN_ICON_PRIORITY = 25;  //描画順

	enum ICON_TYPE
	{
		ICON_TYPE_AR,
		ICON_TYPE_MAX,
	};
	/**
	 * @brief コンストラクタ
	 * @param [in]プライオリティ
	 */
	CGunIcon(int nPriority = GUN_ICON_PRIORITY);
	/**
	 * @brief デストラクタ
	 */
	~CGunIcon()override;
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
	 * @return 銃のアイコン
	 */
	static CGunIcon* Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXCOLOR col, ICON_TYPE type);
private:
};

//=============================================
//アサルトのアイコン
//=============================================
class CARIcon : public CGunIcon
{
public:
	/**
	 * @brief コンストラクタ
	 * @param [in]プライオリティ
	 */
	CARIcon(int nPriority = GUN_ICON_PRIORITY);
	/**
	 * @brief デストラクタ
	 */
	~CARIcon()override;
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