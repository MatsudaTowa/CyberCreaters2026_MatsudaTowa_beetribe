//=============================================
//
//カメラ[camera.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _CAMERA_H_ //これが定義されてないとき

#define _CAMERA_H_
#include "main.h"
#include "input.h"
#include "camera_state.h"

//=============================================
// 前方宣言
//=============================================
class CCameraState;

//=============================================
// カメラクラス
//=============================================
class CCamera
{
public:
	//カメラタイプ宣言
	enum CANERA_TYPE
	{
		TYPE_THIRDVIEW, //第三者視点
		TYPE_ULTVIEW, //ウルト視点
		TYPE_DEBUG,
		TYPE_MAX,
	};
	/**
	 * @brief コンストラクタ
	 */
	CCamera();
	/**
	 * @brief デストラクタ
	 */
	~CCamera();
	/**
	 * @brief 初期化
	 * @return 成功したか
	 */
	HRESULT Init();
	/**
	 * @brief 終了
	 */
	void Uninit();
	/**
	 * @brief 更新
	 */
	void Update();
	/*
	 * @brief カメラ設定 
	 */
	void SetCamera();
	/**
	 * @brief カメラリセット
	 */
	void ResetCamera();

	/**
	 * @brief 入力処理
	 */
	void InputMove();

	/**
	 * @brief ステート変更
	 * @param [in]次のステート
	 */
	void ChangeCameraState(CCameraState* state);

	/**
	 * @brief 方向設定
	 * @param [in]方向
	 */
	inline void SetRot(D3DXVECTOR3 rot)
	{
		m_rot = rot;
	}

	/**
	 * @brief 方向の移動量設定
	 * @param [in]方向
	 */
	inline void SetRotMove(D3DXVECTOR3 rot_move)
	{
		m_rotmove = rot_move;
	}

	/**
	 * @brief 視点設定
	 * @param [in]視点位置
	 */
	inline void SetPosV(D3DXVECTOR3 posV)
	{
		m_posV = posV;
	}
	/**
	 * @brief 注視点設定
	 * @param [in]注視点位置
	 */
	inline void SetPosR(D3DXVECTOR3 posR)
	{
		m_posR = posR;
	}

	/**
	 * @brief 動かすか設定
	 * @param [in]isActive
	 */
	inline void SetActive(bool isActive)
	{
		m_isActive = isActive;
	}

	/**
	 * @brief 距離設定
	 * @param [in]距離
	 */
	inline void SetLength(float length)
	{
		m_fLength = length;
	}

	/**
	 * @brief 方向取得
	 * @return 方向
	 */
	inline D3DXVECTOR3 GetRot()
	{
		return m_rot;
	}

	/**
	 * @brief 方向の移動量取得
	 * @return 方向の移動量
	 */
	inline D3DXVECTOR3 GetRotMove()
	{
		return m_rotmove;
	}

	/**
	 * @brief 視点取得
	 * @return 視点位置
	 */
	inline D3DXVECTOR3 GetPosV()
	{
		return m_posV;
	}

	/**
	 * @brief 注視点取得
	 * @return 注視点位置
	 */
	inline D3DXVECTOR3 GetPosR()
	{
		return m_posR;
	}

	/**
	 * @brief 動かす状態か取得
	 * @return 状態
	 */
	inline bool GetActive()
	{
		return m_isActive;
	}

	/**
	 * @brief 距離取得
	 * @return 距離
	 */
	inline float& GetLength()
	{
		return m_fLength;
	}

	/**
	 * @brief 設定された値を感度に変換
	 * @param [in]0.0～1.0の値
	 */
	void ConvertSens(float value)
	{
		m_sens = MIN_MOUSE_SENS + value * (MAX_MOUSE_SENS - MIN_MOUSE_SENS);
	}

	/**
	 * @brief 感度を設定する値に変換
	 * @return 0.0～1.0の値
	 */
	float ConvertSensToSettingValue()
	{
		return (m_sens - MIN_MOUSE_SENS) / (MAX_MOUSE_SENS - MIN_MOUSE_SENS);
	}

	/**
	 * @brief カメラのデバッグ表示
	 */
	void DebugCameraDraw();

	/**
	 * @brief カメラのデバッグ表示
	 */
	void ThirdViewCamera(); //サードパーソンビュー処理
private:
	static constexpr float DEFAULT_MOVE = 1.0f; //通常時の移動
	static constexpr float DAMPING_COEFFICIENT = 0.2f; //移動抵抗

	static constexpr float DEFAULT_LENGTH_Y = 200.0f; //通常状態のYの距離
	static constexpr float DEFAULT_LENGTH_Z = 500.0f; //通常状態のZの距離

	static constexpr float BIRDVIEW_LENGTH_Y = 300.0f; //バードビュー時のYの距離

	static constexpr float SIDEVIEW_LENGTH_X = 20.0f; //サイドビュー時のXの距離
	static constexpr float SIDEVIEW_LENGTH_Y = 50.0f; //サイドビュー時のYの距離
	static constexpr float SIDEVIEW_LENGTH_Z = 200.0f; //サイドビュー時のZの距離

	static constexpr float THIRDVIEW_CORRECT_X = 20.0f; //サードパーソンビュー時の補正値X
	static constexpr float THIRDVIEW_CORRECT_Y = 105.0f; //サードパーソンビュー時の補正値Y
	static constexpr float THIRDVIEW_CORRECT_Z = 20.0f; //サードパーソンビュー時の補正値Z

	static constexpr float DEFAULT_MOUSE_SENS = 0.00505f; //デフォルトのマウス感度
	static constexpr float MAX_MOUSE_SENS = 0.01f;		//最大のマウス感度
	static constexpr float MIN_MOUSE_SENS = 0.0001f;	//最小のマウス感度

	static constexpr float TURN_SPEED = 0.02f; //カメラの回転スピード

	static constexpr float MAX_TURN_X = 0.45f; //サードパーソンビュー時のXの最大可動域
	static constexpr float MIN_TURN_X = -0.45f; //サードパーソンビュー時のXの最小可動域

	static constexpr float ROT_MOVE_FRICTION = 0.3f; //移動抵抗

	/**
	 * @brief カメラ回転処理
	 */
	void CameraTurn();

	D3DXVECTOR3 m_posV; //視点
	D3DXVECTOR3 m_posR; //注視点

	D3DXVECTOR3 m_moveV; //視点移動量
	D3DXVECTOR3 m_moveR; //注視点移動量

	D3DXVECTOR3 m_vecU; //上方向ベクトル

	D3DXVECTOR3 m_rot; //方向
	D3DXVECTOR3 m_rotmove; //回転量

	bool m_isActive;	//動かせる状態かどうか
	float m_sens;		//マウス感度
	float m_fLength;	//対象との距離
	float m_fAngle;		//対象との対角線の角度

	D3DXMATRIX m_mtxProjection; //プロジェクション
	D3DXMATRIX m_mtxView; //ビュー行列
	CCameraState* m_pCameraState;

};
#endif
