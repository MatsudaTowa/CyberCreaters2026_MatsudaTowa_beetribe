//=============================================
//
//Xファイルオブジェクト[objectX.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _OBJECTX_H_ //これが定義されてないとき

#define _OBJECTX_H_
#include "main.h"
#include "object.h"

//=============================================
//Xファイルオブジェクトクラス
//=============================================
class CObjectX : public CObject
{
public:
	static const int MAX_TEX = 256; //テクスチャの数

	/**
	 * @brief コンストラクタ
	 * @param [in]プライオリティ
	 */
	CObjectX(int nPriority);
	/**
	 * @brief デストラクタ
	 */
	~CObjectX()override;
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
	 * @brief テクスチャ設定
	 * @param [in]テクスチャ情報
	 * @param [in]番号
	 */
	void BindTexture(LPDIRECT3DTEXTURE9 pTex,int Idx);

	/**
	 * @brief Xファイル設定
	 * @param [in]マテリアル情報
	 * @param [in]マテリアル数
	 * @param [in]メッシュ情報
	 */
	void BindXFile(LPD3DXBUFFER pBuffMat, DWORD dwNumMat, LPD3DXMESH pMesh);

	/**
	 * @brief スケール代入
	 * @param [in]スケール倍率
	 */
	inline void SetScale(D3DXVECTOR3 scale)
	{
		m_scale = scale;
	}

	/**
	 * @brief 位置の代入
	 * @param [in]位置
	 */
	inline void SetPos(D3DXVECTOR3 pos)
	{
		m_pos = pos;
	}

	/**
	 * @brief 方向の設定
	 * @param [in]方向
	 */
	inline void SetRot(D3DXVECTOR3 rot)
	{
		m_rot = rot;
	}

	/**
	 * @brief 最小値代入
	 * @param [in]最小値
	 */
	inline void SetMinPos(D3DXVECTOR3 MinPos)
	{
		m_minpos = MinPos;
	}

	/**
	 * @brief 最大値代入
	 * @param [in]最大値
	 */
	inline void SetMaxPos(D3DXVECTOR3 MaxPos)
	{
		m_maxpos = MaxPos;
	}

	/**
	 * @brief ワールドマトリックス代入
	 * @param [in]ワールドマトリックス
	 */
	inline void SetMtxWorld(D3DXMATRIX mtxWorld)
	{
		m_mtxWorld = mtxWorld;
	}

	/**
	 * @brief 色の代入
	 * @param [in]色
	 */
	inline void SetColor(D3DXCOLOR col)
	{
		m_col = col;
	}

	/**
	 * @brief スケールの取得
	 * @return スケール
	 */
	inline D3DXVECTOR3& GetScale()
	{
		return m_scale;
	}

	/**
	 * @brief 位置の取得
	 * @return 位置
	 */
	inline D3DXVECTOR3& GetPos()
	{
		return m_pos;
	}

	/**
	 * @brief 方向の取得
	 * @return 方向
	 */
	inline D3DXVECTOR3& GetRot()
	{
		return m_rot;
	}

	/**
	 * @brief 最小値取得
	 * @return 最小値
	 */
	D3DXVECTOR3& GetMinPos();

	/**
	 * @brief 最大値取得
	 * @return 最大値
	 */
	D3DXVECTOR3& GetMaxPos();

	/**
	 * @brief メッシュ情報取得
	 * @return メッシュ情報
	 */
	inline LPD3DXMESH& GetpMesh()
	{
		return m_pMesh;
	}

	/**
	 * @brief マテリアル情報取得
	 * @return マテリアル情報
	 */
	inline LPD3DXBUFFER& GetpBuffMat()
	{
		return m_pBuffMat;
	}

	/**
	 * @brief マテリアル数取得
	 * @return マテリアル数
	 */
	inline DWORD& GetNumMat()
	{
		return m_dwNumMat;
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
	 * @brief カラー取得
	 * @return カラー
	 */
	inline D3DXCOLOR& GetCol()
	{
		return m_col;
	}

private:

	LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEX]; //テクスチャへのポインタ

	D3DXVECTOR3 m_scale;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_minpos; //pos最小値
	D3DXVECTOR3 m_maxpos; //pos最大値

	D3DXMATRIX m_mtxWorld; //ワールドマトリックス
	
	LPD3DXMESH m_pMesh; //メッシュ情報
	LPD3DXBUFFER m_pBuffMat; //マテリアル情報
	DWORD m_dwNumMat; //マテリアル数

	D3DXCOLOR m_col; //カラーの値
};
#endif