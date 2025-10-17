//=============================================
//
//ウェーブリザルト画面[wave_result_screen.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _WAVE_RESULT_SCREEN_H_ //これが定義されてないとき

#define _WAVE_RESULT_SCREEN_H_
#include "main.h"
#include "object2D.h"

//=============================================
//ウェーブリザルト
//=============================================
class CWave_Result_Screen : public CObject2D
{
public:
	static const int RESULT_SCREEN_PRIORITY = 15;  //描画順
	/**
	 * @brief コンストラクタ
	 * @param [in]プライオリティ
	 */
	CWave_Result_Screen(int nPriority = RESULT_SCREEN_PRIORITY);
	/**
	 * @brief デストラクタ
	 */
	~CWave_Result_Screen()override;
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
	 * @return ウェーブUIポインタ
	 */
	static CWave_Result_Screen* Create(D3DXVECTOR3 pos);
private:
	static const D3DXCOLOR COLOR;
};
#endif