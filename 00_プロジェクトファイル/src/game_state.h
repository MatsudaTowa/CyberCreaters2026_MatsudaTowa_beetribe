//=============================================
//
//ゲームのステートパターン[game_state.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _GAME_STATE_H_
#define _GAME_STATE_H_
#include "pause_mask.h"
#include "pause_select.h"
#include "active_scene_state.h"

//=============================================
//前方宣言
//=============================================
class CActiveScene;

/** @brief 通常クラス */
class CGameNormal :public CNormal
{
public:
	/**
	 * @brief コンストラクタ
	 */
	CGameNormal();
	/**
	* @brief ニュートラル処理
	* @param [in]アクティブシーンのポインタ
	*/
	void Normal(CActiveScene* active_scene) override;
};

/** @brief 状態処理クラス */
class CGamePause :public CPause
{
public:
	/**
	* @brief ポーズ状態処理
	* @param [in]アクティブシーンポインタ
	*/
	void Pause(CActiveScene* active_scene) override;
	/**
	 * @brief ポーズの選択されたUIの更新実行処理
	 * @param [in]アクティブシーンのポインタ
	 */
	void HandlePoseSelection(CActiveScene* active_scene) override;
	/**
	 * @brief ポーズキャンセル
	 * @param [in]アクティブシーンのポインタ
	 */
	void CancelPause(CActiveScene* active_scene) override;
private:
};

/** @brief 設定クラス */
class CGameSetting :public CSetting
{
public:
	/**
	* @brief 設定処理
	* @param [in]アクティブシーンポインタ
	*/
	void Setting(CActiveScene* active_scene) override;
private:
};

#endif // !_GAME_STATE_H_
