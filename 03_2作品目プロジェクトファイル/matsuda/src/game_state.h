//=============================================
//
//�Q�[���̃X�e�[�g�p�^�[��[game_state.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _GAME_STATE_H_
#define _GAME_STATE_H_

#include "paper.h"

/** @brief My ���O��� */
namespace My
{
	//=============================================
	//�O���錾
	//=============================================
	class CGame;

	/** @brief �Q�[���̃X�e�[�g�N���X */
	class CGameState
	{
	public:
		CGameState() {};
		virtual ~CGameState() {};
		/**
		* @brief �ʏ폈��(�e�ł͉������Ȃ�)
		* @param [in]�Q�[���|�C���^
		*/
		virtual void Normal([[maybe_unused]] CGame* game) {};

		/**
		* @brief �|�[�Y��ԏ���(�e�ł͉������Ȃ�)
		* @param [in]�Q�[���|�C���^
		*/
		virtual void Pause([[maybe_unused]] CGame* game) {};

		/**
		* @brief �v���C���[�U��������(�e�ł͉������Ȃ�)
		* @param [in]�Q�[���|�C���^
		*/
		virtual void Attack([[maybe_unused]] CGame* game) {};

		/**
		* @brief �K�E�Z�`������(�e�ł͉������Ȃ�)
		* @param [in]�Q�[���|�C���^
		*/
		virtual void SpecialWrite([[maybe_unused]] CGame* game) {};

		/**
		* @brief �K�E�Z�`������(�e�ł͉������Ȃ�)
		* @param [in]�Q�[���|�C���^
		*/
		virtual void SpecialAttack([[maybe_unused]] CGame* game) {};
	};

	/** @brief �ʏ�N���X */
	class CNormal :public CGameState
	{
	public:
		static const int SPECIAL_TIME = 30;	//�K�E�Z��ԂɈڂ鎞��
		/**
		* @brief �j���[�g��������
		* @param [in]�Q�[���v���C���[�|�C���^
		*/
		void Normal(CGame* game) override;
	private:
	};

	/** @brief ��ԏ����N���X */
	class CPause :public CGameState
	{
	public:
		~CPause()override;
		/**
		* @brief �|�[�Y��ԏ���
		* @param [in]�Q�[���|�C���^
		*/
		void Pause(CGame* game) override;
	private:
		static constexpr float THRESHOLD = 10.0f; // �������萔�ȉ��Ȃ瓞�B�Ƃ���i�K�v�ɉ����Ē����j
	};

	/** @brief �U���������N���X */
	class CAttack :public CGameState
	{
	public:
		~CAttack()override;
		/**
		* @brief �U����ԏ���
		* @param [in]�Q�[���|�C���^
		*/
		void Attack(CGame* game) override;
	private:
	};

	/** @brief �K�E�Z��`�������N���X */
	class CSpecialWrite :public CGameState
	{
	public:
		/**
		 * @brief �R���X�g���N�^
		 */
		CSpecialWrite();
		/**
		 * @brief �f�X�g���N�^
		 */
		~CSpecialWrite() override;
		/**
		* @brief �K�E�Z����
		* @param [in]�Q�[���|�C���^
		*/
		void SpecialWrite(CGame* game) override;
	private:
	};

	/** @brief �K�E�Z�̍U�������N���X */
	class CSpecialAttack :public CGameState
	{
	public:
		/**
		 * @brief �R���X�g���N�^
		 */
		CSpecialAttack();
		/**
		 * @brief �f�X�g���N�^
		 */
		~CSpecialAttack() override;
		/**
		* @brief �K�E�Z�U������
		* @param [in]�Q�[���|�C���^
		*/
		void SpecialAttack(CGame* game) override;
	private:
	};
}
#endif // !_GAME_PLAYER_STATE_H_
