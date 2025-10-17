//=============================================
//
//����G�t�F�N�g[flash_effect.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _FLASH_EFFECT_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _FLASH_EFFECT_H_
#include "main.h"
#include "billboard.h"
#include "count.h"

/** @brief My ���O��� */
namespace My
{
	/**
	 * @brief ����
	 * @copydoc CBillboard_Anim
	 */
	class CFlashEffect : public CBillboard_Anim
	{
	public:
		static const int PRIORITY = 21;		//!<�`�揇

		/**
		 * @brief �R���X�g���N�^
		 * @param �v���C�I���e�B
		 */
		CFlashEffect(int nPriority = PRIORITY);

		/**
		 * @brief �f�X�g���N�^
		 */
		~CFlashEffect()override;

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
		 * @return �G�t�F�N�g�̃|�C���^
		 */
		static CFlashEffect* Create(D3DXVECTOR3 pos);
	private:
	};
}

#endif