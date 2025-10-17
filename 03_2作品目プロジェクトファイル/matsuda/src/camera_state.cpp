//=============================================
//
//カメラのステートパターン[camera_state.cpp]
//Author Matsuda Towa
//
//=============================================
#include "camera_state.h"
#include "manager.h"

//=============================================
// 自由旋回処理
//=============================================
void My::CFreeView::FreeView(CCamera* camera)
{
	//カメラとの距離設定
	camera->SetLength(LENGTH);

	//入力
	camera->InputMove();
	camera->InputTurn();
}

//=============================================
// 三人称視点処理
//=============================================
void My::CThirdView::ThirdView(CCamera* camera)
{
	//カメラとの距離設定
	camera->SetLength(LENGTH);

	for (int nCnt = 0; nCnt < CObject::MAX_OBJECT; nCnt++)
	{
		//オブジェクト取得
		CObject* pObj = CObject::Getobject(CPlayer::PLAYER_PRIORITY, nCnt);
		if (pObj == nullptr)
		{//ヌルポインタなら
			//オブジェクトを探し続ける
			continue;
		}
		//タイプ取得
		CObject::OBJECT_TYPE type = pObj->GetType();

		if (type != CObject::OBJECT_TYPE::OBJECT_TYPE_PLAYER)
		{//プレイヤーじゃなければ
			//プレイヤーを探し続ける
			continue;
		}
		CPlayer* pPlayer = dynamic_cast<CPlayer*>(pObj);

		//注視点取得
		D3DXVECTOR3 posR = camera->GetPosR();

		//視点取得
		D3DXVECTOR3 posV = camera->GetPosV();

		//方向取得
		D3DXVECTOR3 rot = camera->GetRot();

		//視点、注視点算出処理
		CalculateCameraView(pPlayer, posR, posV, rot);

		//注視点代入
		camera->SetPosR(posR);

		//視点代入
		camera->SetPosV({posV.x,posV.y,posV.z});

		//方向代入
		camera->SetRot(rot);
	};
}

//=============================================
// 視点、注視点算出処理
//=============================================
void My::CThirdView::CalculateCameraView(CPlayer* pPlayer, D3DXVECTOR3& posR, D3DXVECTOR3& posV, D3DXVECTOR3& rot)
{
	//注視点算出
	posR = { pPlayer->GetPos().x, pPlayer->GetPos().y + CORRECT_Y, pPlayer->GetPos().z };

	//視点算出
	posV = { posR + D3DXVECTOR3(LENGTH * cosf(rot.x) * sinf(rot.y), LENGTH * sinf(rot.x), LENGTH * cosf(rot.x) * cosf(rot.y)) };
}

//=============================================
// 上からの視点処理
//=============================================
void My::CTrailView::TrailView(CCamera* camera)
{
	camera->SetLength(LENGTH_Y);
	camera->SetRot({1.4f,0.0f,0.0f});

	for (int nCnt = 0; nCnt < CObject::MAX_OBJECT; nCnt++)
	{
		//オブジェクト取得
		CObject* pObj = CObject::Getobject(CPlayer::PLAYER_PRIORITY, nCnt);
		if (pObj == nullptr)
		{//ヌルポインタなら
			//オブジェクトを探し続ける
			continue;
		}
		//タイプ取得
		CObject::OBJECT_TYPE type = pObj->GetType();

		if (type != CObject::OBJECT_TYPE::OBJECT_TYPE_PLAYER)
		{//プレイヤーじゃなければ
			//プレイヤーを探し続ける
			continue;
		}
		CPlayer* pPlayer = dynamic_cast<CPlayer*>(pObj);

		//注視点取得
		D3DXVECTOR3 posR = camera->GetPosR();

		//視点取得
		D3DXVECTOR3 posV = camera->GetPosV();

		//方向取得
		D3DXVECTOR3 rot = camera->GetRot();

		//視点、注視点算出処理
		CalculateCameraView(pPlayer, posR, posV, rot);

		//注視点代入
		camera->SetPosR(posR);

		//視点代入
		camera->SetPosV(posV);
	};
}

//=============================================
// 視点、注視点算出処理
//=============================================
void My::CTrailView::CalculateCameraView(CPlayer* pPlayer, D3DXVECTOR3& posR, D3DXVECTOR3& posV, D3DXVECTOR3& rot)
{
	// プレイヤーの現在位置
	D3DXVECTOR3 playerPos = pPlayer->GetPos();

	// 注視点のオフセット
	float offsetRight = -280.0f; // プレイヤー右側に

	// 回転（方向）
	float dirSin = sinf(rot.y);
	float dirCos = cosf(rot.y);

	// 注視点 = プレイヤー位置 + 前 + 右 + 上
	posR.x = playerPos.x + dirSin + dirCos;
	posR.y = playerPos.y;
	posR.z = playerPos.z + dirCos - dirSin;

	posV = playerPos;
}

//=============================================
// 横からの視点処理
//=============================================
void My::CSideView::SideView(CCamera* camera)
{
	camera->SetRot({ 0.0f,0.0f,0.0f });

	for (int nCnt = 0; nCnt < CObject::MAX_OBJECT; nCnt++)
	{
		//オブジェクト取得
		CObject* pObj = CObject::Getobject(CPlayer::PLAYER_PRIORITY, nCnt);
		if (pObj == nullptr)
		{//ヌルポインタなら
			//オブジェクトを探し続ける
			continue;
		}
		//タイプ取得
		CObject::OBJECT_TYPE type = pObj->GetType();

		if (type != CObject::OBJECT_TYPE::OBJECT_TYPE_PLAYER)
		{//プレイヤーじゃなければ
			//プレイヤーを探し続ける
			continue;
		}
		CPlayer* pPlayer = dynamic_cast<CPlayer*>(pObj);

		//注視点取得
		D3DXVECTOR3 posR = camera->GetPosR();

		//視点取得
		D3DXVECTOR3 posV = camera->GetPosV();

		//方向取得
		D3DXVECTOR3 rot = camera->GetRot();

		//視点、注視点算出処理
		CalculateCameraView(pPlayer, posR, posV, rot);

		//注視点代入
		camera->SetPosR(posR);

		//視点代入
		camera->SetPosV({ posV.x,posV.y,posV.z });

		D3DXVECTOR3 vecCamera = posR - posV;

		camera->SetLength(sqrtf(vecCamera.y * vecCamera.y + vecCamera.z * vecCamera.z));

		//方向代入
		camera->SetRot(rot);
	};
}

//=============================================
// 視点、注視点算出処理
//=============================================
void My::CSideView::CalculateCameraView(CPlayer* pPlayer, D3DXVECTOR3& posR, D3DXVECTOR3& posV, D3DXVECTOR3& rot)
{
	posR.x = pPlayer->GetPos().x;
	posR.y = CORRECT_Y;
	posR.z = pPlayer->GetPos().z;
	posV.x = posR.x - sinf(rot.y) * LENGTH_X;
	posV.y = LENGTH_Y;
	posV.z = posR.z - cosf(rot.y) * LENGTH_Z;
}

void My::CDiagonaView::DiagonalView(CCamera* camera)
{
	camera->SetLength(LENGTH_Y);
	camera->SetRot({ 1.1f,0.0f,0.0f });

	for (int nCnt = 0; nCnt < CObject::MAX_OBJECT; nCnt++)
	{
		//オブジェクト取得
		CObject* pObj = CObject::Getobject(CPlayer::PLAYER_PRIORITY, nCnt);
		if (pObj == nullptr)
		{//ヌルポインタなら
			//オブジェクトを探し続ける
			continue;
		}
		//タイプ取得
		CObject::OBJECT_TYPE type = pObj->GetType();

		if (type != CObject::OBJECT_TYPE::OBJECT_TYPE_PLAYER)
		{//プレイヤーじゃなければ
			//プレイヤーを探し続ける
			continue;
		}
		CPlayer* pPlayer = dynamic_cast<CPlayer*>(pObj);

		//注視点取得
		D3DXVECTOR3 posR = camera->GetPosR();

		//視点取得
		D3DXVECTOR3 posV = camera->GetPosV();

		//方向取得
		D3DXVECTOR3 rot = camera->GetRot();

		//視点、注視点算出処理
		CalculateCameraView(pPlayer, posR, posV, rot);

		//注視点代入
		camera->SetPosR(posR);

		//視点代入
		camera->SetPosV(posV);
	};
}

void My::CDiagonaView::CalculateCameraView(CPlayer* pPlayer, D3DXVECTOR3& posR, D3DXVECTOR3& posV, D3DXVECTOR3& rot)
{
	// プレイヤーの現在位置
	D3DXVECTOR3 playerPos = pPlayer->GetPos();

	// 回転（方向）
	float dirSin = sinf(rot.y);
	float dirCos = cosf(rot.y);

	// 注視点 = プレイヤー位置 + 前 + 右 + 上
	posR.x = playerPos.x + dirSin + dirCos;
	posR.y = playerPos.y;
	posR.z = playerPos.z + dirCos - dirSin;

	posV = playerPos;
}
