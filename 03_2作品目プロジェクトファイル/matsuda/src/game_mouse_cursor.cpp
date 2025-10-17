//=============================================
//
//ゲームマウスのカーソル[game_mouse_cursor.cpp]
//Author Matsuda Towa
//
//=============================================
#include "game_mouse_cursor.h"
#include "field.h"
#include "mouse_trail.h"
#include "board_holder.h"
#include "game_manager.h"

const std::string My::CGameMouseCursor::WRITE_TEX_PATH = "data\\TEXTURE\\mouse_cursor_write_anim.png"; //ファイルパス

//=============================================
//コンストラクタ
//=============================================
My::CGameMouseCursor::CGameMouseCursor(int nPriority) :CMouseCursor(nPriority),
m_pMouse_Trail_Point(),					//軌跡生成ポイント初期化
m_max_tex_x(FLOAT_ZERO),				//テクスチャ座標最大値
m_min_tex_x(FLOAT_ZERO),				//テクスチャ座標最小値
m_pState(nullptr)						//マウスの状態
{
}

//=============================================
//デストラクタ
//=============================================
My::CGameMouseCursor::~CGameMouseCursor()
{
	for (auto& itr : m_pMouse_Trail_Point)
	{//生成した分だけ削除
		if (itr == nullptr) { continue; }

		itr->Uninit();
		itr = nullptr;
	}
	m_pMouse_Trail_Point.clear();
}

//=============================================
//初期化
//=============================================
HRESULT My::CGameMouseCursor::Init()
{
	//テクスチャ取得
	CTexture* pTexture = GET_TEXTURE;

	BindTexture(pTexture->GetAddress(pTexture->Regist(&WRITE_TEX_PATH)));
	if (m_pState == nullptr)
	{
		m_pState = new CNormalCursol;
	}

	m_min_tex_x = 1.0f / (float)SPLIT * (SPLIT - 1);
	m_max_tex_x = 1.0f / (float)SPLIT * SPLIT;

	CGameManager::GetInstance()->SetMouseCursor(this);
	//親クラスの初期化を呼ぶ
	CMouseCursor::Init();

	return S_OK;
}

//=============================================
//終了
//=============================================
void My::CGameMouseCursor::Uninit()
{
	if (m_pState != nullptr)
	{
		delete m_pState;
		m_pState = nullptr;
	}

	for (auto& itr : m_pMouse_Trail_Point)
	{//生成した分だけ削除
		if (itr == nullptr) { continue; }

		itr->Uninit();
		itr = nullptr;
	}
	m_pMouse_Trail_Point.clear();

	//親クラスの終了を呼ぶ
	CMouseCursor::Uninit();
}

//=============================================
//更新
//=============================================
void My::CGameMouseCursor::Update()
{
	if (m_pState != nullptr)
	{
		m_pState->Normal(this);
		m_pState->Write(this);
		m_pState->Written(this);
		m_pState->Pause(this);
	}

	//親クラスの更新を呼ぶ
	CMouseCursor::Update();
	SetTexPos();
}

//=============================================
//ステート変更
//=============================================
void My::CGameMouseCursor::ChangeState(CMouseCursorState* state)
{
	//今のステートを消し引数のステートに切り替える
	if (m_pState != nullptr)
	{
		if (typeid(*m_pState) == typeid(*state))
		{
			return;
		}
		delete m_pState;
		m_pState = state;
	}
}

//=============================================
//テクスチャ座標設定
//=============================================
void My::CGameMouseCursor::SetTexPos()
{

	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;

	LPDIRECT3DVERTEXBUFFER9 pBuff = GetVtxBuff();

	if (pBuff == nullptr)
	{
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &pBuff, NULL);
	}
	VERTEX_2D* pVtx;
	//頂点バッファをロックし頂点情報へのポインタを取得
	pBuff->Lock(0, 0, (void**)&pVtx, 0);
	pVtx[0].tex = D3DXVECTOR2(m_min_tex_x, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(m_max_tex_x, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(m_min_tex_x, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(m_max_tex_x, 1.0f);

	//アンロック
	pBuff->Unlock();

	SetVtxBuff(pBuff);
}

//=============================================
//描画
//=============================================
void My::CGameMouseCursor::Draw()
{
	//親クラスの描画を呼ぶ
	CMouseCursor::Draw();
	DebugDraw();
}

//=============================================
//軌跡の数描画
//=============================================
void My::CGameMouseCursor::DebugDraw() 
{
#ifdef _DEBUG
	LPD3DXFONT pFont = CManager::GetInstance()->GetRenderer()->GetFont();
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	sprintf(&aStr[0], "\n\n\n\n\n\n\n\n軌跡の数%d"
		,m_pMouse_Trail_Point.size());
	//テキストの描画
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 0, 0, 255));
#endif // _DEBUG
}