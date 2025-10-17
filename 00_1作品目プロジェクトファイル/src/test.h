//=============================================
//
//テストシーン[test.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _TEST_H_ //これが定義されてないとき

#define _TEST_H_
#include "main.h"
#include "scene.h"
#include "player.h"
#include "block.h"

//=============================================
// テストクラス
//=============================================
class CTest :public CScene
{
public:
	static const int BLOCK_TXT_MAX = 2048; //敵を読み込む際の読み込める最大文字数
	static const std::string BLOCK_FILE;	//エネミーのファイル

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
	CTest();
	/**
	 * @brief デストラクタ
	 */
	~CTest() override;
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
private:
	/**
	 * @brief ブロック読み込み
	 * @param [in]ファイルパス
	 */
	void LoadBlock(const std::string& pFileName);

	LOAD_BLOCK m_LoadBlock; //読み込むときに必要なブロックの情報

	//プレイヤー
	CPlayer* m_pPlayer;
};
#endif