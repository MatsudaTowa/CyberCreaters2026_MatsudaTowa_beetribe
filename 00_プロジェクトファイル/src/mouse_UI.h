//=============================================
//
//マウスUIの表記[mouse_UI.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _MOUSE_UI_H_ //これが定義されてないとき

#define _MOUSE_UI_H_
#include "main.h"
#include "object2D.h"

//=============================================
//マウスの表記クラス
//=============================================
class CMouse_UI : public CObject2D
{
public:
	static const int PRIORITY = 27;  //描画順

	enum MOUSE_TYPE
	{
		MOUSE_R = 0,
		MOUSE_L,
		MOUSE_MAX
	};

	/**
	 * @brief コンストラクタ
	 * @param [in]プライオリティ
	 */
	CMouse_UI(int nPriority = PRIORITY);
	/**
	 * @brief デストラクタ
	 */
	~CMouse_UI()override;
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
	 * @return マウスのUIポインタ
	 */
	static CMouse_UI* Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXCOLOR col, MOUSE_TYPE type);
private:
	static const std::string TEXTURE_NAME[MOUSE_MAX];	//テクスチャの名前
	MOUSE_TYPE m_type;
};
#endif