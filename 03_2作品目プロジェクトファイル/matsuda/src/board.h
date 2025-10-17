//=============================================
//
//�uboard.h�v
// Author���c�i�v
//
//=============================================
#ifndef _BOARD_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _BOARD_H_
#include "main.h"
#include "objectX.h"
#include "model.h"

/** @brief My ���O��� */
namespace My
{
	/**
	 * @brief �N���X
	 * @copydoc CObjectX : TODO:����X
	 */
	class CBoard : public CModel_Parts
	{
	public:

		enum BOARD_TYPE
		{
			BOARD_NORMAL = 0,
			BOARD_HARD,
			BOARD_DANGER,
			BOARD_MAX,
		};

		static const int PRIORITY = 11; //!<�`�揇

		/**
		 * @brief �R���X�g���N�^
		 */
		CBoard(int nPriority = PRIORITY);

		/**
		 * @brief �f�X�g���N�^
		 */
		~CBoard()override;

		/**
		 * @brief �`��
		 */
		void Draw()override;


		/**
		 * @brief �`��
		 */
		void Draw(D3DXCOLOR col)override;

		/**
		 * @brief ����
		 * @param [in]�ʒu
		 * @param [in]�m�ۂ���̃|�C���^
		 * @return �{�[�h�̃|�C���^
		 */
		static CBoard* Create(D3DXVECTOR3 pos, CBoard* board);
	private:
		bool m_isDirection;
	};
}

#endif