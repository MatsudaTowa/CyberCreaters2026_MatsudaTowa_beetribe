//=============================================
//
//�q�b�gUI[hit_UI.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _HIT_UI_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _HIT_UI_H_
#include "main.h"
#include "object2D.h"

/** @brief My ���O��� */
namespace My
{
	/**
	 * @brief �q�b�g����UI�N���X
	 * @copydoc CObject2D
	 */
	class CHit_UI : public CObject2D
	{
	public:
		static const int PRIORITY = 25;  //!<�`�揇

		enum POINT_TYPE
		{
			BREAK = 0,
			STUN,
			MAX,
		};

		/**
		 * @brief �R���X�g���N�^
		 * @param �v���C�I���e�B
		 */
		CHit_UI(int nPriority = PRIORITY);

		/**
		 * @brief �f�X�g���N�^
		 */
		~CHit_UI()override;

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
		 * @param [in]�^�C�v
		 * @return �A�^�b�N�|�C���g�|�C���^
		 */
		static CHit_UI* Create(D3DXVECTOR3 pos, int type);
	private:
	};
}

#endif