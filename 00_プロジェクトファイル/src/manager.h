//=============================================
//
//マネージャー[maneger.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _MANAGER_H_ //これが定義されてないとき

#define _MANAGER_H_
#include "main.h"
#include "input.h"
#include "camera.h"
#include "light.h"
#include "texture.h"
#include "model.h"
#include "scene.h"
#include "fade.h"
#include "sound.h"
#include "colision.h"
#include "useful.h"

//=============================================
//マネージャークラス
//=============================================
class CManager
{
public:
	static const int NUM_RESULT_FILE = 4;
	static const std::string RESULT_SCORE_FILE[NUM_RESULT_FILE]; //リザルトのファイルネーム

	/**
	 * @brief コンストラクタ
	 */
	CManager();
	/**
	 * @brief デストラクタ
	 */
	~CManager();
	/**
	 * @brief 初期化
	 * @param [in]インスタンス
	 * @param [in]ハンドルワンド
	 * @param [in]ウィンドウ生成できたか
	 * @return 成功したか
	 */
	HRESULT Init(HINSTANCE hInstance,HWND hWnd,BOOL bWindow);
	/**
	 * @brief 終了
	 */
	void Uninit();
	/**
	 * @brief 更新
	 */
	void Update();
	/**
	 * @brief 描画
	 */
	void Draw();

	/**
	 * @brief シーン設定
	 * @param [in]シーン
	 */
	void SetMode(CScene::MODE mode);

	/**
	 * @brief インスタンス生成
	 * @return インスタンス
	 */
	static CManager* GetInstance()
	{
		static CManager instance; //静的インスタンス
		return &instance;
	}

	/**
	 * @brief シーン取得
	 * @return シーンポインタ
	 */
	CScene* GetScene();

	/**
	 * @brief レンダラー取得
	 * @return レンダラーポインタ
	 */	
	CRenderer*GetRenderer();

	/**
	* @brief キーボード取得
	* @return キーボードポインタ
	*/
	CInputKeyboard* GetKeyboard();

	/**
	* @brief マウス取得
	* @return マウスポインタ
	*/	
	CInputMouse* GetMouse();

	/**
	* @brief カメラ取得
	* @return カメラポインタ
	*/
	CCamera* GetCamera();

	/**
	* @brief ライト取得
	* @return ライトポインタ
	*/
	CLight* GetLight();

	/**
	* @brief テクスチャ取得
	* @return テクスチャポインタ
	*/
	CTexture* GetTexture();

	/**
	* @brief モデル取得
	* @return モデルポインタ
	*/
	CModel* GetModel();

	/**
	* @brief サウンド取得
	* @return サウンドポインタ
	*/
	CSound* GetSound();

	/**
	* @brief フェード取得
	* @return フェードポインタ
	*/
	CFade* GetFade();

	/**
	* @brief 当たり判定取得
	* @return 当たり判定ポインタ
	*/
	CColision* GetColision();

	/**
	* @brief ハンドルワンド取得
	* @return ハンドルワンド
	*/
	HWND GetHWnd();
	/**
	* @brief スコアに0書き出し
	* @return ファイルネーム
	*/
	static void ExportScoreReset(const std::string* pFileName);

private:

	HWND m_hWnd;
	CScene* m_pScene;
	CRenderer* m_pRenderer;
	CInputKeyboard* m_pKeyboard;
	CInputMouse* m_pMouse;
	CCamera* m_pCamera;
	CLight* m_pLight;
	CTexture* m_pTexture;
	CModel* m_pModel;
	CSound* m_pSound;
	CColision* m_pColision;
	CFade* m_pFade;
};

#endif