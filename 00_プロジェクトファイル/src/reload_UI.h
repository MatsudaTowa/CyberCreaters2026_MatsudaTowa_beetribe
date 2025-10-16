//=============================================
//
//リロード状況表示「reload_UI.h」
// Author松田永久
//
//=============================================
#ifndef _RELOAD_UI_H_ //これが定義されてないとき
#define _RELOAD_UI_H_
#include "main.h"
#include "active_player.h"
#include "reload_Txt.h"

//=============================================
//リロードUIクラス
//=============================================
class CReload_UI
{
public:
	/**
	 * @brief コンストラクタ
	 */
	CReload_UI();
	/**
	 * @brief デストラクタ
	 */
	~CReload_UI();
	/**
	 * @brief 初期化
	 * @return 成功したか
	 */
	HRESULT Init();
	/**
	 * @brief 終了
	 */
	void Uninit();
	/**
	 * @brief 更新
	 */
	void Update();
private:
	static const D3DXVECTOR3 TXT_POS; //リロードテキストの位置
	static const D3DXVECTOR2 TXT_SIZE; //リロードテキストのサイズ

	CReloatTxt* m_pTxt;
};

#endif