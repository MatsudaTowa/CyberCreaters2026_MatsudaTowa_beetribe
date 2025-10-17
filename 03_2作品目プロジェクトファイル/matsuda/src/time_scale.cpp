//=============================================
//
//���ԊǗ�[time_scale.cpp]
//Author Kasai Keisuke
//
//=============================================
#include "time_scale.h"
#include "game_manager.h"

//=============================================
// �R���X�g���N�^
//=============================================
My::CTimeScale::CTimeScale(float timeScale):
	m_TimeScale(timeScale)
{

}

//=============================================
// ����������
//=============================================
HRESULT My::CTimeScale::Init()
{
	CGameManager::GetInstance()->SetTimeScalePointer(this);

	return S_OK;
}

//=============================================
// �^�C���X�P�[���ݒ�
//=============================================
void My::CTimeScale::SetTimeScale(float timescale)
{
	m_TimeScale = timescale;
}
