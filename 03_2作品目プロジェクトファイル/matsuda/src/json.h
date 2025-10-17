//===============================================================
//
// ���C�u����(test_text.h)
// Author : Haruki Chiba
//
//===============================================================

#pragma once

#include "json.hpp"
#include <functional>
#include <vector>

//using�錾
using json = nlohmann::json;  //�W�F�C�\���̎g�p�\�錾
using namespace std;          //std�ȗ�

////===================================
//	//������̐ݒ�
//string u8FieldText = u8"��i"; //���{��Ή�


/** @brief My TextLibrary */
namespace My
{
	//==========================================
	//���I�u�W�F�N�g�̊��N���X
	class CKarateObject
	{
	public:

		//���
		enum class Type
		{
			board = 0,                             //��
			kawara,                                //��
			trap                                   //�
		};

		/**
		* @brief �R���X�g���N�^
		*/
		CKarateObject() : m_ngage(0), m_nupperLimitNumber(UPPER_LIMIT_NUMBER), m_ncount(0),
			m_nkarateObjCount(0), m_ncreateCount(0)
		{

		}

		/**
		* @brief �f�X�g���N�^
		*/
		virtual ~CKarateObject()
		{
			
		}

		/**
		* @brief �^�C�v�ʐ�������
		*/
		virtual void Createobj();

		/**
	   * @brief ��������犄�����o���֐�
	   */
		void UpperLimitRatio();

		/**
		* @brief �I�u�W�F�N�g���𑝂₷�֐�
		*/
		void PlusCreateobjCount()
		{
			m_ncreateCount++;
		}

		/**
		* @brief �J�E���g�𒲐�����֐�
		*/
		inline void AdjsutobjCount()
		{
			m_nkarateObjCount++;
			m_ncreateCount--;
		}

		/**
		* @brief �����ۊǐ����擾
		*/
		inline int& GetcreateCount() { return m_ncreateCount; }

		/**
		* @brief ���g�̃I�u�W�F�N�g�̃J�E���g���̐ݒ�
		* @param[in]�����l
		*/
		inline void SetKarateObjCount(int nkarateobjectCount) { m_nkarateObjCount = nkarateobjectCount; }

		/**
		* @brief �Q�[�W�̒l�̐ݒ�
		* @param[in]�����l
		*/
		inline void SetGage(int ngage) { m_ngage = ngage; }

		/**
		* @brief �Q�[�W�̒l�̎擾
		*/
		inline int& GetGage() { return m_ngage; }

		/**
		* @brief ������̎擾
		*/
		inline int& GetUpperLimitNumber() { return m_nupperLimitNumber; }

		int& GetCount() { return m_ncount; }


	protected:
		//=================================
		//�}�N����`
		static constexpr int LOWESTNUMBER = 1;            //�Œ�l
		static constexpr int RECAST_TIME = 120;           //���L���X�g�^�C���̍ő吔
		static constexpr int UPPER_LIMIT_NUMBER = 5;      //�����
		static constexpr int UPPER_LIMIT_NUMBER_PLUS = 5; //������̉��Z�l
		static constexpr int INIT_BOARDCOUNT = 3;         //���̏�����
		static constexpr int INIT_KAWARACOUNT = 1;        //�����̏�����
		static constexpr int INIT_TRAPCOUNT = 1;          //㩂̏�����

	private:
		int m_nkarateObjCount;                            //���̐�   (����ꂽ��)
		int m_ncreateCount;                               //�������ꂽ�̐�
		int m_ngage;                                      //���Q�[
		int m_nupperLimitNumber;                          //�����

		//NOTE �Ⴆ��,>=2�̎������������ĂԂȂǂ̎g����
		int m_ncount;                                     //�J�E���g���Ő������邩���߂�悤
	};

	//==========================================
	//���̏��N���X
	class CBoardObj : public CKarateObject
	{
	public:
		/**
		* @brief �R���X�g���N�^
		*/
		CBoardObj()
		{
			SetKarateObjCount(INIT_BOARDCOUNT);                 //�I�u�W�F�N�g���̐ݒ�
			//PshuObjRecastTime(INIT_BOARDCOUNT, RECAST_TIME);  //���L���X�g�^�C���̐ݒ�
		}

		/**
		* @brief �f�X�g���N�^
		*/
		~CBoardObj()override
		{

		}

		/**
		* @brief �^�C�v�ʐ�������
		*/
		void Createobj()override
		{
			CKarateObject::Createobj();
		}

	private:
	};

	//==========================================
	//���̏��N���X
	class CKawaraObj :public CKarateObject
	{
	public:
		/**
		* @brief �R���X�g���N�^
		*/
		CKawaraObj()
		{
			SetKarateObjCount(INIT_KAWARACOUNT);               //�I�u�W�F�N�g���̐ݒ�
		}

		/**
		* @brief �f�X�g���N�^
		*/
		~CKawaraObj()override
		{

		}

		/**
		* @brief �^�C�v�ʐ�������
		*/
		void Createobj()override
		{
			CKarateObject::Createobj();
		}

	private:
	};

	//==========================================
	//㩂̏��N���X
	class CTrapObj :public CKarateObject
	{
	public:
		/**
		* @brief �R���X�g���N�^
		*/
		CTrapObj()
		{
			SetKarateObjCount(INIT_TRAPCOUNT);               //�I�u�W�F�N�g���̐ݒ�
		}

		/**
		* @brief �f�X�g���N�^
		*/
		~CTrapObj()override
		{

		}

		/**
		* @brief �^�C�v�ʐ�������
		*/
		void Createobj()override
		{
			CKarateObject::Createobj();
		}
	private:
	};

	//==========================================
	//�W�F�C�\���N���X
	class CJson
	{
	public:
		/**
		* @brief ���g�̃|�C���^�[
		*/
		static CJson*& GetJson() { return m_pJson; }

		/**
		* @brief ���I�u�W�F�N�g�̎擾
		* * @param [in]�ԍ�(0=��,1=��,2=�)
		*/
		inline CKarateObject* GetKarate(int idx) { return pKarateObject[idx]; }

		/**
		* @brief �R���X�g���N�^
		*/
		CJson();

		/**
		* @brief �f�X�g���N�^
		*/
		~CJson();

		/**
		* @brief �I������
		*/
		void Uninit()
		{
			delete m_pJson;
			m_pJson = nullptr;
		}

		/**
		* @brief ��������
		*/
		void Create()
		{
			m_pJson = new CJson();
		}

		/**
		* @brief �W�F�C�\���t�@�C���̓ǂݍ��݁i�ʒu�𗐐��Œ����j
		* @param [in] X���̈ʒu
		*/
		void JysonRandLoad();

		/**
		* @brief �W�F�C�\���t�@�C���̏�������
		* @param
		*/
		void JysonWrite();

		/**
		* @brief �W�F�C�\���t�@�C���̒��g�̏��폜
		* @param
		*/
		void DeleteJson();

		/**
		* @brief �W�F�C�\���t�@�C���̏�������(���ݒ�)
		* @param [in]���
		*/
		void SetJson();

		//=======================
		//�}�N����`				      
		static constexpr int RANDRANGE = 200;      //�����l�͈̔�(+-�̒l)
		static constexpr int NOTSPOWN = 80;        //�X�|�[�����Ȃ��͈�
		static constexpr int MAX_KARATEOBJ = 3;    //���I�u�W�F�N�g�̑���

		//=======================
		//�e���I�u�W�F�N�g�̔ԍ��i�z��ԍ��j
		static constexpr int BOARDHOLDER_NUMBER = 0;
		static constexpr int KAWARA_NUMBER = 1;
		static constexpr int TRAPHOLDER_NUMBER = 2;

	private:

		//�p�X�p�N���X
		class CJsonName
		{
		public:
			static constexpr auto POS = "POS";                                   //�ʒu
			static constexpr auto TYPE = "TYPE";                                 //���

			static constexpr auto  jsonFileName = "data\\json\\file.json";       //�W�F�C�\���t�@�C���p�X
		};

		//�����A���E�̔��ʁA�i�̔���,���x,����\������
		json m_json =
		{
			{CJsonName::POS,{0.0f,0.0f,0.0f}},     //�ʒu
			{CJsonName::TYPE,-1},                  //���
		};

		//======================
		//�|�C���^�[
		CKarateObject* pKarateObject[MAX_KARATEOBJ];
		static  CJson* m_pJson;
	};
}