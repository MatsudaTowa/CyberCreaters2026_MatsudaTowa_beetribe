//=============================================
//
//ゲームプレイヤー[game_player.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _GAME_PLAYER_H_ //これが定義されてないとき

#define _GAME_PLAYER_H_
#include "main.h"
#include "active_player.h"

//=============================================
//チュートリアルプレイヤークラス
//=============================================
class CGamePlayer :public CActivePlayer
{
public:
	/**
	 * @brief コンストラクタ
	 * @param [in]プライオリティ
	 */
	CGamePlayer(int nPriority = PLAYER_PRIORITY);
	/**
	 * @brief デストラクタ
	 */
	~CGamePlayer()override;
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