//=============================================
//
//2Dオブジェクト[object2D.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _OBJECT2D_H_ //これが定義されてないとき

#define _OBJECT2D_H_
#include "main.h"
#include "object.h"

//=============================================
//2Dオブジェクトクラス
//=============================================
class CObject2D : public CObject
{
public:
	/**
	 * @brief コンストラクタ
	 * @param [in]プライオリティ
	 */
	CObject2D(int nPriority = 3);
	/**
	 * @brief デストラクタ
	 */
	~CObject2D()override;
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
	 * @brief 位置の代入
	 * @param [in]位置
	 */
	inline void SetPos(D3DXVECTOR3 pos)
	{
		m_pos = pos;
	}

	/**
	 * @brief 方向の代入
	 * @param [in]方向
	 */
	inline void SetRot(D3DXVECTOR3 rot)
	{
		m_rot = rot;
	}

	/**
	 * @brief サイズの代入
	 * @param [in]サイズ
	 */
	inline void SetSize(D3DXVECTOR2 size)
	{
		m_size = size;
	}

	/**
	 * @brief テクスチャ座標の代入
	 * @param [in]テクスチャ座標
	 */
	inline void SetTexPos(D3DXVECTOR2 tex)
	{
		m_tex_pos = tex;
	}

	/**
	 * @brief 頂点バッファ設定
	 * @param [in]頂点バッファ
	 */
	inline void SetVtxBuff(LPDIRECT3DVERTEXBUFFER9 Buff)
	{
		m_pVtxBuff = Buff;
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
	 * @brief 頂点生成
	 * @param [in]rhw
	 */
	void SetVtx(float rhw);

	/**
	 * @brief 頂点生成
	 * @param [in]rhw
	 * @param [in]方向
	 * @param [in]距離
	 */
	void SetVtx(float rhw,float fAngle,float fLength);

	/**
	 * @brief ゲージ用の頂点生成
	 * @param [in]rhw
	 */
	void SetGaugeVtx(float rhw);

	/**
	 * @brief 基点足元の頂点生成
	 * @param [in]rhw
	 * @param [in]方向
	 * @param [in]距離
	 */
	void SetVtx_FootPos(float rhw,float fAngle,float fLength);

	/**
	 * @brief 位置取得
	 * @return 位置
	 */
	inline D3DXVECTOR3& GetPos()
	{
		return m_pos;
	}

	/**
	 * @brief 方向取得
	 * @return 方向
	 */
	inline D3DXVECTOR3& GetRot()
	{
		return m_rot;
	}

	/**
	 * @brief サイズ取得
	 * @return サイズ
	 */
	inline D3DXVECTOR2& GetSize()
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
	 * @brief 色の取得
	 * @return 色
	 */
	inline D3DXCOLOR& GetColor()
	{
		return m_col;
	}

	/**
	 * @brief 頂点バッファ取得
	 * @return 頂点バッファ
	 */
	inline LPDIRECT3DVERTEXBUFFER9& GetVtxBuff()
	{
		return m_pVtxBuff;
	}


private:

	LPDIRECT3DTEXTURE9 m_pTexture; //テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff; //頂点バッファへのポインタ

	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR2 m_size;
	D3DXVECTOR2 m_tex_pos; //tex座標
	D3DXCOLOR m_col;
};
#endif