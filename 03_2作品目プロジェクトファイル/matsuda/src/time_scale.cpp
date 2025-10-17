//=============================================
//
//時間管理[time_scale.cpp]
//Author Kasai Keisuke
//
//=============================================
#include "time_scale.h"
#include "game_manager.h"

//=============================================
// コンストラクタ
//=============================================
My::CTimeScale::CTimeScale(float timeScale):
	m_TimeScale(timeScale)
{

}

//=============================================
// 初期化処理
//=============================================
HRESULT My::CTimeScale::Init()
{
	CGameManager::GetInstance()->SetTimeScalePointer(this);

	return S_OK;
}

//=============================================
// タイムスケール設定
//=============================================
void My::CTimeScale::SetTimeScale(float timescale)
{
	m_TimeScale = timescale;
}
