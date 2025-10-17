//=============================================
//
//ウルトのマークの表記[ult_icon.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _ULT_ICON_H_ //これが定義されてないとき

#define _ULT_ICON_H_
#include "main.h"
#include "object2D.h"
#include "ult_icon_effect.h"

//=============================================
//ウルト表記クラス
//=============================================
class CUltIcon : public CObject2D
{
public:
	static const int ULT_ICON_PRIORITY = 21;  //描画順
	static const D3DXCOLOR START_COLOR;
	enum ULT_TYPE
	{
		ULT_TYPE_MEDIUM,
		ULT_TYPE_MAX,
	};
	/**
	 * @brief コンストラクタ
	 * @param [in]プライオリティ
	 */
	CUltIcon(int nPriority = ULT_ICON_PRIORITY);
	/**
	 * @brief デストラクタ
	 */
	~CUltIcon()override;
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
	 * @param [in]加算値
	 * @param [in]タイプ
	 * @return ウルトのUIポインタ
	 */
	static CUltIcon* Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, float add_col, ULT_TYPE type);

	/**
	 * @brief リセット
	 */
	void Reset();
private:
	static const D3DXVECTOR2 EFFECT_SIZE;
	static const D3DXCOLOR EFFECT_COLOR;
	bool m_isAddColor; //ウルトが溜まったらfalseに
	float m_AddColor; //色加算の値
	CUltIconEffect* m_pIconEffect;
};

//=============================================
//通常キャラのウルトのアイコンクラス
//=============================================
class CMediumIcon : public CUltIcon
{
public:
	/**
	 * @brief コンストラクタ
	 * @param [in]プライオリティ
	 */
	CMediumIcon(int nPriority = ULT_ICON_PRIORITY);
	/**
	 * @brief デストラクタ
	 */
	~CMediumIcon()override;
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