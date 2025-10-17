//=============================================
//
//レティクル[reticle.h]
//Author Matsuda Towa
//
//=============================================
#include "main.h"
#include "billboard.h"
#include "crosshair.h"
#include"centerdot.h"
#include "hitmaker.h"

#ifndef _RETICLE_H_ //これが定義されてないとき

#define _RETICLE_H_

//=============================================
//レティクルクラス
//=============================================
class CReticle
{
public:
	/**
	 * @brief コンストラクタ
	 */
	CReticle();
	/**
	 * @brief デストラクタ
	 */
	~CReticle();
	/**
	 * @brief 初期化
	 * @return 成功したか
	 */
	HRESULT Init();
	/**
	 * @brief 終了
	 */
	void Uninit();
	/**
	 * @brief 更新
	 */
	void Update();

	/**
	 * @brief 位置代入
	 * @param [in]位置
	 */
	inline void SetPos(D3DXVECTOR3 pos)
	{
		m_ReticlePos = pos;
	}

	/**
	 * @brief サイズ設定
	 * @param [in]サイズ
	 */
	inline void SetSize(D3DXVECTOR3 size)
	{
		m_ReticleSize = size;
	}

	/**
	 * @brief 色設定
	 * @param [in]色
	 */
	inline void SetCol(D3DXCOLOR col)
	{
		m_ReticleCol = col;
	}

	/**
	 * @brief 位置取得
	 * @return 位置
	 */
	inline D3DXVECTOR3& GetReticlePos()
	{
		return m_ReticlePos;
	}

	/**
	 * @brief サイズ取得
	 * @return サイズ
	 */
	inline D3DXVECTOR3& GetReticleSize()
	{
		return m_ReticleSize;
	}

	/**
	 * @brief 色取得
	 * @return 色
	 */
	inline D3DXCOLOR& GetReticleCol()
	{
		return m_ReticleCol;
	}

	CCrossHair* m_pCrosshair;
	CCenterDot* m_pCenterDot;
	CHitMaker* m_pHitMaker;
private:

	D3DXVECTOR3 m_ReticlePos;
	D3DXVECTOR3 m_ReticleSize;
	D3DXCOLOR m_ReticleCol;
};

#endif