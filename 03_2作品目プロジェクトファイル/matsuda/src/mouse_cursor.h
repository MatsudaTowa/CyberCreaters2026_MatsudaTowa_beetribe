//=============================================
//
//�}�E�X�J�[�\��[mouse_cursor.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _MOUSE_CURSOR_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _MOUSE_CURSOR_H_
#include "main.h"
#include "object2D.h"
#include "count.h"
#include "mouse_trail_point.h"
#include "mouse_cursor_state.h"

/** @brief My ���O��� */
namespace My
{
	/**
	 * @brief �}�E�X�J�[�\���N���X
	 * @copydoc CObject2D
	 */
	class CMouseCursor : public CObject2D
	{
	public:
		static const std::string TEX_PATH;	//�t�@�C���p�X

		static const int PRIORITY = 29;  //!<�`�揇

		/**
		 * @brief �R���X�g���N�^
		 * @param �v���C�I���e�B
		 */
		CMouseCursor(int nPriority = PRIORITY);

		/**
		 * @brief �f�X�g���N�^
		 */
		~CMouseCursor()override;

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
		 * @param [in]�}�E�X�J�[�\���̃|�C���^
		 * @return �}�E�X�J�[�\���̃|�C���^
		 */
		static CMouseCursor* Create(CMouseCursor* mouse_cursor);

		/**
		 * @brief �ߋ��Ɉʒu�擾
		 * @return �ߋ��̈ʒu
		 */		
		inline D3DXVECTOR3 GetOldPos()
		{
			return m_oldpos;
		}
	private:
		D3DXVECTOR3 m_oldpos;									//!<�ߋ��̈ʒu
	};
}

#endif