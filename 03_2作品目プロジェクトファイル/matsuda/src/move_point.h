//=============================================
//
//�ړ�����|�C���g[move_point.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _MOVE_POINT_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _MOVE_POINT_H_
#include "main.h"
#include "billboard.h"

/** @brief My ���O��� */
namespace My
{
	/**
	 * @brief �ړ�����|�C���g�N���X
	 * @copydoc CBillboard
	 */
	class CMovePoint : public CBillboard
	{
	public:
		static const int PRIORITY = 10;  //!<�`�揇

		/**
		 * @brief �R���X�g���N�^
		 * @param �v���C�I���e�B
		 */
		CMovePoint(int nPriority = PRIORITY) :CBillboard(nPriority) {};

		/**
		 * @brief �f�X�g���N�^
		 */
		~CMovePoint()override {};

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
		 * @param [in]�|�C���g
		 * @return �ړ�����|�C���g
		 */
		static CMovePoint* Create(D3DXVECTOR3 pos,CMovePoint* point);
	private:
	};
}

#endif