//=============================================
//
//�Q�[���}�l�[�W���[[gamemaneger.h]
//Auther MatsudaTowa
//
//=============================================

#ifndef _GAME_MANAGER_H_	//���ꂪ��`����ĂȂ��Ƃ�
#define _GAME_MANAGER_H_	//��d�}�N���h�~

//�w�b�_�[�̃C���N���[�h
#include "game_player.h"
#include "game_mouse_cursor.h"
#include "board_holder_generator.h"
#include "timer.h"
#include "time_scale.h"
#include "game_state.h"
#include "field.h"
#include "score.h"

/** @brief My ���O��� */
namespace My
{
	/** @brief �Q�[���}�l�[�W���[�N���X */
	class CGameManager
	{
	public:
		/**
		 * @brief �R���X�g���N�^
		 */
		CGameManager();

		/**
		 * @brief �f�X�g���N�^
		 */		
		~CGameManager();

		/**
		 * @brief �I��
		 */		
		void Uninit();

		/**
		 * @brief �������g�̃C���X�^���X�𐶐����擾
		 */
		static CGameManager* GetInstance()
		{
			//�ÓI�C���X�^���X
			static CGameManager instance;
			return &instance;
		}

		/**
		 * @brief �v���C���[�̐ݒ�
		 * @param [in]�v���C���[�̃|�C���^
		 */		
		void SetPlayer(CGamePlayer* player) { m_pPlayer = player; }

		/**
		 * @brief �v���C���[�̎擾
		 * @return �v���C���[�̃|�C���^
		 */		
		CGamePlayer* GetPlayer() { return m_pPlayer; }

		/**
		 * @brief ���̐ݒ�
		 * @param [in]���̃|�C���^
		 */
		void SetField(CField* field) { m_pField = field; }

		/**
		 * @brief ���̎擾
		 * @return ���̃|�C���^
		 */
		CField* GetField() { return m_pField; }

		/**
		 * @brief ���̐ݒ�
		 * @param [in]���̃|�C���^
		 */
		void SetPaper(CPaper* paper) { m_pPaper = paper; }

		/**
		 * @brief ���̎擾
		 * @return ���̃|�C���^
		 */
		CPaper* GetPaper() { return m_pPaper; }

		/**
		 * @brief �Q�[���̃X�e�[�g�̐ݒ�
		 * @param [in]�Q�[���̃X�e�[�g�̃|�C���^
		 */
		void SetState(CGameState* state) { m_pState = state; }

		/**
		 * @brief �Q�[���̃X�e�[�g�擾
		 * @return �Q�[���̃X�e�[�g�|�C���^
		 */
		CGameState* GetState() { return m_pState; }

		/**
		 * @brief �}�E�X�J�[�\���̐ݒ�
		 * @param [in]�}�E�X�J�[�\���̃|�C���^
		 */
		void SetMouseCursor(CGameMouseCursor* mouse_cursor) { m_pMouseCursor = mouse_cursor; }

		/**
		 * @brief �}�E�X�J�[�\���̎擾
		 * @return �}�E�X�J�[�\���̃|�C���^
		 */
		CGameMouseCursor* GetMouseCursor() { return m_pMouseCursor; }

		/**
		 * @brief �W�F�l���[�^�[�̐ݒ�
		 * @param [in]�W�F�l���[�^�[�̃|�C���^
		 */
		void SetGenerator(CBoardHolderGenerator* generator) 
		{ 
			m_pGenerator = generator; 
		}

		/**
		 * @brief �^�C�}�[�擾
		 * @return �^�C�}�[�̃|�C���^
		 */
		CTimer* GetTimer() { return m_pTimer; }

		/**
		 * @brief �^�C�}�[�̐ݒ�
		 * @param [in]�^�C�}�[�̃|�C���^
		 */
		void SetTimer(CTimer* timer)
		{
			m_pTimer = timer;
		}

		/**
		 * @brief �W�F�l���[�^�[�擾
		 * @return �W�F�l���[�^�[�̃|�C���^
		 */
		CBoardHolderGenerator* GetGenerator() { return m_pGenerator; }
	
		/**
		 * @brief �^�C���X�P�[���̐ݒ�
		 * @param [in]�^�C���X�P�[���̃|�C���^
		 */
		void SetTimeScalePointer(CTimeScale* timescale)
		{
			m_pTimeScale = timescale;
		}

		/**
		 * @brief �^�C���X�P�[���擾
		 * @return �^�C���X�P�[���̃|�C���^
		 */
		CTimeScale* GetTimeScalePointer() { return m_pTimeScale; }

		/**
		 * @brief �X�e�[�g�ύX
		 * @param [in]���̃X�e�[�g
		 */
		void ChangeState(CGameState* state);

		/**
		 * @brief �X�e�[�g���s����
		 * @param [in]�Q�[���̃V�[���|�C���^
		 */
		void GameStateExecution(CGame* game)
		{
			if (m_pState == nullptr) { return; }

			m_pState->Normal(game);
			m_pState->Pause(game);
			m_pState->Attack(game);
			m_pState->SpecialWrite(game);
			m_pState->SpecialAttack(game);
		}
	
		/**
		 * @brief �I���ݒ�
		 * @param [in]�I�������邩
		 */
		inline void SetFinish(bool is_finish)
		{
			m_isFinish = is_finish;
		}

		/**
		 * @brief �I���擾
		 * @return �I�������邩
		 */
		inline bool GetFinish()
		{
			return m_isFinish;
		}
	private:
		CGameState* m_pState;				//!<�Q�[���̃X�e�[�g���
		CGamePlayer* m_pPlayer;				//!<�v���C���[
		CField* m_pField;					//!<��
		CGameMouseCursor* m_pMouseCursor;	//!<�}�E�X�J�[�\��
		CBoardHolderGenerator* m_pGenerator;//!<�W�F�l���[�^�[
		CTimer* m_pTimer;					//!�^�C�}�[
		CTimeScale* m_pTimeScale;			//!<�^�C���X�P�[��
		CPaper* m_pPaper;					//!��
		bool m_isFinish;					//!�Q�[���̏������I��点�邩
	};
}

#endif