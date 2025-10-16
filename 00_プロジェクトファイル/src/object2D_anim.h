//=============================================
//
//アニメーションする2Dオブジェクト[move_texture.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _MOVE_TEXTURE_H_ //これが定義されてないとき

#define _MOVE_TEXTURE_H_
#include "main.h"
#include "object2D.h"

//=============================================
//アニメーション2Dクラス
//=============================================
class CObject2D_Anim : public CObject2D
{
public:
	/**
	 * @brief コンストラクタ
	 * @param [in]プライオリティ
	 */
	CObject2D_Anim(int nPriority);
	/**
	 * @brief デストラクタ
	 */
	~CObject2D_Anim()override;

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
	 * @brief アニメーション座標設定
	 * @param [in]テクスチャ座標
	 * @param [in]テクスチャ移動量
	 */
	void AnimationTex(D3DXVECTOR2 tex_pos, D3DXVECTOR2 tex_move);

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
	//アニメーション
	int m_nAnimFrame; //アニメーションフレーム
	int m_nAnimCnt; //アニメーションカウント
	D3DXVECTOR2 m_tex_move; //tex移動量

};
#endif