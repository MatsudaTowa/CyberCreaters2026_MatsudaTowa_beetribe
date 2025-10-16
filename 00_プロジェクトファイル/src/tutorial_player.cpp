#include "tutorial_player.h"

//=============================================
//コンストラクタ
//=============================================
CTutorialPlayer::CTutorialPlayer(int nPriority):CActivePlayer(nPriority)
{
}

//=============================================
//デストラクタ
//=============================================
CTutorialPlayer::~CTutorialPlayer()
{
}

//=============================================
//初期化
//=============================================
HRESULT CTutorialPlayer::Init()
{
	CActivePlayer::Init();
	return S_OK;
}

//=============================================
//終了
//=============================================
void CTutorialPlayer::Uninit()
{
	CActivePlayer::Uninit();
}

//=============================================
//更新
//=============================================
void CTutorialPlayer::Update()
{
	CActivePlayer::Update();
}

//=============================================
//描画
//=============================================
void CTutorialPlayer::Draw()
{
	CActivePlayer::Draw();
}
