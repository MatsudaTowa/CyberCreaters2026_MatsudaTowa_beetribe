//=============================================
//
//�Q�[���v���C���[�̃X�e�[�g�p�^�[��[game_player_state.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _GAME_PLAYER_STATE_H_
#define _GAME_PLAYER_STATE_H_

#include "character.h"
#include "board_holder.h"

/** @brief My ���O��� */
namespace My
{
	//=============================================
	//�O���錾
	//=============================================
	class CGamePlayer;

	/** @brief �v���C���[�̃X�e�[�g�N���X */
	class CGamePlayerState
	{
	public:
		CGamePlayerState() {};
		virtual ~CGamePlayerState() {};
		/**
		* @brief �j���[�g��������(�e�ł͉������Ȃ�)
		* @param [in]�Q�[���v���C���[�|�C���^
		*/
		virtual void Neutral([[maybe_unused]] CGamePlayer* player) {};

		/**
		* @brief ���R�ړ�����(�e�ł͉������Ȃ�)
		* @param [in]�Q�[���v���C���[�|�C���^
		*/
		virtual void MovetoFree([[maybe_unused]] CGamePlayer* player) {};

		/**
		* @brief �U������(�e�ł͉������Ȃ�)
		* @param [in]�Q�[���v���C���[�|�C���^
		*/
		virtual void Attack([[maybe_unused]] CGamePlayer* player) {};
	};

	/** @brief �v���C���[�̃j���[�g�����N���X */
	class CNeutralState :public CGamePlayerState
	{
	public:
		/**
		* @brief �j���[�g��������
		* @param [in]�Q�[���v���C���[�|�C���^
		*/
		void Neutral(CGamePlayer* player) override;
	};

	/** @brief �v���C���[�̎��R�ړ��N���X */
	class CMovetoFreeState :public CGamePlayerState
	{
	public:
		/**
		* @brief ���R�ړ�����
		* @param [in]�Q�[���v���C���[�|�C���^
		*/
		void MovetoFree(CGamePlayer* player) override;
	private:
		static constexpr float THRESHOLD = 10.0f; // �������萔�ȉ��Ȃ瓞�B�Ƃ���i�K�v�ɉ����Ē����j
	};

	/** @brief �v���C���[�̍U���N���X */
	class CAttackState :public CGamePlayerState
	{
	public:
		/**
		 * @brief �R���X�g���N�^
		 */
		CAttackState();
		/**
		* @brief �U������
		* @param [in]�Q�[���v���C���[�|�C���^
		*/
		void Attack(CGamePlayer* player) override;
	private:
		static const int DELAY_FLAME = 60;	//�J�ڂ܂ł̃t���[����
		static const int PENALTY = 5;		//�g���b�v�����������̃^�C������
		static const D3DXVECTOR3 COMBO_UI_POS; 	//�R���{UI�̈ʒu
		/**
		 * @brief �����̂ق�������
		 * @param [in]�����|�C���^
		 * @param [in]�v���C���[�|�C���^
		 */
		void LookAtBoardHolder(My::CBoardHolder* board_holder, My::CGamePlayer* player);
	};
}
#endif // !_GAME_PLAYER_STATE_H_
