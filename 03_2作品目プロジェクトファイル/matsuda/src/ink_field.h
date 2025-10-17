//=============================================
//
//�n�̔�юU��[ink_field.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _INK_FIELD_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _INK_FIELD_H_
#include "main.h"
#include "object3D.h"

/** @brief My ���O��� */
namespace My
{
	/**
	 * @brief �n�̔�юU��N���X
	 * @copydoc CObject3D
	 */
	class CInkField : public CObject3D
	{
	public:

		static const int FIELD_PRIORITY = 21; //!<�`�揇

		/**
		 * @brief �R���X�g���N�^
		 * @param [in]�v���C�I���e�B
		 */
		CInkField(int nPriority = FIELD_PRIORITY);

		/**
		 * @brief �f�X�g���N�^
		 */
		~CInkField()override;

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
		 * @brief �C���N�̐Ր���
		 * @param [in]�����ʒu
		 * @return �C���N�̐Ղ̃|�C���^
		 */
		static CInkField* Create(D3DXVECTOR3 pos);
	private:
	};
}

#endif