//=============================================
//
//チュートリアル[tutorial.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _TUTORIAL_H_ //これが定義されてないとき

#define _TUTORIAL_H_
#include "main.h"
#include "active_scene.h"
#include "player.h"
#include"block.h"
#include "wave.h"
#include "score.h"
#include"wave_result.h"
#include "tutorial_UI.h"

//=============================================
// チュートリアルクラス
//=============================================
class CTutorial:public CActiveScene
{
public:
	//読み込むときに必要なエネミーの構造体
	struct LOAD_ENEMY
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
		CEnemy::ENEMY_TYPE type;
	};

	//読み込むときに必要な壁の構造体
	struct LOAD_WALL
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 size;
		D3DXVECTOR3 rot;
	};

	static const std::string ENEMY_FILE;	//エネミーのファイル
	static const std::string BLOCK_FILE;	//ブロックのファイル
	static const std::string WALL_FILE;		//壁のファイル
	static const int TXT_MAX = 2048; //敵を読み込む際の読み込める最大文字数
	/**
	 * @brief コンストラクタ
	 */
	CTutorial();
	/**
	 * @brief デストラクタ
	 */
	~CTutorial() override;
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
	 * @brief 実行
	 */
	void Active();
	/**
	 * @brief 描画
	 */
	void Draw() override;
private:
	static const D3DXVECTOR3 FIELD_SIZE; //床のサイズ
	static const D3DXVECTOR3 UI_POS; //UIの位置
	static const D3DXVECTOR2 UI_SIZE; //UIのサイズ

	LOAD_ENEMY m_LoadEnemy; //読み込むときに必要なエネミーの情報
	LOAD_WALL m_LoadWall; //読み込むときに必要な壁の情報

	CTutorial_UI* m_pTutorial_UI;
	/**
	 * @brief 壁読み込み
	 * @param [in]ファイルネーム
	 */
	void LoadWall(const std::string* pFileName);
	/**
	 * @brief 敵読み込み
	 * @param [in]ファイルネーム
	 */
	void LoadEnemy(const std::string* pFileName);
};
#endif