//=============================================
//
//敵のリアクションのUI[enemy_reaction_UI.h]
//Author Matsuda Towa
//
//=============================================
#include "main.h"
#include "billboard.h"

#ifndef _ENEMY_REACTION_UI_H_ //これが定義されてないとき

#define _ENEMY_REACTION_UI_H_

//=============================================
// エネミーのリアクションUIクラス
//=============================================
class CEnemy_Reaction_UI : public CBillboard
{
public:
	static const int PRIORITY = 17; //描画順

	enum REACTION
	{
		REACTION_RELOAD = 0,
		REACTION_CONFUSION,
		REACTION_STAN,
	};

	/**
	 * @brief コンストラクタ
	 * @param [in]プライオリティ
	 */
	CEnemy_Reaction_UI(int nPriority = PRIORITY);
	/**
	 * @brief デストラクタ
	 */
	~CEnemy_Reaction_UI()override;
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
	 * @param [in]タイプ
	 * @return リアクションUIポインタ
	 */
	static CEnemy_Reaction_UI* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, REACTION type);

private:
};

#endif