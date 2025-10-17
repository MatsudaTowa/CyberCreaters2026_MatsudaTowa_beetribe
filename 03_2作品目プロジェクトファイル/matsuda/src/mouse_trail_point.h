//=============================================
//
//�}�E�X�̋O�Ղ�ݒu����|�C���g[mouse_trail_point.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _MOUSE_TRAIL_POINT_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _MOUSE_TRAIL_POINT_H_
#include "main.h"
#include "billboard.h"
#include "count.h"

/** @brief My ���O��� */
namespace My
{
	/**
	 * @brief �}�E�X�̋O�Ղ�ݒu����|�C���g�N���X
	 * @copydoc CBillboard
	 */
	class CMouseTrailPoint : public CBillboard
	{
	public:
		static const int PRIORITY = 25;  //!<�`�揇

		/**
		 * @brief �R���X�g���N�^
		 * @param �v���C�I���e�B
		 */
		CMouseTrailPoint(int nPriority = PRIORITY):CBillboard(nPriority) {};

		/**
		 * @brief �f�X�g���N�^
		 */
		~CMouseTrailPoint()override{};

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
		 * @return �}�E�X�̋O�Ղ̃|�C���^
		 */
		static CMouseTrailPoint* Create(D3DXVECTOR3 pos);

		/**
		 * @brief �O�Ր���
		 * @param [in]�ʒu
		 * @return �}�E�X�J�[�\���̃��[���h���W
		 */
		void CreateTrail();
	private:
	};
}

#endif