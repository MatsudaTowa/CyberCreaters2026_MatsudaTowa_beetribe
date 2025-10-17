//=============================================
//
//カメラのステートパターン[camera_state.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _CAMERA_STATE_H_
#define _CAMERA_STATE_H_

#include "camera.h"
#include "player.h"


/** @brief My 名前空間 */
namespace My
{
	//=============================================
	//前方宣言
	//=============================================
	class CCamera;

	/** @brief カメラステートクラス */
	class CCameraState
	{
	public:

		/**
		* @brief 自由旋回処理(親では何もしない)
		* @param [in]カメラのポインタ
		*/
		virtual void FreeView([[maybe_unused]] CCamera* camera) {};

		/**
		* @brief 三人称視点(親では何もしない)
		* @param [in]カメラのポインタ
		*/
		virtual void ThirdView([[maybe_unused]] CCamera* camera) {};

		/**
		* @brief 斜め視点(親では何もしない)
		* @param [in]カメラのポインタ
		*/
		virtual void DiagonalView([[maybe_unused]] CCamera* camera) {};
		
		/**
		* @brief 上からの視点(親では何もしない)
		* @param [in]カメラのポインタ
		*/
		virtual void TrailView([[maybe_unused]] CCamera* camera) {};

		/**
		* @brief 横からの視点(親では何もしない)
		* @param [in]カメラのポインタ
		*/
		virtual void SideView([[maybe_unused]] CCamera* camera) {};
	};

	/** @brief 自由旋回クラス */
	class CFreeView : public CCameraState
	{
	public:

		/**
		* @brief 自由旋回処理
		* @param [in]カメラのポインタ
		*/
		virtual void FreeView(CCamera* camera)override;
	private:
		static constexpr float LENGTH = 200.0f;
	};

	/** @brief 三人称視点クラス */
	class CThirdView : public CCameraState
	{
	public:
		/**
		* @brief 三人称視点
		* @param [in]カメラのポインタ
		*/
		virtual void ThirdView(CCamera* camera)override;
	private:
		/**
		* @brief 視点、注視点算出
		* @param [in]プレイヤーのポインタ
		* @param [in][out]注視点
		* @param [in][out]視点
		* @param [in][out]方向
		*/
		void CalculateCameraView(CPlayer* pPlayer, D3DXVECTOR3& posR,  D3DXVECTOR3& posV, D3DXVECTOR3& rot);

		static constexpr float LENGTH = 130.0f;

		static constexpr float CORRECT_X = 20.0f; //サードパーソンビュー時の補正値X
		static constexpr float CORRECT_Y = 55.0f; //サードパーソンビュー時の補正値Y
		static constexpr float CORRECT_Z = 20.0f; //サードパーソンビュー時の補正値Z
	};

	/** @brief 軌跡を描く際の視点クラス */
	class CTrailView : public CCameraState
	{
	public:
		/**
		* @brief 上からの視点
		* @param [in]カメラのポインタ
		*/
		virtual void TrailView(CCamera* camera)override;
	private:
		/**
		* @brief 視点、注視点算出処理
		* @param [in]プレイヤーのポインタ
		* @param [in][out]注視点
		* @param [in][out]視点
		* @param [in][out]方向
		*/				
		void CalculateCameraView(CPlayer* pPlayer, D3DXVECTOR3& posR, D3DXVECTOR3& posV, D3DXVECTOR3& rot);
		//バードビュー時のYの距離	
		static constexpr float LENGTH_Y = 500.0f;
	};

	/** @brief 軌跡を描く際の視点クラス */
	class CDiagonaView : public CCameraState
	{
	public:
		/**
		* @brief 上からの視点
		* @param [in]カメラのポインタ
		*/
		virtual void DiagonalView(CCamera* camera)override;
	private:
		/**
		* @brief 視点、注視点算出処理
		* @param [in]プレイヤーのポインタ
		* @param [in][out]注視点
		* @param [in][out]視点
		* @param [in][out]方向
		*/
		void CalculateCameraView(CPlayer* pPlayer, D3DXVECTOR3& posR, D3DXVECTOR3& posV, D3DXVECTOR3& rot);
		//バードビュー時のYの距離	
		static constexpr float LENGTH_Y = 550.0f;
	};

	/** @brief 横からの視点クラス */
	class CSideView : public CCameraState
	{
	public:
		/**
		* @brief 横からの視点
		* @param [in]カメラのポインタ
		*/
		virtual void SideView(CCamera* camera)override;
	private:
		/**
		* @brief 視点、注視点算出処理
		* @param [in]プレイヤーのポインタ
		* @param [in][out]注視点
		* @param [in][out]視点
		* @param [in][out]方向
		*/
		void CalculateCameraView(CPlayer* pPlayer, D3DXVECTOR3& posR, D3DXVECTOR3& posV, D3DXVECTOR3& rot);
		static constexpr float LENGTH_X = 20.0f;//サイドビュー時の距離X
		static constexpr float LENGTH_Y = 50.0f;//サイドビュー時の距離Y
		static constexpr float LENGTH_Z = 300.0f;//サイドビュー時の距離Z

		static constexpr float CORRECT_Y = 70.0f;//サイドビュー時の補正値Z
	};
}
#endif // !_CAMERA_STATE_H
