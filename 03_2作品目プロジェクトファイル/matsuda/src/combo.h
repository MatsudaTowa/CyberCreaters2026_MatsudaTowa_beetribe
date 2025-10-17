//=============================================
//
//�R���{�\�������ucombo.h�v
// Author���c�i�v
//
//=============================================
#ifndef _COMBO_H_ //���ꂪ��`����ĂȂ��Ƃ�
#define _COMBO_H_
#include "main.h"
#include "object2D.h"
#include "number.h"
#include "count.h"

/** @brief My ���O��� */
namespace My
{
	/** @brief �R���{�N���X */
	class CCombo:public CObject2D
	{
	public:
		static const int PRIORITY = 28;
		CCombo(int nPriority = PRIORITY);
		~CCombo() override;
		HRESULT Init() override;
		void Uninit() override;
		void Update() override;
		void SubAlpha();
		void Draw() override;

		/**
		 * @brief �R���{���ݒ�
		 * @param [in]�R���{���ݒ�
		 */
		inline void SetNumCombo(int combo)
		{
			m_combo = combo;
		}

		/**
		 * @brief �R���{���擾
		 * @return �R���{��
		 */
		inline int GetNumCombo()
		{
			return m_combo;
		}

		/**
		 * @brief ����
		 * @param [in]�ʒu
		 * @return �R���{�̃|�C���^
		 */
		static CCombo* Create(D3DXVECTOR3 pos);

	private:
		/**
		 * @brief �R���{�ݒ�
		 */
		void SetCombo();
		/**
		 * @brief ���ǉ�
		 * @param [in]U���W
		 * @param [in]����
		 */
		void AddDigit(std::vector<int>& pos_texU, int& num_digit);
		CCount* m_pCnt;							//���t���[���o�������J�E���g����ϐ�
		D3DXVECTOR3 m_num_pos;					//�����̈ʒu
		int m_combo;							//�R���{��
		std::vector<CNumber_2D*> m_pNumber;		//����
	};
}

#endif // DEBUG