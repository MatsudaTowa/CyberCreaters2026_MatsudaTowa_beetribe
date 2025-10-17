//=============================================
//
//�}�E�X�̋O��_�ʏ�[mouse_trail_normal.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _MOUSE_TRAIL_NORMAL_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _MOUSE_TRAIL_NORMAL_H_
#include "mouse_trail.h"

/** @brief My ���O��� */
namespace My
{
	/**
	 * @brief �}�E�X�̋O��_�ʏ�N���X
	 * @copydoc CMouseTrail
	 */
	class CMouseTrail_Normal : public CMouseTrail
	{
	public:
		/**
		 * @brief �R���X�g���N�^
		 * @param �v���C�I���e�B
		 */
		CMouseTrail_Normal(int nPriority = PRIORITY);

		/**
		 * @brief �f�X�g���N�^
		 */
		~CMouseTrail_Normal()override;

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
		CCount* m_pCnt;
	};
}

#endif