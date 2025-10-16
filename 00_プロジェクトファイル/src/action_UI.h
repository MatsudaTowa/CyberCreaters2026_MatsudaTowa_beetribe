//=============================================
//
//アクションUIの表記[action_UI.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _ACTION_UI_H_ //これが定義されてないとき

#define _ACTION_UI_H_
#include "main.h"
#include "object2D.h"

/**
* @brief アクションUIクラス
* @copydoc CObject2D
*/
class CAction_UI : public CObject2D
{
public:
	static const int PRIORITY = 20;  //描画順

	enum ACTION_TYPE
	{
		ACTION_MOVE = 0,
		ACTION_SHOTMODE,
		ACTION_SHOT,
		ACTION_RELOAD,
		ACTION_ULT,
		ACTION_SMOKE,
		ACTION_MAX
	};

	/**
	 * @brief コンストラクタ
	 * @param [in]プライオリティ
	 */
	CAction_UI(int nPriority = PRIORITY);
	/**
	 * @brief デストラクタ
	 */
	~CAction_UI()override;
	/**
	 * @brief コンストラクタ
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
	 * @brief コンストラクタ
	 * @param[in]位置
	 * @param[in]サイズ
	 * @param[in]色
	 * @param[in]どのタイプか
	 * @return アクションのUIポインタ
	 */
	static CAction_UI* Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXCOLOR col, ACTION_TYPE type);
private:
	static const std::string TEXTURE_NAME[ACTION_MAX];	//テクスチャの名前
	ACTION_TYPE m_type;		//アクションのタイプ
};
#endif