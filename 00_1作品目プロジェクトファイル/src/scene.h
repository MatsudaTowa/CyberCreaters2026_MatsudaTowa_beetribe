//=============================================
//
//シーン[scene.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _SCENE_H_ //これが定義されてないとき

#define _SCENE_H_
#include "main.h"

//=============================================
// シーンクラス
//=============================================
class CScene
{
public:

	//画面の種類の列挙
	enum MODE
	{
		MODE_TITLE = 0,
		MODE_TEST,
		MODE_TUTORIAL,
		MODE_GAME,
		MODE_RESULT,
		MODE_MAX,
	};

	/**
	 * @brief コンストラクタ
	 */
	CScene();
	/**
	 * @brief デストラクタ
	 */
	virtual ~CScene();

	/**
	 * @brief 初期化
	 * @return 成功したか
	 */
	virtual HRESULT Init();
	/**
	 * @brief 終了
	 */
	virtual void Uninit();
	/**
	 * @brief 更新
	 */
	virtual void Update();
	/**
	 * @brief 描画
	 */
	virtual void Draw();
	/**
	 * @brief 生成
	 * @param [in]シーンモード
	 * @return シーンポインタ
	 */
	static CScene* Create(MODE mode);
	/**
	 * @brief シーンモード取得
	 * @return シーンモード
	 */
	static MODE GetSceneMode();
private:
	static MODE m_Mode; //現在のモード
};
#endif