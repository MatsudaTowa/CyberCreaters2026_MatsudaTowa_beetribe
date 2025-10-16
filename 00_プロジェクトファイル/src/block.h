//=============================================
//
//ブロック[block.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _BLOCK_H_ //これが定義されてないとき

#define _BLOCK_H_
#include "main.h"
#include "objectX.h"

//=============================================
//ブロッククラス
//=============================================
class CBlock : public CObjectX
{
public:
	static const int BLOCK_PRIORITY = 10; //描画順
	enum BLOCKTYPE
	{
		BLOCKTYPE_NONE = 0,
		BLOCKTYPE_DEFAULT,
		BLOCKTYPE_MAX,
	};
	/**
	 * @brief コンストラクタ
	 * @param [in]プライオリティ
	 */
	CBlock(int nPriority = BLOCK_PRIORITY);
	/**
	 * @brief デストラクタ
	 */
	~CBlock()override;
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
	 * @brief 生成
	 * @param [in]ブロックのタイプ
	 * @param [in]位置
	 * @param [in]方向
	 * @return ブロックのポインタ 
	 */
	static CBlock* Create(BLOCKTYPE type,D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	/**
	 * @brief 破片を生成
	 */
	void CreatePiece();
private:
	static const char* MODEL_NAME;	//モデルの名前

	static const int NUM_PIECE = 5; //壊れた際に生成するピース数
	static const int LIFE = 3;		//ブロックライフ
	static const int NUM_SMOKE = 30; //壊れた際に生成するスモーク数

	static constexpr float PIECE_ROTATION_MAX = 3.0f; //回転範囲最大値
	static constexpr float PIECE_ROTATION_MIN = 0.0f; //回転範囲最小値

	static const D3DXCOLOR SMOKE_COLOR; //壊れた際に生成するスモークの色

	static const D3DXVECTOR3 MOVE_PIECE_SCALE; //動くピースのスケール
	static const D3DXVECTOR3 STACK_PIECE_SCALE; //残るピースのスケール

	BLOCKTYPE m_type;
	bool m_bBreak; //壊せるかどうか
	int m_nLife;
};
#endif