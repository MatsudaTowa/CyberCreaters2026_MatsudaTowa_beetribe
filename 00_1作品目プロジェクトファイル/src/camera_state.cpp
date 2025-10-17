//=============================================
//
//カメラのステートパターン[camera_state.cpp]
//Author Matsuda Towa
//
//=============================================
#include "camera_state.h"
#include "manager.h"

//=============================================
//自由視点
//=============================================
void CCameraState::FreeView([[maybe_unused]] CCamera* camera)
{
}

//=============================================
//三人称の状態
//=============================================
void CCameraState::ThirdView([[maybe_unused]] CCamera* camera)
{
}

//=============================================
//ウルトの状態
//=============================================
void CCameraState::Ult([[maybe_unused]] CCamera* camera)
{
}

//=============================================
//自由旋回状態
//=============================================
void CFreeView::FreeView(CCamera* camera)
{
	//カメラとの距離設定
	camera->SetLength(FREEVIEW_LENGTH);

	//入力
	camera->InputMove();
	
	//キーボード情報取得
	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetKeyboard();
	if (pKeyboard->GetTrigger(DIK_V))
	{
		camera->ChangeCameraState(new CThirdView);
	}
}

//=============================================
//三人称の状態
//=============================================
void CThirdView::ThirdView(CCamera* camera)
{
	camera->SetLength(THIRDVIEW_LENGTH);

	camera->ThirdViewCamera();

#ifdef _DEBUG

	//キーボード情報取得
	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetKeyboard();
	if (pKeyboard->GetTrigger(DIK_B))
	{
		camera->ChangeCameraState(new CFreeView);
	}
#endif // _DEBUG

}

//=============================================
//ウルトの状態
//=============================================
void CUltCameraState::Ult(CCamera* camera)
{
	camera->SetLength(ULT_LENGTH);
	camera->ThirdViewCamera();
}
