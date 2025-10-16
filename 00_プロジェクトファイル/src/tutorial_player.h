//=============================================
//
//チュートリアルプレイヤー[tutorial_player.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _TUTORIAL_PLAYER_H_ //これが定義されてないとき

#define _TUTORIAL_PLAYER_H_
#include "main.h"
#include "active_player.h"

//=============================================
//チュートリアルプレイヤークラス
//=============================================
class CTutorialPlayer :public CActivePlayer
{
public:
	/**
	 * @brief コンストラクタ
	 * @param [in]プライオリティ
	 */
	CTutorialPlayer(int nPriority = PLAYER_PRIORITY);
	/**
	 * @brief デストラクタ
	 */
	~CTutorialPlayer()override;
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
};
#endif