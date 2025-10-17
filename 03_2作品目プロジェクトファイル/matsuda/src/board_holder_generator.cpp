//=============================================
//
//��������[board_holder_generator.cpp]
//Auther matsuda towa
//
//=============================================
#include "board_holder_generator.h"
#include "field.h"
#include "game_manager.h"
#include "json.h"
#include "game.h"

//=============================================
//�|�C���^�[
//=============================================
namespace MyPointer
{
	My::CField* pField; //�t�B�[���h�̃|�C���^�[
}

//�����Ɋւ���l�[���X�y�[�X
namespace MyRandomBoard_Generator
{
	auto seed = chrono::system_clock::now().time_since_epoch().count(); //���ݎ������V�[�h�l�Ƃ��Ďg�p
	mt19937 gen((unsigned)seed);                                        // �����Z���k�E�c�C�X�^�[��32�r�b�g��
}

//=============================================
// �����̐�������
//=============================================
int My::CBoardHolderGenerator::Random(int Low, int Hight)
{
	uniform_int_distribution<> dist(Low, Hight);                        //�w�肳�ꂽ�͈͂̒l�����m���Ŕ�������悤���U���z����N���X�Őݒ�
	return dist(MyRandomBoard_Generator::gen);                          //������Ԃ�
}

//========================================
// �o�^
//========================================
void My::CBoardHolderGenerator::Regist(CBoardHolder* board_holder)
{
	//�o�^�ς݂�
	bool bRegisted = false;

	//�������̂����������m�F
	for (auto itr : m_pBoardHolderList)
	{
		if (itr == board_holder)
		{
			bRegisted = true;
			break;
		}
	}

	//�o�^����Ă���Ȃ甲����
	if (bRegisted)
	{
		return;
	}

	//�����̏���o�^
	m_pBoardHolderList.push_back(board_holder);
}

//========================================
// �폜
//========================================
void My::CBoardHolderGenerator::Delete(CBoardHolder* board_holder, D3DXVECTOR3 pos)
{
	//�T�C�Y��0�Ȃ甲����
	if (m_pBoardHolderList.size() == 0)
	{
		return;
	}

	//�o�^�ς݂�
	bool bRegisted = false;

	//�������̂����������m�F
	for (auto itr : m_pBoardHolderList)
	{
		if (itr == board_holder)
		{
			bRegisted = true;
			break;
		}
	}

	//�o�^����Ă��Ȃ��Ȃ甲����
	if (!bRegisted)
	{
		return;
	}

	//�����̏����폜
	m_pBoardHolderList.remove(board_holder);

	//�ۑ������ʒu�������i���������I�u�W�F�N�g�̈ʒu�j
	int size = m_savepos.size();

	for (int nCount = 0; nCount < size; nCount++)
	{
		if (size > 0)
		{
			//Y���ɏ����ȉ��̔�����ȈׁAX��Z���Ŕ���
			if (pos.x == m_savepos[nCount].x && pos.z == m_savepos[nCount].z)
			{
				m_savepos.erase(m_savepos.begin() + nCount);
				break;
			}
		}
	}
}

//=============================================
// ������
//=============================================
HRESULT My::CBoardHolderGenerator::Init()
{
	CGameManager::GetInstance()->SetGenerator(this);
	return S_OK;
}

//=============================================
// ����
//=============================================
void My::CBoardHolderGenerator::Generate()
{
	int UpperBoard = (int)(CJson::GetJson()->GetKarate(CJson::BOARDHOLDER_NUMBER)->GetUpperLimitNumber() * 0.7);     //��������̎擾
	int UpperKawara = (int)ceil(CJson::GetJson()->GetKarate(CJson::KAWARA_NUMBER)->GetUpperLimitNumber() * 0.1);     //���̏�����̎擾
	int UpperTrap = (int)ceil(CJson::GetJson()->GetKarate(CJson::TRAPHOLDER_NUMBER)->GetUpperLimitNumber() * 0.2);   //㩂̏�����̎擾
	int AllUpper = UpperBoard + UpperTrap + UpperKawara;                                                             //������̑���

	int AllCreateCount = 0;
	for (int i = 0; i < CJson::MAX_KARATEOBJ; ++i)
	{
		AllCreateCount += CJson::GetJson()->GetKarate(i)->GetcreateCount(); //�e���I�u�W�F�N�g�̕ۊǐ��̎擾
	}

	//���I�u�W�F�N�g�̐�(�����̏��Ԃ̊֌W�ネ�[�J��)
	int nBoardCount = AllUpper - AllCreateCount;

	//������������ɍs������
	if (m_num_holder >= UpperBoard && m_numTrap >= UpperTrap)
	{
		return;
	}

	D3DXVECTOR3 spawn_pos = VEC3_RESET_ZERO;

	//���̐�����
	for (int i = 0; i < nBoardCount; i++)
	{
		CField* pField = CGameManager::GetInstance()->GetField();

		MyPointer::pField = pField;

		My::CCamera* pCamera = GET_CAMERA(CGame::CAMERA_TYPE::BOARD_GENERATE_CAMERA);

		//HACK:�}�g���b�N�X�ɒl�������ĂȂ��Ƃ��ɖ������֐������p
		if (pCamera->GetPosR() == VEC3_RESET_ZERO)
		{
			return;
		}
		if (pCamera->GetPosV() == VEC3_RESET_ZERO)
		{
			return;
		}

		//�X�|�[���ʒu�Z�o
		GeneratePosCalculation(pField, spawn_pos);

		{
			D3DXVECTOR3 generate_pos;							//�����ʒu�p�ϐ�

			generate_pos = spawn_pos;

			//=======================================
			//�e���I�u�W�F�N�g�̐������� //MEMO �e���I�u�W�F�N�g�̏�������A���������{�������𑝂₷
			//========================================
			if (m_num_holder < UpperBoard)
			{//����
				CBoardHolder::Create(D3DXVECTOR3(generate_pos.x, 0.0f, generate_pos.z), new CBoardHolderInfo); //���������i�ʒu�𗐐��Ɠ����j
				++m_num_holder;

				m_savepos.push_back(generate_pos);
			}
			//else if (m_numKawara < UpperKawara)
			//{//��
			//	CKawaraInfo::Create(D3DXVECTOR3(generate_pos.x, 0.0f, generate_pos.z), new CKawaraInfo);      //��������
			//	++m_numKawara;

			//	m_savepos.push_back(generate_pos);
			//}
			else if (m_numTrap < UpperTrap)
			{//㩎���

				//�K��l��������񐔂����������� //MEMO ��A�Q�̏ꍇ�A������ɒB������
				if (CJson::GetJson()->GetKarate(CJson::TRAPHOLDER_NUMBER)->GetCount() >= 2)
				{
					CTrapHolderInfo::Create(D3DXVECTOR3(generate_pos.x, 0.0f, generate_pos.z), new CTrapHolderInfo);  //���������i�ʒu�𗐐��Ɠ����j
					++m_numTrap;

					m_savepos.push_back(generate_pos);
				}
			}
		}
	}

	////�����o������
	//if (m_boneflag == false)
	//{
	//	ManyCreate(MyPointer::pField);

	//	m_boneflag = true;
	//}
}

////========================================
//// �X�|�[���ʒu�Z�o
////========================================
//void My::CBoardHolderGenerator::GeneratePosCalculation(CField* pField, D3DXVECTOR3& spawn_pos)
//{
//	D3DXVECTOR3 field_size = pField->GetSize();
//
//	while (1)
//	{
//		float x = Rundom(0, SCREEN_WIDTH);
//		float y = Rundom(0, SCREEN_HEIGHT);
//		spawn_pos = ConvertToWorldPoint({ x,y,0.0f }, pField->GetPos());
//
//		if (spawn_pos.x > -field_size.x && spawn_pos.x < field_size.x
//			&& spawn_pos.z > -field_size.z && spawn_pos.z < field_size.z)
//		{
//			break;
//		}
//	}
//}

//========================================
// �X�|�[���ʒu�Z�o
//========================================
void My::CBoardHolderGenerator::GeneratePosCalculation(CField* pField, D3DXVECTOR3& spawn_pos)
{
	D3DXVECTOR3 field_size = pField->GetSize();

	//�����ʒu���t�B�[���h���Ɏ��܂��Ă��邩�̔���
	while (1)
	{
		//�⊮���������ʒu�ƍ��̐����ʒu�����Ԃ��Ă��邩�ǂ����̔���+�v���C���[�̈ʒu����
		while (1)
		{
			//�����ʒu�͈̔͏�������������Ă��邩�ǂ���
			if (RangePos(pField, spawn_pos, m_savepos) == true)
			{
				break;
			}
		}

		//�ŏI�`�F�b�N
		if (CretaePosCheck(field_size, spawn_pos) == true)
		{
			break;
		}

		spawn_pos = VEC3_RESET_ZERO;
	}
}

//========================================
// �����������鏈��(���̂�)
//========================================
bool My::CBoardHolderGenerator::ManyCreate(CField* pField)
{
	D3DXVECTOR3 field_size = pField->GetSize();                             //�t�B�[���h�̑傫��

	vector<D3DXVECTOR3>savepos;                                             //�����ʒu��⊮����p�ϐ�

	if (!m_boneflag)
	{
		m_boneflag = true;
		CGameManager::GetInstance()->GetPlayer()->SetPos(VEC3_RESET_ZERO);
		return false;
	}

	//���̐�����
	for (int nCount = 0; nCount < SP_CREATE_BOARDER_NUMBER; nCount++)
	{
		D3DXVECTOR3 spawn_pos = VEC3_RESET_ZERO;

		//�����ʒu���t�B�[���h���Ɏ��܂��Ă��邩�̔���
		while (1)
		{
			//�⊮���������ʒu�ƍ��̐����ʒu�����Ԃ��Ă��邩�ǂ����̔���+�v���C���[�̈ʒu����
			while (1)
			{
				//�����ʒu�͈̔͏�������������Ă��邩�ǂ���
				if (RangePos(pField, spawn_pos, savepos) == true)
				{
					break;
				}
			}

			//�ŏI�`�F�b�N
			if (CretaePosCheck(field_size, spawn_pos) == true)
			{
				break;
			}
		}

		CBoardHolder::Create(D3DXVECTOR3(spawn_pos.x, 0.0f, spawn_pos.z), new CBoardHolderInfo); //���������i�ʒu�𗐐��Ɠ����j
		++m_num_holder;

		savepos.push_back(spawn_pos);
	}

	savepos.clear(); //�O�̂��ߋ��

	return true;
}

//========================================
// �����ʒu�͈̔͌���
//========================================
bool My::CBoardHolderGenerator::RangePos(CField* pField, D3DXVECTOR3& spawn_pos, vector<D3DXVECTOR3>savepos)
{
	//NOTE: ��ʓ��M���M�������P����ɂ́A���_�O�i�E�[�A��[�j���痣���A�I�_���A�����Ƃ�����
	float x = Rundom(RANDOM_SCREEN_X, SCREEN_WIDTH - RANDOM_SCREEN_X);
	float y = Rundom(RANDOM_SCREEN_Y, SCREEN_HEIGHT - RANDOM_SCREEN_Y);

	//�v���C���[�͈̔͌��ߗp�ϐ�
	float fPlayerPosX = My::CGameManager::GetInstance()->GetPlayer()->GetPos().x; //�v���C���[��X�� 
	float fplayerPosZ = My::CGameManager::GetInstance()->GetPlayer()->GetPos().z; //�v���C���[��Z�� 

	spawn_pos = ConvertToWorldPoint(GET_CAMERA(CGame::BOARD_GENERATE_CAMERA), { x,y,0.0f }, pField->GetPos());

	int nsize = savepos.size();                                                   //�ۊǐ�

	//size������(�P�l��)
	if (nsize == 0)
	{
		//�v���C���[�͈͓̔�
		if (NotSpwan(spawn_pos, fPlayerPosX, fplayerPosZ) == true)
		{
			return false; 
		}
		return true;      
	}

	//���݂̕⊮���ꂽ�ʒu�̑���
	for (int nCount1 = 0; nCount1 < nsize; nCount1++)
	{
		//�����ʒu�̔���
		if (spawn_pos.x > savepos[nCount1].x + CREATE_X_POS || spawn_pos.x < savepos[nCount1].x - CREATE_X_POS ||
			spawn_pos.z > savepos[nCount1].z + CREATE_Z_POS || spawn_pos.z < savepos[nCount1].z - CREATE_Z_POS)
		{
			//�v���C���[�͈͓̔�
			if (NotSpwan(spawn_pos, fPlayerPosX, fplayerPosZ) == true)
			{
				break;
			}
		}
		else
		{
			break;       //�����ʒu�����łɐ������ꂽ�͈͓��t�߂ɂ��Ԃ遁���߂ł�
		}

		//�Ō�܂ŉ񂵂�
		if (nCount1 >= nsize - 1)
		{
			return true; //����
		}
	}

	return false;        //��������̏����ɓ��Ă͂܂�Ȃ�
}

//========================================
//���������Ȃ��͈͏���(�v���C���[)
//========================================
bool My::CBoardHolderGenerator::NotSpwan(D3DXVECTOR3& spawn_pos, float PlayerPosX, float PlayerPosZ)
{
	//�v���C���[�͈͔̔���
	if (spawn_pos.x > -NOT_SPAWN_PLAYER + PlayerPosX && spawn_pos.x < NOT_SPAWN_PLAYER + PlayerPosX &&
		spawn_pos.z > -NOT_SPAWN_PLAYER + PlayerPosZ && spawn_pos.z < NOT_SPAWN_PLAYER + PlayerPosZ)
	{
		return true;   //�v���C���[�͈͓̔�
	}

	return false;      //�v���C���[�͈̔͊O

}

//========================================
//�����ʒu�̍ŏI�`�F�b�N����
//========================================
bool My::CBoardHolderGenerator::CretaePosCheck(D3DXVECTOR3 field_size, D3DXVECTOR3& spawn_pos)
{
	//��ʓ�����
	if (spawn_pos.x > -field_size.x && spawn_pos.x < field_size.x
		&& spawn_pos.z > -field_size.z && spawn_pos.z < field_size.z)
	{
		return true;
	}

	return false;
}
