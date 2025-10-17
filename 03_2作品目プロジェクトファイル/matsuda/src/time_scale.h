//=============================================
//
//時間管理[time_scale.h]
//Author Kasai Keisuke
//
//=============================================
#ifndef _TIME_SCALE_H_	//これが定義されていないとき

#define _TIME_SCALE_H_

/** @brief My 名前空間 */
namespace My
{
	/** @brief 時間管理クラス */
	class CTimeScale
	{
	public:
		/**
		 * @brief コンストラクタ
		 * @param [in]タイムスケール
		 */
		CTimeScale(float timeScale = 1.0f);

		/**
		 * @brief 初期化処理
		 * @return 成功したかどうか
		 */
		HRESULT Init();

		/**
		 * @brief タイムスケール設定
		 * @param [in]タイムスケール
		 */
		void SetTimeScale(float timescale);

		/**
		* @brief タイムスケール取得
		*/
		float GetTimeScale()const { return m_TimeScale; }

		operator float()const { return m_TimeScale; };


	private:
		float m_TimeScale;	//!<タイムスケール
	};
}

#endif