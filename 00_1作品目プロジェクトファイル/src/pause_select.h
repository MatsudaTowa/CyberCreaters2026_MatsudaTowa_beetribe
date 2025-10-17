//=============================================
//
//ポーズのUI[pause_select.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _PAUSE_SELECT_H_ //これが定義されてないとき

#define _PAUSE_SELECT_H_
#include "main.h"
#include "object2D.h"

//=============================================
//ポーズ選択UIクラス
//=============================================
class CPauseSelect : public CObject2D
{
public:
	static const int PRIORITY = 29;  //描画順

	/**
	 * @brief コンストラクタ
	 * @param [in]プライオリティ
	 */
	CPauseSelect(int nPriority = PRIORITY);

	/**
	 * @brief デストラクタ
	 */
	~CPauseSelect()override;
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
	 * @param [in]ポーズのUIポインタ
	 * @return ポーズのUIポインタ
	 */
	static CPauseSelect* Create(D3DXVECTOR3 pos,CPauseSelect* select);

	/**
	 * @brief 選択されたか
	 * @return どれを選択されたか
	 */
	bool GetSelect()
	{
		return m_isSelect;
	}

	/**
	 * @brief 選択されたか
	 * @param [in]isSelect
	 */
	void SetSelect(bool isSelect)
	{
		m_isSelect = isSelect;
	}

private:
	static const D3DXCOLOR DEFAULT_COLOR;
	static const D3DXVECTOR2 SIZE;
	bool m_isSelect;	//マウスカーソルとヒットしたか
};
#endif