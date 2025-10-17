//=============================================
//
//�^�C�}�[�����utimer.h�v
// Author���c�i�v
//
//=============================================
#ifndef _TIMER_H_ //���ꂪ��`����ĂȂ��Ƃ�
#define _TIMER_H_
#include "main.h"
#include "object2D.h"
#include "number.h"
#include "count.h"

/** @brief My ���O��� */
namespace My
{
	/** @brief �^�C�}�[�N���X */
	class CTimer
	{
	public:
		/**
		 * @brief �R���X�g���N�^
		 */
		CTimer();

		/**
		 * @brief �f�X�g���N�^
		 */
		~CTimer();

		/**
		 * @brief ������
		 * @return ����������
		 */
		HRESULT Init();

		/**
		 * @brief �I��
		 */
		void Uninit();

		/**
		 * @brief �X�V
		 */
		void Update();

		/**
		 * @brief �^�C�}�[�����炷����
		 */
		void DecreaseTime();

		/**
		 * @brief �^�C�}�[�b���擾
		 * @return ���݂̎���
		 */
		inline int GetCurrentTimer()
		{
			return m_nCurrentTime;
		}

		/**
		 * @brief �^�C�}�[�b���ݒ�
		 * @param [in]���݂̎���
		 */
		inline void SetCurrentTimer(int time)
		{
			m_nCurrentTime = time;
		}
	private:
		/**
		 * @brief �^�C�}�[���ݒ�
		 */
		void SetTimer();
		/**
		 * @brief ���폜
		 * @param [in]�e�N�X�`��U���W
		 * @param [in]����
		 */
		void EraseDigit(std::vector<int> pos_texU, int& num_digit);
		CCount* m_pCnt;							//���t���[���o�������J�E���g����ϐ�
		int m_nCurrentTime;						//���̎���
		D3DXVECTOR3 m_pos;						//�ʒu
		std::vector<CNumber_2D*> m_pNumber;		//����
	};
}

#endif // DEBUG