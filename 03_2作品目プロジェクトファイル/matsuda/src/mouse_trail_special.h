//=============================================
//
//�}�E�X�̋O��_�K�E�Z[mouse_trail_special.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _MOUSE_TRAIL_SPECIAL_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _MOUSE_TRAIL_SPECIAL_H_
#include "mouse_trail.h"

/** @brief My ���O��� */
namespace My
{
	/**
	 * @brief �}�E�X�̋O��_�ʏ�N���X
	 * @copydoc CMouseTrail
	 */
	class CMouseTrail_Special : public CMouseTrail
	{
	public:
		static const int SPECIAL_PRIORITY = 28;
		/**
		 * @brief �R���X�g���N�^
		 * @param �v���C�I���e�B
		 */
		CMouseTrail_Special(int nPriority = SPECIAL_PRIORITY);

		/**
		 * @brief �f�X�g���N�^
		 */
		~CMouseTrail_Special()override;

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