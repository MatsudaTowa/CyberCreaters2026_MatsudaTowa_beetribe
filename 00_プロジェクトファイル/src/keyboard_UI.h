//=============================================
//
//キーボードUIの表記[keyboard_UI.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _KEYBOARD_UI_H_ //これが定義されてないとき

#define _KEYBOARD_UI_H_
#include "main.h"
#include "object2D.h"

//スモークの表記クラス
class CKeyboard_UI : public CObject2D
{
public:
	static const int PRIORITY = 26;  //描画順

	enum KEY_TYPE
	{
		KEY_W = 0,
		KEY_A,
		KEY_S,
		KEY_D,
		KEY_Q,
		KEY_X,
		KEY_R,
		KEY_LSHIFT,
		KEY_MAX
	};

	/**
	 * @brief コンストラクタ
	 * @param [in]プライオリティ
	 */
	CKeyboard_UI(int nPriority = PRIORITY);
	/**
	 * @brief デストラクタ
	 */
	~CKeyboard_UI()override;
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
	 * @param [in]キー
	 * @return キーボードUIのポインタ
	 */
	static CKeyboard_UI* Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXCOLOR col, KEY_TYPE key);
private:
	static const std::string TEXTURE_NAME[KEY_MAX];	//テクスチャの名前
	KEY_TYPE m_type;
};
#endif