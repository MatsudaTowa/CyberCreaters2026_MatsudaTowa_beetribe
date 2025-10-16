//=============================================
//
//タイトルプレイヤー[title_player.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _TITLE_PLAYER_H_ //これが定義されてないとき

#define _TITLE_PLAYER_H_
#include "main.h"
#include "player.h"

//=============================================
//タイトルプレイヤークラス
//=============================================
class CTitlePlayer :public CPlayer
{
public:
	/**
	 * @brief コンストラクタ
	 * @param [in]プライオリティ
	 */
	CTitlePlayer(int nPriority = PLAYER_PRIORITY);
	/**
	 * @brief デストラクタ
	 */
	~CTitlePlayer()override;
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