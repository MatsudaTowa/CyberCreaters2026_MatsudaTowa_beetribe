//=============================================
//
//�K�E�Z���ɏ�����[paper.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _PAPER_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _PAPER_H_
#include "main.h"
#include "object2D.h"

/** @brief My ���O��� */
namespace My
{
	/**
	 * @brief ���N���X
	 * @copydoc CObject2D
	 */
	class CPaper : public CObject2D
	{
	public:
		static const int PRIORITY = 27;  //!<�`�揇

		/**
		 * @brief �R���X�g���N�^
		 * @param [in]�v���C�I���e�B
		 */
		CPaper(int nPriority = PRIORITY);

		/**
		 * @brief �f�X�g���N�^
		 */
		~CPaper()override;

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
		 * @brief ���̐���
		 * @param [in]�����ʒu
		 * @return ���̃|�C���^
		 */
		static CPaper* Create(D3DXVECTOR3 pos);
	private:
	};
}

#endif