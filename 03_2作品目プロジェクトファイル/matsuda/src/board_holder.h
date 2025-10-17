//=============================================
//
//�����l[board_holder.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _BOARD_HOLDER_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _BOARD_HOLDER_H_
#include "main.h"
#include "character.h"
#include "hit_UI.h"
#include "board.h"

/** @brief My ���O��� */
namespace My
{
	/**
	 * @brief �����N���X
	 * @copydoc CCharacter
	 */
	class CBoardHolder :public CCharacter
	{
	public:
		static const int PRIORITY = 8;				//!<�`�揇

		/** @brief ���[�V�����̎�ޗ�*/
		enum Motion_Type
		{
			MOTION_NEUTRAL = 0,
			MOTION_MAX,
		};

		/** @brief �̌���*/
		enum Board_Direction
		{
			LEFT = 0,
			RIGHT,
			MAX
		};

		/**
		 * @brief �R���X�g���N�^
		 * @param �v���C�I���e�B
		 */
		CBoardHolder(int nPriority = PRIORITY);

		/**
		 * @brief �f�X�g���N�^
		 */
		~CBoardHolder() override;

		/**
		 * @brief ������
		 * @return ����������
		 */
		HRESULT Init() override;

		/**
		 * @brief �I��
		 */
		void Uninit() override;

		/**
		 * @brief �X�V
		 */
		void Update() override;

		/**
		 * @brief �`��
		 */
		void Draw() override;

		/**
		 * @brief �|�����
		 */
		void KnockDown();

		/**
		 * @brief ����
		 * @param [in]���W
		 * @param [in]�m�ۂ�������̃|�C���^
		 * @return �������ꂽ���̃|�C���^
		 */
		static CBoardHolder* Create(D3DXVECTOR3 pos, CBoardHolder* pBoardHolder);

		/**
		 * @brief �q�b�gUI����
		 */
		virtual void CreateHitUI();

		inline CHit_UI* GetHitUI() { return m_pHitUI; }
		inline void SetHitUI(CHit_UI* hit_ui) { m_pHitUI = hit_ui; }

		/**
		 * @brief �擾
		 * @param [in]�ԍ�
		 * @return ��
		 */
		inline CBoard* GetBoard(unsigned int idx)
		{
			if (idx >= m_pBoard.size())
			{
				return nullptr;
			}
			return m_pBoard[idx]; 
		}

		/**
		 * @brief �w�肳�ꂽ���폜
		 * @param [in]�ԍ�
		 */
		inline void EraseBoard(unsigned int idx)
		{
			if (idx >= m_pBoard.size())
			{
				return;
			}
			CBoard* board = m_pBoard[idx];
			board->Unload();

			m_pBoard.erase(m_pBoard.begin() + idx);
		}

		/**
		 * @brief �ǉ�
		 * @param [in]�ǉ�����|�C���^
		 */
		inline void PushBoard(CBoard* board)
		{
			if (board == nullptr)
			{
				return;
			}
			m_pBoard.push_back(board);
		}

		/**
		 * @brief ������ꂽ���̏���
		 */
		virtual void BreakBoard() = 0;
	private:
		/**
		 * @brief �v���C���[�����߂�
		 */
		void LookAtPlayer();
		std::vector<CBoard*> m_pBoard;	//!<��
		CCount* m_DelayDethCnt;	//���ʂ܂ł̗P�\�J�E���g
		CHit_UI* m_pHitUI; //!<�����������ɕ\������UI
	};

	/**
	 * @brief �������N���X
	 * @copydoc CBoardHolder
	 */
	class CBoardHolderInfo : public CBoardHolder
	{
	public:
		/**
		 * @brief �R���X�g���N�^
		 * @param �v���C�I���e�B
		 */
		CBoardHolderInfo(int nPriority = PRIORITY);

		/**
		 * @brief �f�X�g���N�^
		 */
		~CBoardHolderInfo() override;

		/**
		 * @brief ������
		 * @return ����������
		 */
		HRESULT Init() override;

		/**
		 * @brief �I��
		 */
		void Uninit() override;

		/**
		 * @brief �X�V
		 */
		void Update() override;

		/**
		 * @brief �`��
		 */
		void Draw() override;

		/**
		 * @brief ����ꂽ���̏���
		 */
		void BreakBoard() override;
	private:
		static const D3DXVECTOR3 RIGHT_TURN;	//�E�̔̉�]��
		static const D3DXVECTOR3 LEFT_TURN; 	//���̔̉�]��
		static constexpr float OFFSET_X = -10.0f; //X�̕␳�l
	};

	/**
	 * @brief �����N���X
	 * @copydoc CBoardHolder
	 */
	class CKawaraInfo : public CBoardHolder
	{
	public:
		/**
		 * @brief �R���X�g���N�^
		 * @param �v���C�I���e�B
		 */
		CKawaraInfo(int nPriority = PRIORITY);

		/**
		 * @brief �f�X�g���N�^
		 */
		~CKawaraInfo();

		/**
		 * @brief ������
		 * @return ����������
		 */
		HRESULT Init() override;

		/**
		 * @brief �I��
		 */
		void Uninit() override;

		/**
		 * @brief �X�V
		 */
		void Update() override;

		/**
		 * @brief �`��
		 */
		void Draw() override;

		/**
		 * @brief ����ꂽ���̏���
		 */
		void BreakBoard() override {};
	private:
	};

	/**
	 * @brief 㩎������N���X
	 * @copydoc CBoardHolder
	 */
	class CTrapHolderInfo : public CBoardHolder
	{
	public:
		/**
		 * @brief �R���X�g���N�^
		 * @param �v���C�I���e�B
		 */
		CTrapHolderInfo(int nPriority = PRIORITY);

		/**
		 * @brief �f�X�g���N�^
		 */
		~CTrapHolderInfo() override;

		/**
		 * @brief ������
		 * @return ����������
		 */
		HRESULT Init() override;

		/**
		 * @brief �I��
		 */
		void Uninit() override;

		/**
		 * @brief �X�V
		 */
		void Update() override;

		/**
		 * @brief �`��
		 */
		void Draw() override;

		/**
		 * @brief ����ꂽ���̏���
		 */
		void BreakBoard() override {};
	private:
		static constexpr float OFFSET_X = 8.0f; //X�̕␳�l

		/**
		 * @brief �q�b�gUI����
		 */
		void CreateHitUI()override;
	};
}
#endif