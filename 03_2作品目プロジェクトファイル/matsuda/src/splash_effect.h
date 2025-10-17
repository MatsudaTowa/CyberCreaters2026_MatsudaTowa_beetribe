//=============================================
//
//�����Ԃ��G�t�F�N�g[flash_effect.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _SPLASH_EFFECT_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _SPLASH_EFFECT_H_
#include "main.h"
#include "billboard.h"
#include "count.h"

/** @brief My ���O��� */
namespace My
{
	/**
	 * @brief �����Ԃ�
	 * @copydoc CBillboard_Anim
	 */
	class CSplashEffect : public CBillboard
	{
	public:
		static const int PRIORITY = 21;		//!<�`�揇

		/**
		 * @brief �R���X�g���N�^
		 * @param �v���C�I���e�B
		 */
		CSplashEffect(int nPriority = PRIORITY);

		/**
		 * @brief �f�X�g���N�^
		 */
		~CSplashEffect()override;

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
		static CSplashEffect* Create(D3DXVECTOR3 pos);
	private:
		D3DXVECTOR3 m_move;
		CCount* m_pCnt;
	};
}

#endif