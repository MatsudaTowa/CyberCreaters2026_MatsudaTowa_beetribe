//=============================================
//
//��[belt.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _BELT_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _BELT_H_
#include "main.h"
#include "objectX.h"

namespace My
{
	//=============================================
	//�уN���X
	//=============================================
	class CBelt : public CObjectX
	{
	public:
		static const int PRIORITY = 11; //�`�揇

		//�т̐F
		enum LEVEL
		{
			WHITE = 0,
			YELLOW,
			ORANGE,
			BLUE,
			GREEN,
			PURPLE,
			BLOWN,
			BLACK,
			MAX
		};

		/**
		 * @brief �R���X�g���N�^
		 * @param [in]�v���C�I���e�B
		 */
		CBelt(int nPriority = PRIORITY);
		/**
		 * @brief �f�X�g���N�^
		 */
		~CBelt()override;
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
		 * @param [in]����
		 * @return �у|�C���^
		 */
		static CBelt* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

		/**
		 * @brief ���x���ݒ�
		 * @param [in]���x��
		 */
		void SetLevel(LEVEL level)
		{
			m_level = level;
		}
		
		/**
		 * @brief ���x���擾
		 * @return ���x��
		 */
		LEVEL GetLevel()
		{
			return m_level;
		}
	private:
		/**
		 * @brief ���x���ɍ��킹�ĐF�ύX
		 */
		void ColorLevel();
		LEVEL m_level;
	};
}

#endif