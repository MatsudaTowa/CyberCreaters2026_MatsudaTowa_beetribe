//=============================================
//
// �ł��uboard_hard.h�v
// Author���c�i�v
//
//=============================================
#ifndef _BOARD_HARD_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _BOARD_HARD_H_
#include "main.h"
#include "board.h"

/** @brief My ���O��� */
namespace My
{
	/**
	 * @brief �ł��N���X
	 * @copydoc CBoard
	 */
	class CBoardHard : public CBoard
	{
	public:

		/**
		 * @brief �R���X�g���N�^
		 * @param [in]�v���C�I���e�B
		 */
		CBoardHard(int nPriority = PRIORITY);

		/**
		 * @brief �f�X�g���N�^
		 */
		~CBoardHard()override;

		/**
		 * @brief �`��
		 */
		void Draw()override;
	private:
	};
}

#endif