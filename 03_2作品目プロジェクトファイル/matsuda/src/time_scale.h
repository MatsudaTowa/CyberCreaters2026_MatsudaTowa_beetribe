//=============================================
//
//���ԊǗ�[time_scale.h]
//Author Kasai Keisuke
//
//=============================================
#ifndef _TIME_SCALE_H_	//���ꂪ��`����Ă��Ȃ��Ƃ�

#define _TIME_SCALE_H_

/** @brief My ���O��� */
namespace My
{
	/** @brief ���ԊǗ��N���X */
	class CTimeScale
	{
	public:
		/**
		 * @brief �R���X�g���N�^
		 * @param [in]�^�C���X�P�[��
		 */
		CTimeScale(float timeScale = 1.0f);

		/**
		 * @brief ����������
		 * @return �����������ǂ���
		 */
		HRESULT Init();

		/**
		 * @brief �^�C���X�P�[���ݒ�
		 * @param [in]�^�C���X�P�[��
		 */
		void SetTimeScale(float timescale);

		/**
		* @brief �^�C���X�P�[���擾
		*/
		float GetTimeScale()const { return m_TimeScale; }

		operator float()const { return m_TimeScale; };


	private:
		float m_TimeScale;	//!<�^�C���X�P�[��
	};
}

#endif