//=============================================
//
//�J�����̃X�e�[�g�p�^�[��[camera_state.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _CAMERA_STATE_H_
#define _CAMERA_STATE_H_

#include "camera.h"
#include "player.h"


/** @brief My ���O��� */
namespace My
{
	//=============================================
	//�O���錾
	//=============================================
	class CCamera;

	/** @brief �J�����X�e�[�g�N���X */
	class CCameraState
	{
	public:

		/**
		* @brief ���R���񏈗�(�e�ł͉������Ȃ�)
		* @param [in]�J�����̃|�C���^
		*/
		virtual void FreeView([[maybe_unused]] CCamera* camera) {};

		/**
		* @brief �O�l�̎��_(�e�ł͉������Ȃ�)
		* @param [in]�J�����̃|�C���^
		*/
		virtual void ThirdView([[maybe_unused]] CCamera* camera) {};

		/**
		* @brief �΂ߎ��_(�e�ł͉������Ȃ�)
		* @param [in]�J�����̃|�C���^
		*/
		virtual void DiagonalView([[maybe_unused]] CCamera* camera) {};
		
		/**
		* @brief �ォ��̎��_(�e�ł͉������Ȃ�)
		* @param [in]�J�����̃|�C���^
		*/
		virtual void TrailView([[maybe_unused]] CCamera* camera) {};

		/**
		* @brief ������̎��_(�e�ł͉������Ȃ�)
		* @param [in]�J�����̃|�C���^
		*/
		virtual void SideView([[maybe_unused]] CCamera* camera) {};
	};

	/** @brief ���R����N���X */
	class CFreeView : public CCameraState
	{
	public:

		/**
		* @brief ���R���񏈗�
		* @param [in]�J�����̃|�C���^
		*/
		virtual void FreeView(CCamera* camera)override;
	private:
		static constexpr float LENGTH = 200.0f;
	};

	/** @brief �O�l�̎��_�N���X */
	class CThirdView : public CCameraState
	{
	public:
		/**
		* @brief �O�l�̎��_
		* @param [in]�J�����̃|�C���^
		*/
		virtual void ThirdView(CCamera* camera)override;
	private:
		/**
		* @brief ���_�A�����_�Z�o
		* @param [in]�v���C���[�̃|�C���^
		* @param [in][out]�����_
		* @param [in][out]���_
		* @param [in][out]����
		*/
		void CalculateCameraView(CPlayer* pPlayer, D3DXVECTOR3& posR,  D3DXVECTOR3& posV, D3DXVECTOR3& rot);

		static constexpr float LENGTH = 130.0f;

		static constexpr float CORRECT_X = 20.0f; //�T�[�h�p�[�\���r���[���̕␳�lX
		static constexpr float CORRECT_Y = 55.0f; //�T�[�h�p�[�\���r���[���̕␳�lY
		static constexpr float CORRECT_Z = 20.0f; //�T�[�h�p�[�\���r���[���̕␳�lZ
	};

	/** @brief �O�Ղ�`���ۂ̎��_�N���X */
	class CTrailView : public CCameraState
	{
	public:
		/**
		* @brief �ォ��̎��_
		* @param [in]�J�����̃|�C���^
		*/
		virtual void TrailView(CCamera* camera)override;
	private:
		/**
		* @brief ���_�A�����_�Z�o����
		* @param [in]�v���C���[�̃|�C���^
		* @param [in][out]�����_
		* @param [in][out]���_
		* @param [in][out]����
		*/				
		void CalculateCameraView(CPlayer* pPlayer, D3DXVECTOR3& posR, D3DXVECTOR3& posV, D3DXVECTOR3& rot);
		//�o�[�h�r���[����Y�̋���	
		static constexpr float LENGTH_Y = 500.0f;
	};

	/** @brief �O�Ղ�`���ۂ̎��_�N���X */
	class CDiagonaView : public CCameraState
	{
	public:
		/**
		* @brief �ォ��̎��_
		* @param [in]�J�����̃|�C���^
		*/
		virtual void DiagonalView(CCamera* camera)override;
	private:
		/**
		* @brief ���_�A�����_�Z�o����
		* @param [in]�v���C���[�̃|�C���^
		* @param [in][out]�����_
		* @param [in][out]���_
		* @param [in][out]����
		*/
		void CalculateCameraView(CPlayer* pPlayer, D3DXVECTOR3& posR, D3DXVECTOR3& posV, D3DXVECTOR3& rot);
		//�o�[�h�r���[����Y�̋���	
		static constexpr float LENGTH_Y = 550.0f;
	};

	/** @brief ������̎��_�N���X */
	class CSideView : public CCameraState
	{
	public:
		/**
		* @brief ������̎��_
		* @param [in]�J�����̃|�C���^
		*/
		virtual void SideView(CCamera* camera)override;
	private:
		/**
		* @brief ���_�A�����_�Z�o����
		* @param [in]�v���C���[�̃|�C���^
		* @param [in][out]�����_
		* @param [in][out]���_
		* @param [in][out]����
		*/
		void CalculateCameraView(CPlayer* pPlayer, D3DXVECTOR3& posR, D3DXVECTOR3& posV, D3DXVECTOR3& rot);
		static constexpr float LENGTH_X = 20.0f;//�T�C�h�r���[���̋���X
		static constexpr float LENGTH_Y = 50.0f;//�T�C�h�r���[���̋���Y
		static constexpr float LENGTH_Z = 300.0f;//�T�C�h�r���[���̋���Z

		static constexpr float CORRECT_Y = 70.0f;//�T�C�h�r���[���̕␳�lZ
	};
}
#endif // !_CAMERA_STATE_H
