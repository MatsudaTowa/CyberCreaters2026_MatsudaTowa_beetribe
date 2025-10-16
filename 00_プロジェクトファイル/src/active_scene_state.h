//=============================================
//
//アクティブシーンのステートパターン[active_scene_state.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _ACTIVE_SCENE_STATE_H_
#define _ACTIVE_SCENE_STATE_H_
#include "pause_mask.h"
#include "pause_select.h"
#include "pause_select_continue.h"
#include "pause_select_retry.h"
#include "pause_select_quit.h"
#include "setting_UI.h"
#include "close_pause_UI.h"
//=============================================
//前方宣言
//=============================================
class CActiveScene;

/** @brief アクティブシーンのステートクラス */
class CActiveSceneState
{
public:
	CActiveSceneState() {};
	virtual ~CActiveSceneState() {};
	/**
	* @brief 通常処理(親では何もしない)
	* @param [in]アクティブシーンポインタ
	*/
	virtual void Normal([[maybe_unused]] CActiveScene* active_scene) {};

	/**
	* @brief ポーズ状態処理(親では何もしない)
	* @param [in]アクティブシーンポインタ
	*/
	virtual void Pause([[maybe_unused]] CActiveScene* active_scene) {};

	/**
	* @brief 設定状態処理(親では何もしない)
	* @param [in]アクティブシーンポインタ
	*/
	virtual void Setting([[maybe_unused]] CActiveScene* active_scene) {};
};

/** @brief 通常クラス */
class CNormal :public CActiveSceneState
{
public:
	/**
	 * @brief コンストラクタ
	 */
	CNormal();
	/**
	* @brief ニュートラル処理
	* @param [in]アクティブシーンポインタ
	*/
	void Normal(CActiveScene* active_scene) override;
};

/** @brief 状態処理クラス */
class CPause :public CActiveSceneState
{
public:
	enum PAUSE_SELECT
	{
		CONTINUE = 0,
		SETTING,
		RETRY,
		QUIT,
		MAX
	};
	/**
	 * @brief コンストラクタ
	 */
	CPause();
	/**
	 * @brief デストラクタ
	 */
	~CPause()override;
	/**
	* @brief ポーズ状態処理
	* @param [in]アクティブシーンポインタ
	*/
	void Pause(CActiveScene* active_scene) override;
	/**
	 * @brief ポーズの選択されたUIの更新実行処理
	 * @param [in]アクティブシーンのポインタ
	 */
	virtual void HandlePoseSelection(CActiveScene* );

	/**
	 * @brief ポーズキャンセル
	 * @param [in]アクティブシーンのポインタ
	 */
	virtual void CancelPause(CActiveScene* ) {};

	/**
	 * @brief どれを選択してるか取得
	 * @return 選択されてるもの
	 */
	inline int GetSelect()
	{
		return m_nSelect;
	}

	/**
	 * @brief セレクトされてるUI
	 * @param [in]idx
	 * @return 選択UI
	 */
	inline CPauseSelect* GetSelectUI(int idx)
	{
		return m_pSelect[idx];
	}
private:
	static const D3DXVECTOR3 SELECT_POS[MAX];
	static const D3DXVECTOR3 CLOSE_POS;
	static const D3DXVECTOR2 CLOSE_SIZE;
	int m_nSelect;
	CMask* m_pMask;
	CClosePauseUI* m_pClosePause;
	CPauseSelect* m_pSelect[MAX];
};

/** @brief 設定クラス */
class CSetting :public CActiveSceneState
{
public:
	/**
	 * @brief コンストラクタ
	 */
	CSetting();
	/**
	 * @brief デストラクタ
	 */
	~CSetting() override;
	/**
	* @brief 設定処理
	* @param [in]アクティブシーンポインタ
	*/
	void Setting(CActiveScene* ) override;
private:
	/**
	 * @brief 感度変更
	 * @param [in][out]感度
	 */
	void ChangeSens(float& sens);

	static const int PRESS_FRAME = 5;	//このフレーム数キーが押されたら数値を進める
	static constexpr float MIN_SENS = 0.011f;	//最小感度
	static constexpr float MAX_SENS = 1.00f;	//最大感度
	static constexpr float CHANGE_SENS = 0.01f;	//感度の変動値

	static const D3DXVECTOR3 CLOSE_POS;
	static const D3DXVECTOR2 CLOSE_SIZE;
	CSetting_UI* m_pSettingUI;	//設定UI
	CClosePauseUI* m_pClosePause;
	int m_nPressCnt;	//キーのプレスカウント
};

#endif // !_GAME_STATE_H_
