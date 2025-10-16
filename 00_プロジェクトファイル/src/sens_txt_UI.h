//=============================================
//
//感度の文字UI[sens_txt_UI.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _SENS_TXT_UI_H_ //これが定義されてないとき

#define _SENS_TXT_UI_H_
#include "main.h"
#include "object2D.h"

//=============================================
//感度の文字UIクラス
//=============================================
class CSensTxtUI : public CObject2D
{
public:
	static const int PRIORITY = 29;  //描画順

	/**
	 * @brief コンストラクタ
	 * @param [in]プライオリティ
	 */
	CSensTxtUI(int nPriority = PRIORITY);
	/**
	 * @brief デストラクタ
	 */
	~CSensTxtUI()override;
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
	 * @param [in]サイズ
	 * @return 感度の文字UIポインタ
	 */
	static CSensTxtUI* Create(D3DXVECTOR3 pos, D3DXVECTOR2 size);
private:
	static const std::string TEXTURE_NAME;	//テクスチャの名前
};
#endif