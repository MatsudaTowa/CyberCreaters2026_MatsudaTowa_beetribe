//=============================================
//
//�J�����̃X�e�[�g�p�^�[��[camera_state.cpp]
//Author Matsuda Towa
//
//=============================================
#include "camera_state.h"
#include "manager.h"

//=============================================
// ���R���񏈗�
//=============================================
void My::CFreeView::FreeView(CCamera* camera)
{
	//�J�����Ƃ̋����ݒ�
	camera->SetLength(LENGTH);

	//����
	camera->InputMove();
	camera->InputTurn();
}

//=============================================
// �O�l�̎��_����
//=============================================
void My::CThirdView::ThirdView(CCamera* camera)
{
	//�J�����Ƃ̋����ݒ�
	camera->SetLength(LENGTH);

	for (int nCnt = 0; nCnt < CObject::MAX_OBJECT; nCnt++)
	{
		//�I�u�W�F�N�g�擾
		CObject* pObj = CObject::Getobject(CPlayer::PLAYER_PRIORITY, nCnt);
		if (pObj == nullptr)
		{//�k���|�C���^�Ȃ�
			//�I�u�W�F�N�g��T��������
			continue;
		}
		//�^�C�v�擾
		CObject::OBJECT_TYPE type = pObj->GetType();

		if (type != CObject::OBJECT_TYPE::OBJECT_TYPE_PLAYER)
		{//�v���C���[����Ȃ����
			//�v���C���[��T��������
			continue;
		}
		CPlayer* pPlayer = dynamic_cast<CPlayer*>(pObj);

		//�����_�擾
		D3DXVECTOR3 posR = camera->GetPosR();

		//���_�擾
		D3DXVECTOR3 posV = camera->GetPosV();

		//�����擾
		D3DXVECTOR3 rot = camera->GetRot();

		//���_�A�����_�Z�o����
		CalculateCameraView(pPlayer, posR, posV, rot);

		//�����_���
		camera->SetPosR(posR);

		//���_���
		camera->SetPosV({posV.x,posV.y,posV.z});

		//�������
		camera->SetRot(rot);
	};
}

//=============================================
// ���_�A�����_�Z�o����
//=============================================
void My::CThirdView::CalculateCameraView(CPlayer* pPlayer, D3DXVECTOR3& posR, D3DXVECTOR3& posV, D3DXVECTOR3& rot)
{
	//�����_�Z�o
	posR = { pPlayer->GetPos().x, pPlayer->GetPos().y + CORRECT_Y, pPlayer->GetPos().z };

	//���_�Z�o
	posV = { posR + D3DXVECTOR3(LENGTH * cosf(rot.x) * sinf(rot.y), LENGTH * sinf(rot.x), LENGTH * cosf(rot.x) * cosf(rot.y)) };
}

//=============================================
// �ォ��̎��_����
//=============================================
void My::CTrailView::TrailView(CCamera* camera)
{
	camera->SetLength(LENGTH_Y);
	camera->SetRot({1.4f,0.0f,0.0f});

	for (int nCnt = 0; nCnt < CObject::MAX_OBJECT; nCnt++)
	{
		//�I�u�W�F�N�g�擾
		CObject* pObj = CObject::Getobject(CPlayer::PLAYER_PRIORITY, nCnt);
		if (pObj == nullptr)
		{//�k���|�C���^�Ȃ�
			//�I�u�W�F�N�g��T��������
			continue;
		}
		//�^�C�v�擾
		CObject::OBJECT_TYPE type = pObj->GetType();

		if (type != CObject::OBJECT_TYPE::OBJECT_TYPE_PLAYER)
		{//�v���C���[����Ȃ����
			//�v���C���[��T��������
			continue;
		}
		CPlayer* pPlayer = dynamic_cast<CPlayer*>(pObj);

		//�����_�擾
		D3DXVECTOR3 posR = camera->GetPosR();

		//���_�擾
		D3DXVECTOR3 posV = camera->GetPosV();

		//�����擾
		D3DXVECTOR3 rot = camera->GetRot();

		//���_�A�����_�Z�o����
		CalculateCameraView(pPlayer, posR, posV, rot);

		//�����_���
		camera->SetPosR(posR);

		//���_���
		camera->SetPosV(posV);
	};
}

//=============================================
// ���_�A�����_�Z�o����
//=============================================
void My::CTrailView::CalculateCameraView(CPlayer* pPlayer, D3DXVECTOR3& posR, D3DXVECTOR3& posV, D3DXVECTOR3& rot)
{
	// �v���C���[�̌��݈ʒu
	D3DXVECTOR3 playerPos = pPlayer->GetPos();

	// �����_�̃I�t�Z�b�g
	float offsetRight = -280.0f; // �v���C���[�E����

	// ��]�i�����j
	float dirSin = sinf(rot.y);
	float dirCos = cosf(rot.y);

	// �����_ = �v���C���[�ʒu + �O + �E + ��
	posR.x = playerPos.x + dirSin + dirCos;
	posR.y = playerPos.y;
	posR.z = playerPos.z + dirCos - dirSin;

	posV = playerPos;
}

//=============================================
// ������̎��_����
//=============================================
void My::CSideView::SideView(CCamera* camera)
{
	camera->SetRot({ 0.0f,0.0f,0.0f });

	for (int nCnt = 0; nCnt < CObject::MAX_OBJECT; nCnt++)
	{
		//�I�u�W�F�N�g�擾
		CObject* pObj = CObject::Getobject(CPlayer::PLAYER_PRIORITY, nCnt);
		if (pObj == nullptr)
		{//�k���|�C���^�Ȃ�
			//�I�u�W�F�N�g��T��������
			continue;
		}
		//�^�C�v�擾
		CObject::OBJECT_TYPE type = pObj->GetType();

		if (type != CObject::OBJECT_TYPE::OBJECT_TYPE_PLAYER)
		{//�v���C���[����Ȃ����
			//�v���C���[��T��������
			continue;
		}
		CPlayer* pPlayer = dynamic_cast<CPlayer*>(pObj);

		//�����_�擾
		D3DXVECTOR3 posR = camera->GetPosR();

		//���_�擾
		D3DXVECTOR3 posV = camera->GetPosV();

		//�����擾
		D3DXVECTOR3 rot = camera->GetRot();

		//���_�A�����_�Z�o����
		CalculateCameraView(pPlayer, posR, posV, rot);

		//�����_���
		camera->SetPosR(posR);

		//���_���
		camera->SetPosV({ posV.x,posV.y,posV.z });

		D3DXVECTOR3 vecCamera = posR - posV;

		camera->SetLength(sqrtf(vecCamera.y * vecCamera.y + vecCamera.z * vecCamera.z));

		//�������
		camera->SetRot(rot);
	};
}

//=============================================
// ���_�A�����_�Z�o����
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
		//�I�u�W�F�N�g�擾
		CObject* pObj = CObject::Getobject(CPlayer::PLAYER_PRIORITY, nCnt);
		if (pObj == nullptr)
		{//�k���|�C���^�Ȃ�
			//�I�u�W�F�N�g��T��������
			continue;
		}
		//�^�C�v�擾
		CObject::OBJECT_TYPE type = pObj->GetType();

		if (type != CObject::OBJECT_TYPE::OBJECT_TYPE_PLAYER)
		{//�v���C���[����Ȃ����
			//�v���C���[��T��������
			continue;
		}
		CPlayer* pPlayer = dynamic_cast<CPlayer*>(pObj);

		//�����_�擾
		D3DXVECTOR3 posR = camera->GetPosR();

		//���_�擾
		D3DXVECTOR3 posV = camera->GetPosV();

		//�����擾
		D3DXVECTOR3 rot = camera->GetRot();

		//���_�A�����_�Z�o����
		CalculateCameraView(pPlayer, posR, posV, rot);

		//�����_���
		camera->SetPosR(posR);

		//���_���
		camera->SetPosV(posV);
	};
}

void My::CDiagonaView::CalculateCameraView(CPlayer* pPlayer, D3DXVECTOR3& posR, D3DXVECTOR3& posV, D3DXVECTOR3& rot)
{
	// �v���C���[�̌��݈ʒu
	D3DXVECTOR3 playerPos = pPlayer->GetPos();

	// ��]�i�����j
	float dirSin = sinf(rot.y);
	float dirCos = cosf(rot.y);

	// �����_ = �v���C���[�ʒu + �O + �E + ��
	posR.x = playerPos.x + dirSin + dirCos;
	posR.y = playerPos.y;
	posR.z = playerPos.z + dirCos - dirSin;

	posV = playerPos;
}
