//=============================================
//
//�}�E�X�J�[�\���̃X�e�[�g�p�^�[��[mouse_cursor_state.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _MOUSE_CURSOR_STATE_H_
#define _MOUSE_CURSOR_STATE_H_
#include "count.h"
#include "mouse_trail.h"

/** @brief My ���O��� */
namespace My
{
	//=============================================
	//�O���錾
	//=============================================
	class CGameMouseCursor;

	/** @brief �}�E�X�J�[�\���X�e�[�g�N���X */
	class CMouseCursorState
	{
	public:
		CMouseCursorState() {};
		virtual~CMouseCursorState() {};
		/**
		* @brief �ʏ폈��(�e�ł͉������Ȃ�)
		* @param [in]�}�E�X�J�[�\���̃|�C���^
		*/
		virtual void Normal([[maybe_unused]] CGameMouseCursor* mouse) {};

		/**
		* @brief �`��(�e�ł͉������Ȃ�)
		* @param [in]�}�E�X�J�[�\���̃|�C���^
		*/
		virtual void Write([[maybe_unused]] CGameMouseCursor* mouse) {};

		/**
		* @brief �`���I�����(�e�ł͉������Ȃ�)
		* @param [in]�}�E�X�J�[�\���̃|�C���^
		*/
		virtual void Written([[maybe_unused]] CGameMouseCursor* mouse) {};

		/**
		* @brief �|�[�Y(�e�ł͉������Ȃ�)
		* @param [in]�}�E�X�J�[�\���̃|�C���^
		*/
		virtual void Pause([[maybe_unused]] CGameMouseCursor* mouse) {};
	};

	/** @brief �ʏ��ԃN���X */
	class CNormalCursol : public CMouseCursorState
	{
	public:
		/**
		* @brief �R���X�g���N�^
		*/
		CNormalCursol();

		/**
		* @brief �f�X�g���N�^
		*/
		~CNormalCursol() override;		

		/**
		* @brief �ʏ폈��
		* @param [in]�}�E�X�J�[�\���|�C���^
		*/
		virtual void Normal(CGameMouseCursor* mouse)override;
	private:
	};

	/** @brief �`���Ă��ԃN���X */
	class CWriteCursol : public CMouseCursorState
	{
	public:
		/**
		* @brief �R���X�g���N�^
		*/		
		CWriteCursol();

		/**
		* @brief �f�X�g���N�^
		*/		
		~CWriteCursol() override;

		/**
		* @brief �`��
		* @param [in]�}�E�X�J�[�\���̃|�C���^
		*/
		virtual void Write(CGameMouseCursor* mouse) override;

		/**
		 * @brief �J�[�\���̋O�Ր���
		 * @param [in]�}�E�X�J�[�\���̃|�C���^
		 */
		virtual void CreateTrailPos(CGameMouseCursor* mouse) = 0;

		/**
		 * @brief ���`��Ԃ��r�؂�Ȃ��悤�ɐ���
		 * @param [in][out]�O�Ղ̈ʒu
		 */
		virtual void GenerateInterpolatedPos(CGameMouseCursor* mouse, D3DXVECTOR3& trail_pos) = 0;

		/**
		 * @brief ���݂̃C���N�̗ʎ擾
		 * @return �C���N��
		 */
		inline int GetAmont()
		{
			return m_current_amont;
		}

		/**
		 * @brief ���݂̃C���N�̗ʐݒ�
		 * @param [in]�C���N��
		 */
		inline void SetAmont(int amont)
		{
			m_current_amont = amont;
		}

		/**
		 * @brief ���|�C���g����������
		 * @return �|�C���g������
		 */
		inline int GetCreateNum()
		{
			return m_create_num;
		}

		/**
		 * @brief ���݂̃C���N�̗ʐݒ�
		 * @param [in]�C���N��
		 */
		inline void SetCreateNum(int create_num)
		{
			m_create_num = create_num;
		}

		/**
		 * @brief �J�n�ʒu�擾
		 * @return �����n�߈ʒu
		 */
		inline D3DXVECTOR3 GetStartPos()
		{
			return m_start_pos;
		}

		/**
		 * @brief �J�n�ʒu�ݒ�
		 * @param [in]�J�n�ʒu
		 */
		inline void SetStartPos(D3DXVECTOR3 pos)
		{
			m_start_pos = pos;
		}

		/**
		 * @brief �������̃|�C���g�������̂ɂ��������t���[�����擾
		 * @param [in]�|�C���g�ԍ�
		 * @return ���������t���[����
		 */
		inline int GetCreateFrame(unsigned int idx)
		{
			if (idx > m_create_frame.size())
			{
				assert(false && "�͈͊O�̃T�C�Y");
			}

			return m_create_frame[idx];
		}

		/**
		 * @brief �����J�E���g�p�ϐ��擾
		 * @return �J�E���g�N���X�̃|�C���^
		 */
		inline CCount* GetCreateCnt()
		{
			return m_pCreateCnt;
		}
	private:

		int m_current_amont;									//!<���݂̗�
		int m_create_num;										//!<����������
		std::vector<int> m_create_frame;							//�O�Ղ��Ƃ̐����t���[��
		D3DXVECTOR3 m_start_pos;								//!<�n�_
		CCount* m_pCreateCnt;									//!<��������܂ł̃J�E���g
	};

	/** @brief �`���Ă��Ԓʏ�N���X */
	class CWriteCursol_Normal : public CWriteCursol
	{
	public:
		/**
		* @brief �R���X�g���N�^
		*/
		CWriteCursol_Normal();

		/**
		* @brief �f�X�g���N�^
		*/
		~CWriteCursol_Normal() override;

		/**
		* @brief �`��
		* @param [in]�}�E�X�J�[�\���̃|�C���^
		*/
		virtual void Write(CGameMouseCursor* mouse) override;

		/**
		 * @brief �J�[�\���̋O�Ր���
		 * @param [in]�}�E�X�J�[�\���̃|�C���^
		 */
		void CreateTrailPos(CGameMouseCursor* mouse) override;

		/**
		 * @brief ���`��Ԃ��r�؂�Ȃ��悤�ɐ���
		 * @param [in][out]�O�Ղ̈ʒu
		 */
		void GenerateInterpolatedPos(CGameMouseCursor* mouse, D3DXVECTOR3& trail_pos) override;
	private:
	};

	/** @brief �`���Ă��ԕK�E�Z�N���X */
	class CWriteCursol_Special : public CWriteCursol
	{
	public:
		/**
		* @brief �R���X�g���N�^
		*/
		CWriteCursol_Special();

		/**
		* @brief �f�X�g���N�^
		*/
		~CWriteCursol_Special() override;

		/**
		* @brief �`��
		* @param [in]�}�E�X�J�[�\���̃|�C���^
		*/
		virtual void Write(CGameMouseCursor* mouse) override;

		/**
		 * @brief �J�[�\���̋O�Ր���
		 * @param [in]�}�E�X�J�[�\���̃|�C���^
		 */
		void CreateTrailPos(CGameMouseCursor* mouse) override;

		/**
		 * @brief ���`��Ԃ��r�؂�Ȃ��悤�ɐ���
		 * @param [in][out]�O�Ղ̈ʒu
		 */
		void GenerateInterpolatedPos(CGameMouseCursor* mouse, D3DXVECTOR3& trail_pos) override;
	private:
		static const int TRAIL_CREATE_NUM =5;									//���ŉ��񐶐����邩
		static const int SPECIAL_AMONT = 400;										//����
		static const D3DXVECTOR3 TRAIL_CREATE_MIN_POS;
		static const D3DXVECTOR3 TRAIL_CREATE_MAX_POS;

		std::vector<CMouseTrail*> m_pTrail;
	};

	/** @brief �`���I�������ԃN���X */
	class CWrittenCursol : public CMouseCursorState
	{
	public:
		/**
		* @brief �R���X�g���N�^
		*/
		CWrittenCursol();

		/**
		* @brief �f�X�g���N�^
		*/
		~CWrittenCursol() override;

		/**
		* @brief �`���I�����
		* @param [in]�}�E�X�J�[�\���̃|�C���^
		*/
		virtual void Written(CGameMouseCursor* mouse) override;
	private:
		CCount* m_pTrailCreateCnt;								//!<�O�Ր�������܂ł̃J�E���g

		/**
		 * @brief �v���C���[���O�Ղ̏ꏊ��
		 * @param [in][out]���B������
		 */
		void PlayerSetPos(CMouseTrailPoint* point, bool& retflag);
	};

	/** @brief �|�[�Y��ԃN���X */
	class CPauseCursol : public CMouseCursorState
	{
	public:
		/**
		* @brief �R���X�g���N�^
		*/
		CPauseCursol();

		/**
		* @brief �f�X�g���N�^
		*/
		~CPauseCursol() override;

		/**
		* @brief �|�[�Y����
		* @param [in]�}�E�X�J�[�\���|�C���^
		*/
		virtual void Pause(CGameMouseCursor* mouse)override;
	private:
	}; 
}
#endif // !_MOUSE_CURSOR_STATE_H
