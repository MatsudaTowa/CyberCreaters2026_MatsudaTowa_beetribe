//=============================================
//
//描画処理[renderer.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _RENDERER_H_ //これが定義されてないとき

#define _RENDERER_H_

//=============================================
//レンダラークラス
//=============================================
class CRenderer
{
public:
	/**
	 * @brief コンストラクタ
	 */
	CRenderer();
	/**
	 * @brief デストラクタ
	 */
	~CRenderer();
	/**
	 * @brief 初期化
	 * @param [in]ハンドルワンド
	 * @param [in]ウィンドウが生成出来たか
	 * @return 成功したか
	 */
	HRESULT Init(HWND hWnd,BOOL bWindow);
	/**
	 * @brief 終了
	 */
	void Uninit();
	/**
	 * @brief 更新
	 */
	void Update();
	/**
	 * @brief 描画
	 */
	void Draw();
	/**
	 * @brief FPS表示
	 * @param [in]FPSカウント
	 */
	void DrawFPS(int nCntFPS);

	/**
	 * @brief デバイス取得
	 * @return デバイス
	 */
	static LPDIRECT3DDEVICE9 GetDevice();

	/**
	 * @brief フォント取得
	 * @return フォント
	 */
	LPD3DXFONT GetFont();
private:
	int m_DrawCnt;		//カーソル描画カウント
	LPD3DXFONT m_pFont; //フォントへのポインタ

	LPDIRECT3D9	m_pD3D; //Direct3Dオブジェクトへのポインタ
	static LPDIRECT3DDEVICE9 m_pD3DDevice; //Direct3Dデバイスへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffMain; //頂点バッファへのポインタ
};
#endif