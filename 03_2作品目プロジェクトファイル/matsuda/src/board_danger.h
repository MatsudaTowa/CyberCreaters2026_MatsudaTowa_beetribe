//=============================================
//
//�������Ⴂ���Ȃ��uboard_danger.h�v
// Author���c�i�v
//
//=============================================
#ifndef _BOARD_DANGER_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _BOARD_DANGER_H_
#include "main.h"
#include "board.h"

/** @brief My ���O��� */
namespace My
{
	/**
	 * @brief �������Ⴂ���Ȃ��N���X
	 * @copydoc CBoard
	 */
	class CBoardDanger : public CBoard
	{
	public:

		/**
		 * @brief �R���X�g���N�^
		 * @param [in]�v���C�I���e�B
		 */
		CBoardDanger(int nPriority = PRIORITY);

		/**
		 * @brief �f�X�g���N�^
		 */
		~CBoardDanger()override;

		/**
		 * @brief �`��
		 */
		void Draw()override;
	private:
	};
}

#endif