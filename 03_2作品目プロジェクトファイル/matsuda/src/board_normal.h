//=============================================
//
//�ʏ�̔uboard_normal.h�v
// Author���c�i�v
//
//=============================================
#ifndef _BOARD_NORMAL_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _BOARD_NORMAL_H_
#include "main.h"
#include "board.h"

/** @brief My ���O��� */
namespace My
{
	/**
	 * @brief �ʏ�̔N���X
	 * @copydoc CBoard
	 */
	class CBoardNormal : public CBoard
	{
	public:

		/**
		 * @brief �R���X�g���N�^
		 * @param [in]�v���C�I���e�B
		 */
		CBoardNormal(int nPriority = PRIORITY);

		/**
		 * @brief �f�X�g���N�^
		 */
		~CBoardNormal()override;

		/**
		 * @brief �`��
		 */
		void Draw()override;
	private:
	};
}

#endif