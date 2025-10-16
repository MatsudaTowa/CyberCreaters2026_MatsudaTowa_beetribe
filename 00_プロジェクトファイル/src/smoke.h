//=============================================
//
//スモーク処理[somoke.h]
//Author Matsuda Towa
//
//=============================================
#include "main.h"
#include "billboard.h"

#ifndef _SMOKE_H_ //これが定義されてないとき

#define _SMOKE_H_

//=============================================
// スモーククラス
//=============================================
class CSmoke : public CBillboard
{
public:
	static const std::string SMOKE_TEXTURE_NAME; //テクスチャの名前
	static const int SMOKE_LIFE = 300; //スモークの持続時間

	static const int SMOKE_PRIORITY = 10; //描画順

	enum SMOKE_TYPE
	{
		SMOKE_TYPE_TACTICAL	= 0,
		SMOKE_TYPE_BROKEN
	};

	/**
	 * @brief コンストラクタ
	 * @param [in]プライオリティ
	 */
	CSmoke(int nPriority = SMOKE_PRIORITY);
	/**
	 * @brief デストラクタ
	 */
	~CSmoke()override;
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
	 * @param [in]位置
	 * @param [in]スモークのタイプ
	 * @return スモークポインタ
	 */
	static CSmoke* Create(D3DXVECTOR3 pos, SMOKE_TYPE type);

	/**
	 * @brief 移動量設定
	 * @param [in]移動量
	 */
	inline void SetMove(D3DXVECTOR3 move)
	{
		m_move = move;
	}

	/**
	 * @brief 移動量取得
	 * @return 移動量
	 */
	inline D3DXVECTOR3& GetMove()
	{
		return m_move;
	}

private:
	static constexpr float FADE_VALUE = 0.1f;  //アルファ値減衰量

	/**
	 * @brief 移動処理
	 */
	void Move();

	/**
	 * @brief フェードアウト
	 */
	void FadeOut();

	int m_nLife;
	D3DXVECTOR3 m_move;
};

#endif