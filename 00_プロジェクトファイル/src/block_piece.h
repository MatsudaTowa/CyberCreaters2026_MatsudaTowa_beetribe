//=============================================
//
//ブロックの破片[block_piece.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _BLOCK_PIECE_H_ //これが定義されてないとき

#define _BLOCK_PIECE_H_
#include "main.h"
#include "objectX.h"
#include "manager.h"

//=============================================
//ブロックの破片クラス
//=============================================
class CBlock_Piece : public CObjectX
{
public:
	static const int BLOCK_PRIORITY = 10; //描画順

	enum PIECE_SHAPE
	{
		PIECE_SHAPE_0 = 0,
		PIECE_SHAPE_1,
		PIECE_SHAPE_2,
		PIECE_SHAPE_MAX,
	};

	static const char* MODEL_NAME[PIECE_SHAPE_MAX];	//モデルの名前

	/**
	 * @brief コンストラクタ
	 * @param プライオリティ
	 */
	CBlock_Piece(int nPriority = BLOCK_PRIORITY);
	/**
	 * @brief デストラクタ
	 */
	~CBlock_Piece()override;
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

	/**
	 * @brief ブロックの破片生成
	 * @param 位置
	 * @param 方向
	 * @param サイズ
	 * @param 動かすかどうか
	 * @return 
	 */
	static CBlock_Piece* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,D3DXVECTOR3 scale,bool isMove);
private:
	static constexpr float SHIFT_X_MAX = 50.0f;		//Xの最大ムーブ量
	static constexpr float SHIFT_X_MIN = -50.0f;	//Xの最小ムーブ量

	static constexpr float SHIFT_Z_MAX = 50.0f;		//Zの最大ムーブ量
	static constexpr float SHIFT_Z_MIN = -50.0f;	//Zの最小ムーブ量
	PIECE_SHAPE m_shape;	//破片の形列挙
};

//=============================================
//ブロックの動かす破片クラス
//=============================================
class CMove_Piece :public CBlock_Piece
{
public:
	/**
	 * @brief コンストラクタ
	 * @param [in]プライオリティ
	 */
	CMove_Piece(int nPriority = BLOCK_PRIORITY);
	/**
	 * @brief デストラクタ
	 */
	~CMove_Piece()override;
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
	static const int LIFE = 120;				//寿命
	static const int RAND_RANGE = 101;			//ランダムの算出範囲
	static constexpr float MIN_MOVE = 5.0f;		//移動量の最低値
	static constexpr float MOVE_RANGE = 10.0f;	//移動量の算出範囲
	D3DXVECTOR3 m_move;							//移動量
	int m_nLife;								//体力
};

//=============================================
//ブロックの動かさない破片クラス
//=============================================
class CStack_Piece :public CBlock_Piece
{
public:
	/**
	 * @brief コンストラクタ
	 * @param [in]プライオリティ
	 */
	CStack_Piece(int nPriority = BLOCK_PRIORITY);
	/**
	 * @brief デストラクタ
	 */
	~CStack_Piece()override;
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