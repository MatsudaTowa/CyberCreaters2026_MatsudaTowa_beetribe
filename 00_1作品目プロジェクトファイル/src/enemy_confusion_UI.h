//=============================================
//
//敵の混乱のUI[enemy_confusion_UI.h]
//Author Matsuda Towa
//
//=============================================
#include "main.h"
#include "billboard.h"
#include "enemy_reaction_UI.h"

#ifndef _ENEMY_WANDERING_UI_H_ //これが定義されてないとき

#define _ENEMY_WANDERING_UI_H_

//=============================================
//混乱状態のUIクラス
//=============================================
class CEnemy_Confusion_UI : public CEnemy_Reaction_UI
{
public:
	/**
	 * @brief コンストラクタ
	 * @param [in]プライオリティ
	 */
	CEnemy_Confusion_UI(int nPriority = PRIORITY);
	/**
	 * @brief デストラクタ
	 */
	~CEnemy_Confusion_UI()override;
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