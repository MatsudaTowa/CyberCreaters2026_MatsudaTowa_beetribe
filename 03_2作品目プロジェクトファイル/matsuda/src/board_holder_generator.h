//=============================================
//
//��������[board_holder_generator.h]
//Auther matsuda towa
//
//=============================================

#ifndef _BOARD_HOLDER_GENERATOR_H_
#define _BOARD_HOLDER_GENERATOR_H_

#include "board_holder.h"
#include "field.h"

#include <vector>
using namespace std;

/** @brief My ���O��� */
namespace My
{
	/**
	 * @brief ���������N���X
	 */
	class CBoardHolderGenerator
	{
	public:
		static const int NUM_GENERATE_POINT = 4;

		/**
		 * @brief �R���X�g���N�^
		 */
		CBoardHolderGenerator() :m_num_holder(0), m_numTrap(0), m_numKawara(0){ m_savepos.clear(); m_pBoardHolderList.clear(); }

		/**
		 * @brief �f�X�g���N�^
		 */
		virtual ~CBoardHolderGenerator()
		{
			m_num_holder = 0;
			m_numKawara = 0;
			m_numTrap = 0;
			m_pBoardHolderList.clear();
			m_savepos.clear();
		};

		/**
		 * @brief ������
		 * @return ����������
		 */
		HRESULT Init();

		/**
		 * @brief ����
		 */
		void Generate();

		/**
		 * @brief �X�|�[���ʒu�Z�o
		 * @param [in]���̃|�C���^
		 * @param [in][out]�X�|�[���ʒu
		 */
		void GeneratePosCalculation(CField* pField, D3DXVECTOR3& spawn_pos);

		/**
		 * @brief ��������(�K�E�p) bool�^
		 * @param [in]���̃|�C���^
		 */
		bool ManyCreate(CField* pField);

		/**
		 * @brief �����ʒu�͈̔͌��� bool�^
		 * @param [in]���̃|�C���^,�����ʒu,�ۊǈʒu
		 */
		bool RangePos(CField* pField, D3DXVECTOR3& spawn_pos, vector<D3DXVECTOR3>savepos);

		/**
		 * @brief���������Ȃ������i�v���C���[�j bool�^
		 * @param [in]�����ʒu,�v���C���[��X��,�v���C���[��Z��
		 */
		bool NotSpwan(D3DXVECTOR3& spawn_pos, float PlayerPosX, float PlayerPosZ);

		/**
		 * @brief�����ʒu�̍ŏI�`�F�b�N���� bool�^
		 * @param [in]���̃|�C���^,�����ʒu,�ۊǈʒu
		 */
		bool CretaePosCheck(D3DXVECTOR3 field_size, D3DXVECTOR3& spawn_pos);

		/**
		 * @brief ��������
		 */
		int Random(int Low, int Hight);

		/**
		 * @brief ����
		 */
		void SubHolder()
		{
			if (0 >= m_num_holder)
			{
				return;
			}

			--m_num_holder;
		}

		/**
		 * @brief ����
		 */
		void SubKawara()
		{
			if (0 >= m_numKawara)
			{
				return;
			}

			--m_numKawara;
		}

		/**
		 * @brief ����
		 */
		void SubTrap()
		{
			if (0 >= m_numTrap)
			{
				return;
			}

			--m_numTrap;
		}

		/**
		 * @brief �����̐��擾
		 * @return �����̐�
		 */
		inline int GetNumHolder()
		{
			return m_num_holder;
		}

		/**
		 * @brief �����̐��擾
		 * @return �����̐�
		 */
		inline int GetNumkawara()
		{
			return m_numKawara;
		}

		/**
		 * @brief �����̐��擾
		 * @return �����̐�
		 */
		inline int GetNumTrap()
		{
			return m_numTrap;
		}

		/**
		 * @brief �o�^
		 * @param [in]����
		 */
		void Regist(CBoardHolder* board_holder);

		/**
		 * @brief �폜
		 * @param [in]����
		 */
		void Delete(CBoardHolder* board_holder, D3DXVECTOR3 pos);

		std::list<CBoardHolder*> GetBoardHolderList()
		{
			return m_pBoardHolderList;
		}

	private:
		int m_num_holder;	//!���̂��邩
		int m_numKawara;	//����
		int m_numTrap;		//㩎����̐�

		D3DXVECTOR3 m_generate_point[NUM_GENERATE_POINT];
		std::list<CBoardHolder*> m_pBoardHolderList;

		vector<D3DXVECTOR3>m_savepos;  //�ʒu��ۑ�����ׂ̕ϐ�

		bool m_boneflag = false;       //�K�E�p�����t���O�idebug�p�j

		//===========================
		//�}�N����`
		static constexpr float CREATE_X_POS = 50.0f;             //�w���̐����ʒu�͈̔�
		static constexpr float CREATE_Z_POS = 50.0f;             //�y���̐����ʒu�͈̔�

		static constexpr int SP_CREATE_BOARDER_NUMBER = 50;      //�K�E�Z���̔��̐�����
		static constexpr float NOT_SPAWN_PLAYER = 80.0f;         //�v���C���[�̐����ʒu����Ȃ��͈�

		//�����p
		static constexpr int RANDOM_SCREEN_X = 120;
		static constexpr int RANDOM_SCREEN_Y = 80;
	};
}

#endif