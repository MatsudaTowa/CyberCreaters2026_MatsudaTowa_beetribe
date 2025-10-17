//=============================================
//
//�A�^�b�N�|�C���g[hit_UI_break.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _HIT_UI_BREAK_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _HIT_UI_BREAK_H_
#include "main.h"
#include "hit_UI.h"

/** @brief My ���O��� */
namespace My
{
	/**
	 * @brief �q�b�gUI(����)�N���X
	 * @copydoc CObject2D
	 */
	class CHit_UI_Break : public CHit_UI
	{
	public:
		/**
		 * @brief �R���X�g���N�^
		 * @param �v���C�I���e�B
		 */
		CHit_UI_Break(int nPriority = PRIORITY);

		/**
		 * @brief �f�X�g���N�^
		 */
		~CHit_UI_Break()override;

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