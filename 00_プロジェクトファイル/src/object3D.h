//=============================================
//
//3Dオブジェクト[object3D.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _OBJECT3D_H_ //これが定義されてないとき

#define _OBJECT3D_H_
#include "main.h"
#include "object.h"

//=============================================
//3Dオブジェクトクラス
//=============================================
class CObject3D : public CObject
{
public:
	/**
	 * @brief コンストラクタ
	 * @param [in]プライオリティ
	 */
	CObject3D(int nPriority);
	/**
	 * @brief デストラクタ
	 */
	~CObject3D()override;
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
	 * @param [in]テクスチャ
	 */
	void BindTexture(LPDIRECT3DTEXTURE9 pTex);

	/**
	 * @brief 色設定
	 * @param [in]色
	 */
	inline void SetColor(D3DXCOLOR col)
	{
		m_col = col;
	}

	/**
	 * @brief 位置の設定
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
	 * @brief サイズ設定
	 * @param [in]サイズ
	 */
	inline void SetSize(D3DXVECTOR3 size)
	{
		m_size = size;
	}

	/**
	 * @brief テクスチャ座標代入
	 * @param [in]テクスチャ座標
	 */
	inline void SetTexPos(D3DXVECTOR2 tex)
	{
		m_tex_pos = tex;
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
	 * @brief 頂点バッファ代入
	 * @param [in]頂点バッファ代入
	 */
	inline void SetVtxBuff(LPDIRECT3DVERTEXBUFFER9 vtxBuff)
	{
		m_pVtxBuff = vtxBuff;
	}

	/**
	 * @brief アニメーションフレーム代入
	 * @param [in]アニメーションフレーム
	 */
	inline void SetAnimFrame(int nAnimFrame)
	{
		m_nAnimFrame = nAnimFrame;
	}

	/**
	 * @brief テクスチャ移動量代入
	 * @param [in]テクスチャ移動量
	 */
	inline void SetTexMove(D3DXVECTOR2 tex_move)
	{
		m_tex_move = tex_move;
	}


	/**
	 * @brief 頂点生成
	 * @param [in]法線ベクトル
	 */
	void SetVtx(D3DXVECTOR3 nor);

	/**
	 * @brief 頂点生成
	 * @param [in]法線ベクトル
	 * @param [in]方向
	 * @param [in]距離
	 */
	void SetVtx(D3DXVECTOR3 nor,float fAngle, float fLength);

	/**
	 * @brief 頂点生成
	 * @param [in]法線ベクトル
	 * @param [in]テクスチャ座標
	 * @param [in]テクスチャ移動量
	 */
	void SetVtxAnim(D3DXVECTOR3 nor,D3DXVECTOR2 tex_pos, D3DXVECTOR2 tex_move);

	/**
	 * @brief ゲージ用頂点生成
	 * @param [in]基点位置
	 * @param [in]法線ベクトル
	 */
	void SetGaugeVtx(D3DXVECTOR3 ReferencePos,D3DXVECTOR3 nor);
	/**
	 * @brief 基点足元用頂点生成
	 * @param [in]法線ベクトル
	 */
	void SetVtx_FootPos(D3DXVECTOR3 nor);

	/**
	 * @brief 色の取得
	 * @return 色
	 */
	inline D3DXCOLOR& GetColor()
	{
		return m_col;
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
	 * @brief サイズの取得
	 * @return サイズ
	 */
	inline D3DXVECTOR3& GetSize()
	{
		return m_size;
	}

	/**
	 * @brief テクスチャ座標取得
	 * @return テクスチャ座標
	 */
	inline D3DXVECTOR2& GetTexPos()
	{
		return m_tex_pos;
	}

	/**
	 * @brief 頂点バッファ取得
	 * @return 頂点バッファ
	 */
	inline LPDIRECT3DVERTEXBUFFER9& GetVtxBuff()
	{
		return m_pVtxBuff;
	}

	/**
	 * @brief テクスチャ座標情報取得
	 * @return テクスチャ情報
	 */
	inline LPDIRECT3DTEXTURE9& GetTexture()
	{
		return m_pTexture;
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
	 * @brief アニメーションフレーム取得
	 * @return アニメーションフレーム
	 */
	inline int GetAnimFrame()
	{
		return m_nAnimFrame;
	}

	/**
	 * @brief テクスチャ移動量取得
	 * @return テクスチャ移動量
	 */
	inline D3DXVECTOR2& GetTexMove()
	{
		return m_tex_move;
	}

private:

	LPDIRECT3DTEXTURE9 m_pTexture; //テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff; //頂点バッファへのポインタ

	D3DXCOLOR m_col; //色
	D3DXVECTOR3 m_pos; //位置
	D3DXVECTOR3 m_rot; //方向
	D3DXVECTOR3 m_size; //サイズ
	D3DXVECTOR2 m_tex_pos; //tex座標

	//アニメーション
	int m_nAnimFrame; //アニメーションフレーム
	int m_nAnimCnt; //アニメーションカウント
	D3DXVECTOR2 m_tex_move; //tex移動量

	D3DXMATRIX m_mtxWorld; //ワールドマトリックス
};
#endif