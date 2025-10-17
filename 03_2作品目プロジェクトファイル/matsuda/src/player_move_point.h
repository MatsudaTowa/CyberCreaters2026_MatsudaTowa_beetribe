//=============================================
//
//�v���C���[���ړ�����|�C���g[player_move_point.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _PLAYER_MOVE_POINT_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _PLAYER_MOVE_POINT_H_
#include "main.h"
#include "move_point.h"
#include "count.h"

/** @brief My ���O��� */
namespace My
{
	/**
	 * @brief �v���C���[���ړ�����|�C���g�N���X
	 * @copydoc CMovePoint
	 */
	class CPlayerMovePoint : public CMovePoint
	{
	public:
		static const int PRIORITY = 10;  //!<�`�揇

		/**
		 * @brief �R���X�g���N�^
		 * @param �v���C�I���e�B
		 */
		CPlayerMovePoint(int nPriority = PRIORITY) :CMovePoint(nPriority){};

		/**
		 * @brief �f�X�g���N�^
		 */
		~CPlayerMovePoint()override {};

		/**
		 * @brief ������
		 * @return ����������
		 */
		HRESULT Init()override;

		/**
		 * @brief �I��
		 */
		void Uninit()override;

		/**
		 * @brief �X�V
		 */
		void Update()override;

		/**
		 * @brief �`��
		 */
		void Draw()override;
	private:
	};
}

#endif