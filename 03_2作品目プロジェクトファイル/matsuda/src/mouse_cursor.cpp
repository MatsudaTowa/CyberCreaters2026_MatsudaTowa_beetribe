//=============================================
//
//マウスのカーソル[mouse_cursor.cpp]
//Author Matsuda Towa
//
//=============================================
#include "mouse_cursor.h"
#include "field.h"
#include "mouse_trail.h"
#include "board_holder.h"

const std::string My::CMouseCursor::TEX_PATH = "data\\TEXTURE\\mouse_cursor_normal.png"; //ファイルパス

namespace
{
	const D3DXVECTOR2 POLY_SIZE = { 40.5f,40.5f };					//ポリゴンサイズ
}

//=============================================
//コンストラクタ
//=============================================
My::CMouseCursor::CMouseCursor(int nPriority):CObject2D(nPriority),
m_oldpos(VEC3_RESET_ZERO)				//過去の位置
{
}

//=============================================
//デストラクタ
//=============================================
My::CMouseCursor::~CMouseCursor()
{
}

//=============================================
//初期化
//=============================================
HRESULT My::CMouseCursor::Init()
{
	//親クラスの初期化を呼ぶ
	CObject2D::Init();

	//サイズ設定
	SetSize(POLY_SIZE);

	//色設定
	SetColor(COLOR_WHITE);

	//頂点設定
	SetVtx();

	return S_OK;
}

//=============================================
//終了
//=============================================
void My::CMouseCursor::Uninit()
{
	//親クラスの終了を呼ぶ
	CObject2D::Uninit();
}

//=============================================
//更新
//=============================================
void My::CMouseCursor::Update()
{
	//親クラスの更新を呼ぶ
	CObject2D::Update();

	POINT pMouseMove;

	GetCursorPos(&pMouseMove);

	m_oldpos = GetPos();

	D3DXVECTOR3 pos = { (float)pMouseMove.x ,(float)pMouseMove.y, 0.0f};

	SetPos(pos);

	//頂点設定
	SetVtx();
}

//=============================================
//描画
//=============================================
void My::CMouseCursor::Draw()
{
	//親クラスの描画を呼ぶ
	CObject2D::Draw();
}


//=============================================
//生成
//=============================================
My::CMouseCursor* My::CMouseCursor::Create(CMouseCursor* mouse_cursor)
{
	CTexture* pTexture = GET_TEXTURE;
	CMouseCursor* pMouseCursor = mouse_cursor;

	//nullならnullを返す
	if (pMouseCursor == nullptr) { return nullptr; }

	pMouseCursor->BindTexture(pTexture->GetAddress(pTexture->Regist(&TEX_PATH)));

	pMouseCursor->SetType(OBJECT_MOUSE); //タイプ設定

	pMouseCursor->Init();

	return pMouseCursor;
}
