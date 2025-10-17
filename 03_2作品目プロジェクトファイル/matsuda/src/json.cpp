//===============================================================
//
// ���C�u����(test_text.cpp)
// Author : Haruki Chiba
//
//===============================================================

#include "json.h"
#include <fstream>
#include <cmath>
#include "game.h"

//random_device rd;             //���������G���W��
//default_random_engine  gen;   //�����W�F�l���[�^

My::CJson* My::CJson::m_pJson = nullptr;


//�t�@�C���Ɋւ�����
namespace MyFile
{
	//�G���[���b�Z�[�W�\��
	void ErrorMessage(const char* FileName) { cerr << "File open error: " << FileName << "\n"; }

	//�ǂݏ�����
	template <typename T, typename C = const char*>
	void Error(T& Writing_File, C Message)
	{
		//�t�@�C�����J���Ȃ���									              
		if (!Writing_File)
		{
			ErrorMessage(Message);                                      //�G���[���b�Z�[�W�\��
			quick_exit(0);                                              //�㏈���Ȃ��ŏI��
		}
	}
}

//���O��ԁi�e�L�X�g�ҁj
namespace My
{
	//=============================
	//�R���X�g���N�^
	//=============================
	CJson::CJson() : m_json{}
	{
		pKarateObject[0] = new CBoardObj();
		pKarateObject[1] = new CKawaraObj();
		pKarateObject[2] = new CTrapObj();
	}

	//=============================
	//�f�X�g���N�^
	//=============================
	CJson::~CJson()
	{
		for (int nCount = 0; nCount < MAX_KARATEOBJ; nCount++)
		{
			if (pKarateObject[nCount] != nullptr)
			{
				delete pKarateObject[nCount];
				pKarateObject[nCount] = nullptr;
			}
		}
	}

	//========================================
	//�W�F�C�\���t�@�C����ǂݍ��ޏ���(����)
	//========================================
	void CJson::JysonRandLoad()
	{
		string filename = CJsonName::jsonFileName;                            //�t�@�C���p�X��ݒ�

		//�t�@�C����ǂݍ���œ��e����ʂɕ\������			                  
		//�ǂݍ��݂Ɏ��s�����ꍇ�̓G���[��\������			                  
		ifstream ifs(filename.c_str());

		json json;                                                            //�W�F�C�\���f�[�^�i�[�p

		//��												               
		if (ifs.good())
		{
			//���[�v
			while (1)
			{
				//ifs>>�ŏ�񂪖������͉���catch�ɈȈڍs����
				try
				{
					ifs >> json;                                              //�ǂݍ��񂾃t�@�C�����Ɠ���������
				}
				//try���I������ڍs
				catch (const exception&)
				{
					break;
				}
			}

			DeleteJson();                                                     //�t�@�C�����̏����폜

			ifs.close();
		}
		else
		{
			MyFile::Error(ifs, CJsonName::jsonFileName);                      //�G���[����
		}
	}

	//========================================
	//�W�F�C�\���t�@�C���ɏ������ޏ���
	//========================================
	void CJson::JysonWrite()
	{
		//�쐬�����t�@�C���ɓ��e����������					                  
		ofstream writing_file;
		writing_file.open(CJsonName::jsonFileName, ios::out | ios::app);      //�t�@�C���ɒǉ���������

		//�t�@�C�����J���Ȃ���								                  
		MyFile::Error(writing_file, CJsonName::jsonFileName);

		writing_file << m_json.dump() << endl;                                //�f�[�^�\�����W�F�C�\���ɕϊ�+��������

		writing_file.close();
	}

	//========================================
	//�W�F�C�\���t�@�C���ɏ������ޏ���(���폜)
	//========================================
	void CJson::DeleteJson()
	{
		//�쐬�����t�@�C���ɓ��e����������					                  
		ofstream writing_file;
		writing_file.open(CJsonName::jsonFileName, ios::out);                 //�t�@�C���ɏ�������

		//�t�@�C�����J���Ȃ���									              
		MyFile::Error(writing_file, CJsonName::jsonFileName);

		writing_file << endl;                                                 //������������

		writing_file.close();
	}

	//========================================
	//�W�F�C�\�����̐ݒ�
	//========================================
	void CJson::SetJson()
	{
		m_json[CJsonName::TYPE] = 0;  //��ނ̐ݒ�
		JysonWrite();                 //�t�@�C���ɏ�������
	}


	//==================================================================================================================================
	//���I�u�W�F�N�g�̏��̃N���X����
	//==================================================================================================================================
	void CKarateObject::Createobj()
	{
		//���I�u�W�F�N�g���j�����ꂽ�� //TODO �����ǉ�����ƃW�F�l���[�^�����́A��������Â����̎擾�ɂȂ��Ă��܂�
		//if (m_nkarateObjCount >= 1)

		UpperLimitRatio();
	}

	//==================================
	//��������犄�����o������
	//==================================
	void CKarateObject::UpperLimitRatio()
	{
		int nUpper = m_nupperLimitNumber-4;                                               //�Q�[�W�̋K��l�̍ő吔

		//�Q�[�W���K��l�ȏ�ɒB������							         
		if (m_ngage >= nUpper)
		{
			//��������K��l��菬��������������̍ő�l���K��l�ɂȂ�
			if (m_nupperLimitNumber < 20)
			{
				//�e��ނ̊������o���B
				m_nupperLimitNumber = m_nupperLimitNumber += UPPER_LIMIT_NUMBER_PLUS;  //������̈����グ

				m_ncount++; //�J�E���g��i�߂�
			}

			m_nkarateObjCount = (int)(m_nupperLimitNumber)-m_ncreateCount;             //�������Ratio���蕪�[���ݐ�������Ă��鐔=������������

			m_ngage = 0;                                                               //�Q�[�W���Z�b�g
		}
	}
}