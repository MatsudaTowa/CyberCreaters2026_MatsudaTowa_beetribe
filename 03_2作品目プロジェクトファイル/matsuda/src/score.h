//=============================================
//
//�X�R�A�����uscore.h�v
// Author���c�i�v
//
//=============================================
#ifndef _SCORE_H_ //���ꂪ��`����ĂȂ��Ƃ�
#define _SCORE_H_
#include "main.h"
#include "object2D.h"
#include "number.h"
#include "count.h"

/** @brief My ���O��� */
namespace My
{
	/** @brief �X�R�A�N���X */
	class CScore
	{
	public:
		static const int MAX_SCORE = 100;	//TODO: �Ƃ肠�������̐��ȏ�|�����獕�тɂ��܂�

		CScore();
		~CScore();
		HRESULT Init();
		void Uninit();
		void Update();

		/**
		 * @brief �X�R�A�擾
		 * @return ���݂̃X�R�A
		 */
		inline int GetCurrentScore()
		{
			return m_current_score;
		}

		/**
		 * @brief �X�R�A�ݒ�
		 * @param [in]���݂̃X�R�A
		 */
		inline void SetCurrentScore(int score)
		{
			m_current_score = score;
		}
	private:
		int m_current_score;					//���̃X�R�A
	};
}

#endif // DEBUG