//=============================================
//
//アルティメット[ult.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _ULT_
#define _ULT_
#include "character_behavior.h"
#include "active_player.h"
#include "ult_icon.h"
#include "ult_range.h"
#include "ult_camera_effect.h"

//=============================================
//アルティメット処理ストラテジー
//=============================================
class CUlt
{
public:
	/**
	 * @brief コンストラクタ
	 */
	CUlt();
	/**
	 * @brief デストラクタ
	 */
	virtual ~CUlt();
	/**
	 * @brief 初期化
	 * @return 成功したか
	 */
	virtual HRESULT Init();
	/**
	 * @brief 終了
	 */
	virtual void Uninit();
	/**
	 * @brief 更新
	 */
	virtual void Update();
	/**
	 * @brief 実行
	 * @param [in]プレイヤーのポインタ
	 * @return 終わったか
	 */
	virtual bool Action(CActivePlayer* player) = 0;

	/**
	 * @brief クールタイム代入
	 * @param [in]クールタイム
	 */
	inline void SetCoolTime(int CoolTime)
	{
		m_CoolTime = CoolTime;
	}

	/**
	 * @brief クールタイム計測変数代入
	 * @param [in]クールタイム計測変数
	 */
	inline void SetCoolTimeCnt(int CoolTimeCnt)
	{
		m_CoolTimeCnt = CoolTimeCnt;
	}

	/**
	 * @brief クールタイム取得
	 * @return クールタイム
	 */
	inline int& GetCoolTime()
	{
		return m_CoolTime;
	}

	/**
	 * @brief クールタイム計測変数取得
	 * @return クールタイム計測変数
	 */
	inline int& GetCoolTimeCnt()
	{
		return m_CoolTimeCnt;
	}
protected:
	bool m_isFinish;
private:
	int m_CoolTime;
	int m_CoolTimeCnt;
};

//=============================================
//ミディアムキャラアルティメット処理ストラテジー
//=============================================
class CMediumUlt:public CUlt
{
public:
	/**
	 * @brief コンストラクタ
	 */
	CMediumUlt();
	/**
	 * @brief デストラクタ
	 */
	~CMediumUlt() override;
	/**
	 * @brief 初期化
	 * @return 成功したか
	 */
	HRESULT Init() override;
	/**
	 * @brief 終了
	 */
	void Uninit() override;
	/**
	 * @brief 更新
	 */
	void Update() override;
	/**
	 * @brief 実行
	 * @param [in]プレイヤーのポインタ
	 * @return 終了したか
	 */
	bool Action(CActivePlayer* player) override;
private:
	static const int MEDIUM_ULT_COOL_TIME = 900;
	static constexpr float FLYING_HIGHT = 400.0f; //どこまで飛ぶか
	static const D3DXVECTOR3 SPEED;

	float m_move_y; //y軸の移動量
	CUltRange* m_pUltRange; //ウルトの判定
	CUltCameraEffect* m_pUltCameraEffect; //ウルトのカメラエフェクト
};

#endif // !_ULT_
