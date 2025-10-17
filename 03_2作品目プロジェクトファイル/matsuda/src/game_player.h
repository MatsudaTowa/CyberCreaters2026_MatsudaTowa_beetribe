//=============================================
//
//�v���C���[[game_player.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _GAME_PLAYER_H_ //���ꂪ��`����ĂȂ��Ƃ�

#define _GAME_PLAYER_H_
#include "main.h"
#include "player.h"
#include "board_holder.h"
#include "game_player_state.h"
#include "player_move_point.h"
#include "combo.h"

/** @brief My ���O��� */
namespace My
{
	/**
	 * @brief �Q�[���v���C���[�N���X
	 * @copydoc CPlayer
	 */
	class CGamePlayer :public CPlayer
	{
	public:
		static const D3DXVECTOR3 PLAYER_SPAWN_POS;	//!<�X�|�[���ʒu
		static const D3DXVECTOR3 PLAYER_SPAWN_ROT;	//!<�X�|�[������

		/**
		 * @brief �R���X�g���N�^
		 * @param �v���C�I���e�B
		 */
		CGamePlayer(int nPriority = PLAYER_PRIORITY);

		/**
		 * @brief �f�X�g���N�^
		 */
		~CGamePlayer() override;

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
		 * @brief BGM���؂ꂽ���̏���
		 */
		void Play_Sound_BGM_000();

		/**
		 * @brief �X�e�[�g�ύX
		 * @param [in]���̃X�e�[�g
		 */
		void ChangeState(CGamePlayerState* state);

		/**
		 * @brief �R���{��UI�ݒ�
		 * @param [in]�R���{�̃|�C���^
		 */
		inline void SetComboUI(CCombo* combo)
		{
			m_pCombo = combo;
		}

		/**
		 * @brief ������ݒ�
		 * @param [in]�����̃|�C���^
		 */
		inline void SetBoardHolder(CBoardHolder* holder)
		{
			m_pBoardHolder.push_back(holder);
		}

		/**
		 * @brief ������ݒ�
		 * @param [in]�ړ��|�C���g
		 */
		inline void SetMovePoint(D3DXVECTOR3 pos)
		{
			CMovePoint* point = CMovePoint::Create(pos,new CPlayerMovePoint);
			m_pMovePoint.push_back(point);
		}

		/**
		 * @brief ��ԍŏ��̔������폜
		 */
		inline void EraseBoardHolder()
		{
			m_pBoardHolder.erase(m_pBoardHolder.begin());
		}	

		/**
		 * @brief �w�肳�ꂽ�ړ��|�C���g���폜
		 * @param [in]�ԍ�
		 */
		inline void EraseMovePoint(unsigned int idx)
		{
			if (idx >= m_pMovePoint.size())
			{
				return;
			}
			CMovePoint* point = m_pMovePoint[idx];
			point->Uninit();

			m_pMovePoint.erase(m_pMovePoint.begin()+idx);
		}

		/**
		 * @brief �S�Ă̈ړ��|�C���g���폜
		 */
		inline void ClearMovePoint()
		{
			for (auto& itr : m_pMovePoint)
			{
				if (itr == nullptr) { continue; }
				itr->Uninit();
				itr = nullptr;
			}
			m_pMovePoint.clear();
		}

		/**
		 * @brief �������擾
		 * @param [in]�ԍ�
		 * @return �����̃|�C���^
		 */
		inline CBoardHolder* GetBoardHolder(unsigned int idx)
		{
			if (idx >= m_pBoardHolder.size())
			{
				return nullptr;
			}
			return m_pBoardHolder[idx];
		}

		/**
		 * @brief �������擾
		 * @return �����̊i�[��
		 */
		inline int GetBoardHolderSize()
		{
			return m_pBoardHolder.size();
		}

		/**
		 * @brief �w�肳�ꂽ�ړ��|�C���g���폜
		 * @param [in]�ԍ�
		 * @return �ړ��|�C���g
		 */
		inline CMovePoint* GetMovePoint(unsigned int idx)
		{
			if (idx >= m_pMovePoint.size())
			{
				return nullptr;
			}
			return m_pMovePoint[idx];
		}
		
		/**
		 * @brief �X�e�[�g�擾
		 * @return �X�e�[�g�|�C���^
		 */
		inline CGamePlayerState* GetState()
		{
			return m_pState;
		}

		/**
		 * @brief �R���{UI�擾
		 * @return �R���{UI
		 */
		inline CCombo* GetComboUI()
		{
			return m_pCombo;
		}
private:
		static const D3DXVECTOR3 SHADOW_SIZE;	 //!<�e�̃T�C�Y

		/**
		 * @brief ���͏���
		 */
		void Input();

		/**
		 * @brief �v���C���[�̃f�o�b�O�\��
		 */
		void Debug()override;

		CGamePlayerState* m_pState;						//!�v���C���[�̃X�e�[�g
		std::vector<CMovePoint*> m_pMovePoint;			//!�ړ��|�C���g
		std::vector<CBoardHolder*> m_pBoardHolder;		//!�����i�[�|�C���^

		CCombo* m_pCombo;									//�R���{UI
	};
}
#endif