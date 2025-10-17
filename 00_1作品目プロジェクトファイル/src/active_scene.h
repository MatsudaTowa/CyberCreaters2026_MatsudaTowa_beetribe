//=============================================
//
//遊べるシーン[active_scene.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _ACTIVE_SCENE_H_ //これが定義されてないとき

#define _ACTIVE_SCENE_H_
#include "scene.h"
#include "block.h"
#include "active_scene_state.h"

//=============================================
// シーンクラス
//=============================================
class CActiveScene : public CScene
{
public:
	//読み込むときに必要なブロックの構造体
	struct LOAD_BLOCK
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
		CBlock::BLOCKTYPE type;
	};

	/**
	 * @brief コンストラクタ
	 */
	CActiveScene();
	/**
	 * @brief デストラクタ
	 */
	~CActiveScene() override;

	/**
	 * @brief 初期化
	 * @return 成功したか
	 */
	HRESULT Init() override;
	/**
	 * @brief 終了
	 */
	void Uninit() override;
	/**
	 * @brief 更新
	 */
	void Update() override;
	/**
	 * @brief 描画
	 */
	void Draw() override;

	/**
	 * @brief オブジェクトの更新を行うか決定
	 * @param [in]動かすかどうか
	 */
	void UpdateObjectDecision(bool isActive); 

	/**
	 * @brief 入力可能か取得
	 * @param 入力可能か
	 */
	inline bool GetPauseKey()
	{
		return m_nPauseCnt >= PAUSE_POSSIBLE_FLAME;
	}

	/**
	 * @brief カウントリセット
	 */
	inline void ResetPauseCnt()
	{
		m_nPauseCnt = 0;
	}

	/**
	 * @brief ブロック読み込み
	 * @param [in]ファイルネーム
	 */
	void LoadBlock(const std::string& pFileName);

	/**
	 * @brief ステート変更
	 * @param [in]次のステート
	 */
	void ChangeState(CActiveSceneState* state);

private:
	static const int PAUSE_POSSIBLE_FLAME = 1;	//ポーズを有効化させるフレーム

	LOAD_BLOCK m_LoadBlock; //読み込むときに必要なブロックの情報

	int m_nPauseCnt;	//ポーズを有効化する時に用いるカウント

	CActiveSceneState* m_pState;
};
#endif