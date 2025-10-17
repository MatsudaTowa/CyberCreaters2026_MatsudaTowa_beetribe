//=============================================
// 
//親子関係のパーツ[model.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _MODEL_PARTS_H_ //これが定義されてないとき

#define _MODEL_PARTS_H_
#include "main.h"
#include "objectX.h"
#include "block.h"

//=============================================
// モデルパーツクラス
//=============================================
class CModel_Parts
{
public:
	static const int MAX_MODEL = 256; //モデルの数

	//モデル情報構造体定義
	struct MODEL_INFO
	{
		LPD3DXMESH pMesh; //メッシュ情報
		LPD3DXBUFFER pBuffMat; //マテリアル情報
		DWORD dwNumMat; //マテリアル数;
		char* ModelName; //モデルネーム保存用
	};

	struct ColisionBlockInfo
	{
		bool bColision_X; //X軸に当たっている
		bool bColision_Y; //Y軸に当たっている
		bool bColision_Z; //Z軸に当たっている

		float Radius;
		CBlock* pBlock;
	};

	/**
	 * @brief コンストラクタ
	 */
	CModel_Parts();
	/**
	 * @brief デストラクタ
	 */
	~CModel_Parts();

	/**
	 * @brief モデル破棄
	 */
	void Unload();
	/**
	 * @brief モデル設定
	 * @param [in]マテリアルバッファ
	 * @param [in]マテリアル数
	 * @param [in]メッシュ情報
	 */
	void BindXFile(LPD3DXBUFFER pBuffMat, DWORD dwNumMat, LPD3DXMESH pMesh);

	/**
	 * @brief 描画
	 */
	void Draw();
	/**
	 * @brief 描画
	 * @param [in]色
	 */
	void Draw(D3DXCOLOR col);

	/**
	 * @brief ワールドマトリックス変換
	 */
	void ConversionMtxWorld();

	/**
	 * @brief パーツ生成
	 * @param [in]位置
	 * @param [in]方向
	 * @param [in]モデルのパス
	 * @return モデルパーツポインタ
	 */
	static CModel_Parts*Create(D3DXVECTOR3 pos,D3DXVECTOR3 rot,char* pModel_Path);

	/**
	 * @brief ワールドマトリックスの代入
	 * @param [in]ワールドマトリックス
	 */
	inline void SetMtxWorld(D3DXMATRIX mtxWorld)
	{
		m_mtxWorld = mtxWorld;
	}

	/**
	 * @brief 位置の代入
	 * @param [in]位置
	 */
	inline void SetPos(D3DXVECTOR3 pos)
	{
		m_pos = pos;
	};

	/**
	 * @brief Tポーズの位置代入
	 * @param [in]Tポーズの位置
	 */
	inline void SetTPos(D3DXVECTOR3 Tpos)
	{
		m_Tpos = Tpos;
	};

	/**
	 * @brief 過去の位置代入
	 * @param [in]過去の位置
	 */
	inline void SetOldPos(D3DXVECTOR3 oldpos)
	{
		m_oldpos = oldpos;
	};

	/**
	 * @brief 方向代入
	 * @param [in]方向
	 */
	inline void SetRot(D3DXVECTOR3 rot)
	{
		m_rot = rot;
	};

	/**
	 * @brief Tポーズ方向代入
	 * @param [in]方向
	 */
	inline void SetTRot(D3DXVECTOR3 Trot)
	{
		m_Trot = Trot;
	};

	/**
	 * @brief ブロックの判定情報代入
	 * @param [in]ブロックの判定情報
	 */
	inline void SetColisionBlockInfo(ColisionBlockInfo ColisionBlockInfo)
	{
		m_ColisionBlockInfo = ColisionBlockInfo;
	}

	/**
	 * @brief 親代入
	 * @param [in]親情報
	 */	
	inline void SetParent(CModel_Parts* pParent)
	{
		m_pParent = pParent;
	}

	/**
	 * @brief パーツ番号
	 * @param [in]番号
	 */
	inline void SetIdx(int nIdx)
	{
		m_nIdx = nIdx;
	}

	/**
	 * @brief 親番号代入
	 * @param [in]親番号
	 */
	inline void SetParentIdx(int nParent)
	{
		m_nIdxModelParent = nParent;
	}

	/**
	 * @brief 位置情報取得
	 * @return 位置
	 */
	inline D3DXVECTOR3 GetPos()
	{
		return m_pos;
	};

	/**
	 * @brief Tポーズの位置情報取得
	 * @return Tポーズ位置
	 */
	inline D3DXVECTOR3 GetTPos()
	{
		return m_Tpos;
	};

	/**
	 * @brief 過去の位置情報取得
	 * @return 過去の位置
	 */
	inline D3DXVECTOR3 GetOldPos()
	{
		return m_oldpos;
	};

	/**
	 * @brief 方向情報取得
	 * @return 方向
	 */
	inline D3DXVECTOR3 GetRot()
	{
		return m_rot;
	};

	/**
	 * @brief Tポーズの方向取得
	 * @return Tポーズの方向
	 */
	inline D3DXVECTOR3 GetTRot()
	{
		return m_Trot;
	};

	/**
	 * @brief 最小位置取得
	 * @return 最小位置
	 */
	inline D3DXVECTOR3 GetMin()
	{
		return m_minpos;
	}

	/**
	 * @brief 最大位置取得
	 * @return 最大位置
	 */
	inline D3DXVECTOR3 GetMax()
	{
		return m_maxpos;
	}

	/**
	 * @brief モデル番号取得
	 * @return モデル番号
	 */
	inline int GetIdx()
	{
		return m_nIdx;
	}

	/**
	 * @brief モデルの親番号取得
	 * @return モデルの親番号
	 */
	inline int GetParentIdx()
	{
		return m_nIdxModelParent;
	}

	/**
	 * @brief ブロックの判定情報取得
	 * @return ブロックの判定情報
	 */
	inline ColisionBlockInfo& GetColisionBlockInfo()
	{
		return m_ColisionBlockInfo;
	}

	/**
	 * @brief ワールドマトリックス取得
	 * @return ワールドマトリックス
	 */
	inline D3DXMATRIX& GetMtxWorld()
	{
		return m_mtxWorld;
	}

	/**
	 * @brief モデル情報取得
	 * @param [in]番号
	 * @return モデル情報
	 */
	inline MODEL_INFO GetModelInfo(int nIdx)
	{
		return m_ModelInfo[nIdx];
	}

private:
	LPDIRECT3DTEXTURE9 m_pTexture[256]; //テクスチャへのポインタ
	D3DXMATRIX m_mtxWorld; //ワールドマトリックス
	MODEL_INFO m_ModelInfo[MAX_MODEL]; //モデル情報

	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_Tpos;
	D3DXVECTOR3 m_Trot;
	int m_nIdx; //何番目のパーツか
	int m_nIdxModelParent; //親のインデックス

	D3DXVECTOR3 m_minpos; //pos最小値
	D3DXVECTOR3 m_maxpos; //pos最大値
	D3DXVECTOR3 m_oldpos;
	int m_nNumAll; //モデル総数

	CModel_Parts*m_pParent; //親パーツへのポインタ
	ColisionBlockInfo m_ColisionBlockInfo; //当たった軸

};
#endif