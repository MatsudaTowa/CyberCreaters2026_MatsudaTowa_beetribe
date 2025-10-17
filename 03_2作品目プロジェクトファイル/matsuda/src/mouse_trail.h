//=============================================
//
//�}�E�X�̋O��[mouse_trail.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _MOUSE_TRAIL_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _MOUSE_TRAIL_H_
#include "main.h"
#include "billboard.h"
#include "count.h"

/** @brief My ���O��� */
namespace My
{
	/**
	 * @brief �}�E�X�̋O�ՃN���X
	 * @copydoc CObject3D
	 */
	class CMouseTrail : public CBillboard
	{
	public:
		static const int PRIORITY = 10;		//!<�`�揇
		static const D3DXVECTOR3 POLY_SIZE;	//!<�|���S���T�C�Y
		static const D3DXCOLOR COLOR;		//!�F

		/**
		 * @brief �R���X�g���N�^
		 * @param �v���C�I���e�B
		 */		
		CMouseTrail(int nPriority = PRIORITY);

		/**
		 * @brief �f�X�g���N�^
		 */
		~CMouseTrail()override;

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

		/**
		 * @brief ����
		 * @param [in]�ʒu
		 * @param [in]�m�ۂ���O�Ղ̃|�C���^
		 * @return �}�E�X�̋O�Ղ̃|�C���^
		 */
		static CMouseTrail* Create(D3DXVECTOR3 pos,CMouseTrail* trail);
	private:
	};
}

#endif