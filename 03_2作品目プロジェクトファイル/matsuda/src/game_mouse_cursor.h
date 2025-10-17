//=============================================
//
//�Q�[���}�E�X�J�[�\��[game_mouse_cursor.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _GAME_MOUSE_CURSOR_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _GAME_MOUSE_CURSOR_H_
#include "main.h"
#include "mouse_cursor.h"
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
	class CGameMouseCursor : public CMouseCursor
	{
	public:
		static const std::string WRITE_TEX_PATH;						//�`���Ă鎞�̃e�N�X�`��
		static const int SPLIT = 6;	//�e�N�X�`��������

		/**
		 * @brief �R���X�g���N�^
		 * @param �v���C�I���e�B
		 */
		CGameMouseCursor(int nPriority = PRIORITY);

		/**
		 * @brief �f�X�g���N�^
		 */
		~CGameMouseCursor()override;

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
		 * @brief �X�e�[�g�ύX
		 * @param [in]���̃X�e�[�g
		 */
		void ChangeState(CMouseCursorState* state);

		/**
		 * @brief �O�Ղ̃|�C���g��ݒ�
		 * @param [in]�O�Ղ̃|�C���^
		 */
		inline void SetTrailPoint(CMouseTrailPoint* point)
		{
			m_pMouse_Trail_Point.push_back(point);
		}

		/**
		 * @brief �O�Ղ̃|�C���g���폜
		 */
		inline void EraseTrailPoint()
		{
			m_pMouse_Trail_Point.erase(m_pMouse_Trail_Point.begin());
		}

		/**
		 * @brief �O�Ղ̃|�C���g�̃T�C�Y�擾
		 * @return �T�C�Y��
		 */
		inline int GetTrailPointSize()
		{
			return m_pMouse_Trail_Point.size();
		}

		/**
		 * @brief ��Ԏ擾�擾
		 * @return ���
		 */
		inline CMouseCursorState* GetState()
		{
			return m_pState;
		}

		/**
		 * @brief �O�Ղ̃|�C���g�擾
		 * @param [in]�ԍ�
		 * @return �O�Ղ̃|�C���g
		 */
		inline CMouseTrailPoint* GetTrailPoint(unsigned int idx)
		{
			if (idx >= m_pMouse_Trail_Point.size())
			{
				return nullptr;
			}
			return m_pMouse_Trail_Point[idx];
		}

		/**
		 * @brief �w�肳�ꂽ�O�Ղ̃|�C���g���폜
		 * @param [in]�ԍ�
		 */
		inline void EraseTrailPoint(unsigned int idx)
		{
			if (idx >= m_pMouse_Trail_Point.size())
			{
				return;
			}
			CMouseTrailPoint* point = m_pMouse_Trail_Point[idx];
			point->Uninit();

			m_pMouse_Trail_Point.erase(m_pMouse_Trail_Point.begin() + idx);
		}

		/**
		 * @brief �S�Ă̋O�Ղ̃|�C���g���폜
		 */
		inline void ClearTrailPoint()
		{
			for (auto& itr : m_pMouse_Trail_Point)
			{
				if (itr == nullptr) { continue; }
				itr->Uninit();
				itr = nullptr;
			}
			m_pMouse_Trail_Point.clear();
		}

		/**
		 * @brief 
		 * @param [in]idx
		 */
		void SetTexIdx(int idx)
		{
			if (idx > SPLIT)
			{
				return;
			}
			m_tex_idx = idx;

			m_min_tex_x = (1.0f / (float)SPLIT) * (m_tex_idx - 1);
			m_max_tex_x = (1.0f / (float)SPLIT) * m_tex_idx;
		}
	private:
		std::vector<CMouseTrailPoint*> m_pMouse_Trail_Point;	//!<�O�Ղ�\������|�C���g
		CMouseCursorState* m_pState;
		float m_min_tex_x;
		float m_max_tex_x;

		int m_tex_idx;

		/**
		 * @brief �e�N�X�`�����W�ݒ�
		 */
		void SetTexPos();
		/**
		 * @brief �f�o�b�O�\��
		 */
		void DebugDraw();
	};
}

#endif