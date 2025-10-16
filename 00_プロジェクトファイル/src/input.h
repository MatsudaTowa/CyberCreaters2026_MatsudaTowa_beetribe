//=============================================
//
//3DTemplate[input.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _INPUT_H_ //定義されてなかったら
#define _INPUT_H_ //２種インクルード防止
#include "main.h"

//インプットクラス
class CInput
{
public:
	/**
	 * @brief コンストラクタ
	 */
	CInput();
	/**
	 * @brief デストラクタ
	 */
	~CInput();
	/**
	 * @brief 初期化
	 * @param [in]インスタンス
	 * @param [in]ハンドルワンド
	 * @return 成功したか
	 */
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	/**
	 * @brief 終了
	 */
	virtual void Uninit();
	/**
	 * @brief 更新
	 */
	virtual void Update() = 0;
protected:
	static LPDIRECTINPUT8 m_pInput;
	LPDIRECTINPUTDEVICE8 m_pDevice;
};

//キーボードクラス
class CInputKeyboard:public CInput
{
public:
	static const int NUM_KEY_MAX = 256; //キーボードのキー数
	/**
	 * @brief コンストラクタ
	 */
	CInputKeyboard();
	/**
	 * @brief デストラクタ
	 */
	~CInputKeyboard();
	/**
	 * @brief 初期化
	 * @param [in]インスタンス
	 * @param [in]ハンドルワンド
	 * @return 成功したか
	 */
	HRESULT Init(HINSTANCE hInstance, HWND hWnd) override;
	/**
	 * @brief 終了
	 */
	void Uninit() override;
	/**
	 * @brief 更新
	 */
	void Update() override;

	/**
	 * @brief プレス情報取得
	 * @param [in]キー番号
	 * @return 押されているか
	 */
	inline bool GetPress(int nKey)
	{
		return(m_aKeyState[nKey] & 0x80) != 0;
	}

	/**
	 * @brief トリガー情報取得
	 * @param [in]キー番号
	 * @return 押されているか
	 */
	inline bool GetTrigger(int nKey)
	{
		return(m_aKeyStateTrigger[nKey] & 0x80) != 0;
	}

	/**
	 * @brief リリース情報取得
	 * @param [in]キー番号
	 * @return 離されているか
	 */	
	inline bool GetRelease(int nKey)
	{
		return(m_aKeyStateRelease[nKey] & 0x80) != 0;
	}
private:
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX]; //キーボードのトリガー情報
	BYTE m_aKeyStateRelease[NUM_KEY_MAX]; //キーボードのリリース情報
	BYTE m_aKeyState[NUM_KEY_MAX]; //キーボードのプレス情報
};

//マウスクラス
class CInputMouse :public CInput
{
public:
	static const int NUM_MOUSE_MAX = 3; //マウスのキー数
	/**
	 * @brief コンストラクタ
	 */
	CInputMouse();
	/**
	 * @brief デストラクタ
	 */
	~CInputMouse();
	/**
	 * @brief 初期化
	 * @param [in]インスタンス
	 * @param [in]ハンドルワンド
	 * @return 成功したか
	 */
	HRESULT Init(HINSTANCE hInstance, HWND hWnd) override;
	/**
	 * @brief 終了
	 */
	void Uninit() override;
	/**
	 * @brief 更新
	 */
	void Update() override;

	/**
	 * @brief プレス情報取得
	 * @param [in]キー番号
	 * @return 押されているか
	 */	
	inline bool GetPress(int nKey)
	{
		return(m_KeyState.rgbButtons[nKey] & 0x80) != 0;
	}

	/**
	* @brief トリガー情報取得
	* @param [in]キー番号
	* @return 押されているか
	*/	
	inline bool GetTrigger(int nKey)
	{
		return(m_KeyStateTrigger.rgbButtons[nKey] & 0x80) != 0;
	}

	/**
	* @brief リリース情報取得
	* @param [in]キー番号
	* @return 離されているか
	*/	
	inline bool GetRelease(int nKey)
	{
		return(m_KeyStateRelease.rgbButtons[nKey] & 0x80) != 0;
	}

	/**
	 * @brief 移動量取得
	 * @return 移動量
	 */
	inline D3DXVECTOR3 GetMouseMove(void)
	{
		return m_MouseMove;
	}

	/**
	 * @brief デバッグ情報
	 */
	void Debug();
private:
	DIMOUSESTATE m_KeyStateTrigger; //マウスのトリガー情報
	DIMOUSESTATE m_KeyStateRelease; //マウスのリリース情報
	DIMOUSESTATE m_KeyState; //マウスのプレス情報
	DIMOUSESTATE m_zdiMouseMove; //マウスムーブ
	D3DXVECTOR3 m_MousePos;
	D3DXVECTOR3 m_MouseMove;
};

#endif // _INPUT_H_ //定義されてなかったら