//=============================================
//
//インプット[input.cpp]
//Author Matsuda Towa
//
//=============================================
#include "input.h"
#include "manager.h"

//静的メンバ初期化
LPDIRECTINPUT8 CInput::m_pInput = nullptr;

//=============================================
//コンストラクタ
//=============================================
CInput::CInput()
{
	m_pDevice = nullptr;
}

//=============================================
//デストラクタ
//=============================================
CInput::~CInput()
{
}

//=============================================
//初期化
//=============================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pInput == nullptr)
	{
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
		{
			return E_FAIL;
		}
	}
	return S_OK;
}

//=============================================
//終了
//=============================================
void CInput::Uninit()
{
	//入力デバイスの破棄
	if (m_pDevice != nullptr)
	{
		m_pDevice->Unacquire();
		m_pDevice = nullptr;
	}

	//DirectInputオブジェクトの破棄
	if (m_pInput != nullptr)
	{
		m_pInput->Release();
		m_pInput = nullptr;
	}
	
	delete this;
}

//↓からキーボード

//=============================================
//コンストラクタ
//=============================================
CInputKeyboard::CInputKeyboard()
{
}

//=============================================
//デストラクタ
//=============================================
CInputKeyboard::~CInputKeyboard()
{
}


//=============================================
//初期化
//=============================================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance,hWnd);
	//入力デバイスの生成
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}
	//データフォーマットを設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	//協調モードを設定
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}
	//キーボードのアクセス権を獲得
	m_pDevice->Acquire();
	return S_OK;
}

//=============================================
//終了
//=============================================
void CInputKeyboard::Uninit()
{
	CInput::Uninit();
}

//=============================================
//更新
//=============================================
void CInputKeyboard::Update()
{
	BYTE aKeyState[NUM_KEY_MAX]; //入力情報
	int nCntKey;
	//入力デバイスからデータを取得
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = INT_ZERO; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			m_aKeyStateRelease[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & ~aKeyState[nCntKey]; //リリース
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];
			m_aKeyState[nCntKey] = aKeyState[nCntKey]; //キーボードのプレス情報を保存
		}
	}
	else
	{
		m_pDevice->Acquire(); //キーボードのアクセス権を獲得
	}
}
//↓からマウス

//=============================================
//コンストラクタ
//=============================================
CInputMouse::CInputMouse()
{
}

//=============================================
//デストラクタ
//=============================================
CInputMouse::~CInputMouse()
{
}

//=============================================
//初期化
//=============================================
HRESULT CInputMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInputオブジェクトの生成
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
	{
		return E_FAIL;
	}
	//入力デバイスの生成
	if (FAILED(m_pInput->CreateDevice(GUID_SysMouse, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}
	//データフォーマットを設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIMouse)))
	{
		return E_FAIL;
	}
	//協調モードを設定
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}
	// デバイスの設定
	DIPROPDWORD diprop;
	m_MousePos = VEC3_RESET_ZERO;
	m_MouseMove = VEC3_RESET_ZERO;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = INT_ZERO;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = DIPROPAXISMODE_REL;


	if (FAILED(m_pDevice->SetProperty(DIPROP_AXISMODE, &diprop.diph)))
	{
		// デバイスの設定に失敗
		return E_FAIL;
	}

	//マウスのアクセス権を獲得
	m_pDevice->Acquire();
	return S_OK;
}

//=============================================
//終了
//=============================================
void CInputMouse::Uninit()
{
	CInput::Uninit();
}

//=============================================
//更新
//=============================================
void CInputMouse::Update()
{

	DIMOUSESTATE zdiMouseState;
	int nCntMouse;
	
	//入力デバイスからデータを取得
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(zdiMouseState), &zdiMouseState)))
	{
		for (nCntMouse = INT_ZERO; nCntMouse < NUM_MOUSE_MAX; nCntMouse++)
		{
			m_KeyStateRelease.rgbButtons[nCntMouse] = (m_KeyState.rgbButtons[nCntMouse] ^ zdiMouseState.rgbButtons[nCntMouse]) & ~zdiMouseState.rgbButtons[nCntMouse];
			m_KeyStateTrigger.rgbButtons[nCntMouse] = (m_KeyState.rgbButtons[nCntMouse] ^ zdiMouseState.rgbButtons[nCntMouse]) & zdiMouseState.rgbButtons[nCntMouse];
			m_KeyState.rgbButtons[nCntMouse] = zdiMouseState.rgbButtons[nCntMouse]; //キーボードのプレス情報を保存
		}
		
		m_MouseMove.x = (float)zdiMouseState.lX;
		m_MouseMove.y = (float)zdiMouseState.lY;
	}
	else
	{
		m_pDevice->Acquire(); //キーボードのアクセス権を獲得
	}
}

//=============================================
//マウスのデバッグ表示
//=============================================
void CInputMouse::Debug()
{
#ifdef _DEBUG
	LPD3DXFONT pFont = CManager::GetInstance()->GetRenderer()->GetFont();
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];
	POINT pMousePos;
	GetCursorPos(&pMousePos);
	ScreenToClient(CManager::GetInstance()->GetHWnd(), &pMousePos);
	sprintf(&aStr[0], "[mouse]\nmove:%.1f,%.1f,%.1f\npos%.1f,%.1f"
		, m_MouseMove.x, m_MouseMove.y, m_MouseMove.z,(float)pMousePos.x,(float)pMousePos.y);
	//テキストの描画
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_RIGHT, D3DCOLOR_RGBA(255, 0, 0, 255));
#endif // _DEBUG


}